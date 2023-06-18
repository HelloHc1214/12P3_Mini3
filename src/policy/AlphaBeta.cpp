#include <cstdlib>

#include "../state/state.hpp"
#include "./AlphaBeta.hpp"
#define MAX(a,b) a > b? a : b
#define MIN(a,b) a < b? a : b 
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBeta::get_move(State *state, int depth,int a,int b){
  if(!state->legal_actions.size())
    state->get_legal_actions();

  Move BestStep;
  int BestValue = -100000000;
  for (auto it : state->legal_actions){
    State* next_S = (*state).next_state(it);
    int AB_culculate = get_alphabeta(next_S,depth -1,false,-10000000,10000000);
    if (AB_culculate > BestValue){
      BestValue = AB_culculate;
      BestStep = it;
    }
    delete next_S;
  }
  return BestStep;
}

int AlphaBeta::get_alphabeta(State *state2, int depth2,bool me,int a,int b){
  if(!state2->legal_actions.size())
    state2->get_legal_actions();

  if (depth2 == 0){
    if (me){
      return (*state2).evaluate();
    }else {
      return (*state2).evaluate() * (-1);
    }
  }else if (me){
    
    for (auto it2 : state2->legal_actions){
      a = MAX(a,get_alphabeta((*state2).next_state(it2),depth2 - 1,false,a,b));
      if (a >= b) break;
    }
    return a;
  }else {
    
    for (auto it3 : state2->legal_actions){
      b = MIN(b,get_alphabeta((*state2).next_state(it3),depth2 - 1,true,a,b));
      if (a >= b) break;
    }
    return b;
  }
}