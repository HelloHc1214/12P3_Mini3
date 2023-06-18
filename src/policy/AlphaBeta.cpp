#include <cstdlib>
#include <algorithm>
#include "../state/state.hpp"
#include "./AlphaBeta.hpp"
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
  int val = -100000000;
  for (auto &it : state->legal_actions){
    State* next_S = (*state).next_state(it);
    int AB_culculate = get_alphabeta(next_S,depth -1,false,-10000000,10000000);
    val = std::max(val,AB_culculate);
    if (val > a){
      a = val;
      //BestValue = AB_culculate;
      BestStep = it;
    }
  }
  return BestStep;
}

int AlphaBeta::get_alphabeta(State *state3, int depth3,bool me,int a,int b){
  if(!state3->legal_actions.size()) state3->get_legal_actions();


  if (depth3 == 0 || !state3->legal_actions.size()){
    if (me){
      return (*state3).evaluate();
    }else {
      return (*state3).evaluate() * (-1);
    }
  }else if (me){
    int val1 = -10000000;
    for (auto it2 : state3->legal_actions){
      val1 = std::max(val1,get_alphabeta((*state3).next_state(it2),depth3 - 1,false,a,b));
      a = std::max(a,val1);
      if (a >= b) break;
    }
    return val1;
  }else {
    int val2 = 10000000;
    for (auto it3 : state3->legal_actions){
      val2 = std::min(val2,get_alphabeta((*state3).next_state(it3),depth3 - 1,true,a,b));
      b = std::min(b,val2);
      if (a >= b) break;
    }
    return val2;
  }
}