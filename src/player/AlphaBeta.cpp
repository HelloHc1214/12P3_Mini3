#include <iostream>
#include <fstream>

#include "../config.hpp"
#include "../state/state.hpp"
#include "../policy/AlphaBeta.hpp"

State* root;
int depth;
/**
 * @brief Read the board from the file
 * 
 * @param fin 
 */
void read_board(std::ifstream& fin) {
  Board board;
  int player;
  fin >> player;

  for (int pl=0; pl<2; pl++) {
    for (int i=0; i<BOARD_H; i++) {
      for (int j=0; j<BOARD_W; j++) {
        int c; fin >> c;
        // std::cout << c << " ";
        board.board[pl][i][j] = c;
      }
      // std::cout << std::endl;
    }
  }
  root = new State(board, player);
  root->get_legal_actions();
}


/**
 * @brief randomly choose a move and then write it into output file
 * 
 * @param fout
 */
void write_valid_spot(std::ofstream& fout) {
  // Keep updating the output until getting killed.
  Move move;
  depth = 5;
  /*static const char init_board[3][BOARD_H][BOARD_W] ={
    {
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1},
      {2, 3, 4, 5, 6},
    },
    {
      {6, 5, 4, 3, 2},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    },
    {
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {0, 1, 1, 1, 1},
      {2, 3, 4, 5, 6},      
    }
  }; */
  while(true) {
    /*if (root->player == 0){
      if (root->board.board[0] == init_board[0]){
        move = {Point(4,3),Point(3,3)};
        break;
      }
    }*/
    // Choose a random spot.
    if (depth == 7) break;
    move = AlphaBeta::get_move(root, depth);

    fout << move.first.first << " " << move.first.second << " "\
         << move.second.first << " " << move.second.second <<std::endl;
    depth+=1;
    // Remember to flush the output to ensure the last action is written to file.
    fout.flush();
    //break;
  }
}


/**
 * @brief Main function for player
 * 
 * @param argv 
 * @return int 
 */
int main(int, char** argv) {
  srand(RANDOM_SEED);
  std::ifstream fin(argv[1]);
  std::ofstream fout(argv[2]);

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
