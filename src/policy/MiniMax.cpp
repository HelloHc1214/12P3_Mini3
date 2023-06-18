#include <cstdlib>

#include "../state/state.hpp"
#include "./MiniMax.hpp"
#define MAX(a,b) a > b? a : b
#define MIN(a,b) a < b? a : b 
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move MiniMax::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();

  Move BestStep;
  int BestValue = -100000000;
  for (auto it : state->legal_actions){
    State* next_S = (*state).next_state(it);
    int NowCal = get_evaluate(next_S,depth -1,false);
    if (NowCal >= BestValue){
      BestValue = NowCal;
      BestStep = it;
    }
    delete next_S;
  }
  return BestStep;
}

int MiniMax::get_evaluate(State *state2, int depth2,bool me){
  if(!state2->legal_actions.size())
    state2->get_legal_actions();

  if (depth2 == 0){
    if (me){
      return (*state2).evaluate();
    }else {
      return (*state2).evaluate() * (-1);
    }
  }else if (me){
    int CalBest = -100000000;
    for (auto it2 : state2->legal_actions){
      int Next_Val = get_evaluate((*state2).next_state(it2),depth2 -1,false);
      CalBest = MAX(CalBest,Next_Val);
    }
    return CalBest;
  }else {
    int CalBest = 100000000;
    for (auto it3 : state2->legal_actions){
      int Next_Val = get_evaluate((*state2).next_state(it3),depth2 -1,true);
      CalBest = MIN(CalBest,Next_Val);
    }
    return CalBest;
  }
}