#include <iostream>
#include <sstream>
#include <cstdint>

#include "./state.hpp"
#include "../config.hpp"


/**
 * @brief evaluate the state
 * 
 * @return int 
 */
int State::evaluate(){
  // [TODO] design your own evaluation function
  
  static const char bouns[7][BOARD_H][BOARD_W] = {
  {//empty
    {0, 0, 0, 0, 0},
    {0,0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
  
  },    
  {//pawn
    {0, 0, 0, 0, 0},
    {20, 20, 20, 20, 20},
    {2, 2, 10, 2, 2},//
    {0, 0, 8, 0, 0},//
    {2, 4, -8, 4, 2},
    {0, 0, 0, 0, 0},
  },
  {//rookt
    {0, 0, 0, 0, 0},
    {2,4, 4, 4,2},
    {-2, 0, 0, 0, -2},
    {-2, 0, 0, 0, -2},
    {-2, 0, 0, 0, -2},
    {0, 0, 2, 0, 0},
  
  },
  {//knight
    {-20, -16, -12, -16, -20},
    {-16,-8, 0, -8, -16},
    {-12, 2,8, 2, -12},
    {-12, 0,8, 0, -12},
    {-16, -8, 2, -8, -16},
    {-20, -16, -12, -16, -20},
  },
  {//bishopt(2)
    {-8, -4, -4, -4, -8},
    {-4,0, 0, 0, -4},
    {-4, 2, 4, 2, -4},
    {-4, 0, 4, 0, -4},
    {-4, 2, 0, 2, -4},
    {-8, -4, -4, -4, -8},
  },
  {//queent(2)
    {-8, -4, -2, -4, -8},
    {-2, 0, 2, 0, -2},
    {0, 0, 2, 0, -2},//
    {-4,0, 0, 0, -4},//
    {-8, -4, -2, -4, -8},
  
  },
  {//kingt(2)
    {-12, -16, -20, -16, -12},
    {-12, -16, -20, -16, -12},
    {-12, -16, -20, -16, -12},
    {-8, -12, -16, -12, -8},
    {8, 8, 0, 8, 8},
    {8, 12, 0, 12, 8},
  
  }
  };
  /*
  int State_Value = 0;
  const int Chess_Point[7] = {0,95,500,320,300,900,100000};
  for (int i = 0;i < BOARD_H;i++){
    for (int j= 0;j < BOARD_W;j++){
      int BlockType = board.board[player][i][j];
      if (BlockType != 0){
        if (!player) State_Value += (Chess_Point[BlockType] + bouns[BlockType-1][i][j]);
        else State_Value -= (Chess_Point[BlockType] + bouns[BlockType-1][5-i][4-j]);
      }
      BlockType = board.board[1 - player][i][j];
      if (BlockType != 0){
        if (!(player)) State_Value -= (Chess_Point[BlockType] + bouns[BlockType-1][5-i][4-j]);
        else State_Value += (Chess_Point[BlockType] + bouns[BlockType-1][i][j]);
      }
    }
  }
  return State_Value;*/
  
  int State_Value = 0;
  const int Chess_Point[7] = {0,4,20,12,12,36,100000};
  for (int i = 0;i < BOARD_H;i++){
    for (int j= 0;j < BOARD_W;j++){
      int WhiteBlock = board.board[0][i][j];
      int BlackBlock = board.board[1][i][j];
      int WhiteBouns = bouns[WhiteBlock][i][j];
      int BlackBouns = bouns[BlackBlock][5-i][4-j];
      //for (auto action = legal_actions.begin();action != legal_actions.end();action++){
        //State_Value += 1;
      //}
      if (player == 0){
        //if (WhiteBlock == 1){
          //if (i - 1 >= 0 && board.board[0][i-1][j] == '1' ) State_Value -= 2;
        //}
        State_Value += (Chess_Point[WhiteBlock] + WhiteBouns + 12);
        State_Value -= (Chess_Point[BlackBlock] + BlackBouns + 4);
      }else if (player == 1){
        //if (BlackBlock == 1){
          //if (i - 1 >= 0 && board.board[1][i-1][j] == '1' ) State_Value -= 2;
        //}
        State_Value += (Chess_Point[BlackBlock] + BlackBouns + 4);
        State_Value -= (Chess_Point[WhiteBlock] + WhiteBouns + 12);
      }
    }
  }
  return State_Value;
  /*
  int State_Value = 0;
  static const int Chess_Point[7] = {0,1,5,3,3,9,1000};
  for (int i = 0;i < BOARD_H;++i){
    for (int j= 0;j < BOARD_W;++j){
      int BlockType = board.board[player][i][j];
      if (BlockType != 0){
        State_Value += Chess_Point[BlockType];
      }
      BlockType = board.board[1 - player][i][j];
      if (BlockType != 0){
        State_Value -= Chess_Point[BlockType];
      }
    }
  }
  */
}


/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-player][to.first][to.second]){
    next.board[1-player][to.first][to.second] = 0;
  }
  
  next.board[player][from.first][from.second] = 0;
  next.board[player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-player);
  
  if(game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}