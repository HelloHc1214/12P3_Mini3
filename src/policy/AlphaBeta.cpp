#include <cstdlib>
#include <algorithm>
#include "../state/state.hpp"
#include "./AlphaBeta.hpp"



Move AlphaBeta::get_move(State *state, int depth){

  if(state->legal_actions.empty())
    state->get_legal_actions();

  //stored_state state_table
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
  //std::string table_key = state->encode_state();
  //if (state_table.count(table_key)){
  //  return state_table[table_key];
  //}
  if(state->legal_actions.empty()) state->get_legal_actions();
  if (depth == 0 || state->legal_actions.empty()){
    if (me){
      int state_val = state->evaluate();
      //state_table[table_key] = state_val;
      return state_val;
    }else {
      int state_val = -state->evaluate();
      //state_table[table_key] = state_val;
      return state_val;
    }
  }
  //return me ? state->evaluate() : -state->evaluate();
  if(state->game_state == WIN) {
    if (me) {
      //state_table[table_key] =  INT32_MAX;
      return INT32_MAX;      
    }else {
      //state_table[table_key] = INT32_MIN;
      return INT32_MIN;
    }
  }

  if (me){
    int value = -100000;
    for (const auto& it : state->legal_actions){
      State* NewState = state->next_state(it);
      value = std::max(value,get_alphabeta(NewState, depth - 1, false, alpha, beta));
      alpha = std::max(value,alpha);
      if (alpha >= beta) break;
    }
    //state_table[table_key] = value;
    return value;
  }else {
    int value = 100000;
    for (const auto& it : state->legal_actions){
      State* NewState = state->next_state(it);
      value = std::min(value, get_alphabeta(NewState, depth - 1, true, alpha, beta));
      beta = std::min(value,beta);
      if (alpha >=beta) break;
    }
    //state_table[table_key] = value;
    return value;
  }
}