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
Move AlphaBeta::get_move(State *state, int depth){
  if(state->legal_actions.empty())
    state->get_legal_actions();

  Move BestStep;
  int val = -100000;
  for (const auto &it : state->legal_actions){
    State* next_S = state->next_state(it);
    int AB_culculate = get_alphabeta(next_S,depth -1,false,-100000,100000);
    if (AB_culculate > val){
      val = AB_culculate;
      BestStep = it;
    }
  }
  return BestStep;
}

int AlphaBeta::get_alphabeta(State *state, int depth,bool me,int alpha,int beta){
  if(state->legal_actions.empty()) state->get_legal_actions();


  if (depth == 0 || state->legal_actions.empty() || state->game_state == WIN)
    return me ? state->evaluate() : -state->evaluate();

  if (me){
    int value = -100000;
    for (const auto& it : state->legal_actions){
      State* NewState = state->next_state(it);
      value = std::max(value,get_alphabeta(NewState, depth - 1, false, alpha, beta));
      alpha = std::max(value,alpha);
      if (alpha >= beta) break;
    }
    return value;
  }else {
    int value = 100000;
    for (const auto& it : state->legal_actions){
      State* NewState = state->next_state(it);
      value = std::min(value, get_alphabeta(NewState, depth - 1, true, alpha, beta));
      beta = std::min(value,beta);
      if (alpha >=beta) break;
    }
    return value;
  }
}