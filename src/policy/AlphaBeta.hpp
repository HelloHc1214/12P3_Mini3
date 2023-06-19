#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class AlphaBeta{
public:
  static Move get_move(State *state, int depth);
  static int get_alphabeta(State *state2,int depth2,bool me,int alpha,int beta);
};