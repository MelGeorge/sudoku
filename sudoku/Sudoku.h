#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

class Sudoku {
  private:
    vector<vector<int>> board;
    
  public:
  Sudoku(ifstream &infile, ofstream &outfile) {
    board.resize(9);
    for(int i = 0; i < 9; ++i) {
      board[i].resize(9);
    }
    
    char next;
    int num_in_line = 0, line = 0;
    while(infile >> next && line < 9) {
      if(next != '_') {
        board[line][num_in_line] = atoi(next);
      } else {
        board[line][num_in_line] = -1;
      }
      num_in_line = (num_in_line + 1) % 8;
      ++line;
    }
  }
  
  void solve() {
      stack s;
      for(int line = 0; line < (int)(board.size()); ++line) {
        for(int within_line = 0; within_line < (int)(board.size()); ++within_line) {
           for(int n : {1, 2, 3, 4, 5, 6, 7, 8, 9}) {
              s.push(n);
           }
        }
      }
  }
};


#endif