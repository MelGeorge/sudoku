#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "Sudoku.h"

using namespace std;

void setup_board(vector<vector<int>> &board) {
    
  string next;
  
  for(size_t row = 0; row < 9; ++row) {
      board[row].resize(9);
      for(size_t col = 0; col < 9; ++col) {
          cin >> next;
          if(next != "_") {
              board[row][col] = stoi(next);
          } else {
              board[row][col] = -1;
          }
      }
  }
  
}

void print_solution(const vector<vector<int>> &board) {
    for(size_t row = 0; row < 9; ++row) {
        for(size_t col = 0; col < 9; ++col) {
            cout << board[row][col] << ' ';
        }
        cout << '\n';
    }
}

int main() {
  cout << "\nWelcome to Sudoku Solver! Stuck?\n\n";
  
  vector<vector<int>> board(9);
  
  setup_board(board);

  Sudoku sudoku(board);
  
  if(sudoku.solve()) {
      print_solution(board);
  } else {
      cout << "No solution!\n";
  }
  
  return 0;
}
