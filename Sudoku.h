#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <stack>

using namespace std;

class Sudoku {
private:

   struct Square {
   Square(size_t x, size_t y, size_t i, int v) 
      : x(x), y(y), index(i), val(v) {}

      size_t x, y, index;
      int val;
   };

   vector<vector<int>> board;
   vector<unordered_map<int, bool> > rows;
   vector<unordered_map<int, bool> > cols;
   vector<Square> path;
   size_t unfilled = 0;
    
public:

  // Ctor for sudoku board -- constructs
  // from input file & hashes already used values
  Sudoku(ifstream &infile) {
    // Make everything the correct size
    rows.resize(9);
    cols.resize(9);
    board.resize(9);
    for(size_t i = 0; i < 9; ++i) {
      board[i].resize(9);
    }
    
    string next;

    // Read in/ setup board
    for(size_t row = 0; row < 9; ++row) {
       for(size_t col = 0; col < 9; ++col) {
          infile >> next;
          if(next != "_") {
             board[row][col] = stoi(next);
             rows[row][stoi(next)] = true;
             cols[col][stoi(next)] = true;
          } else {
             board[row][col] = -1;
             path.push_back(Square(row, col, path.size(), -1));
             ++unfilled;
          }
       }
    }
  }
  
  // Function for finding / storing the solution using
  // a backtrackig algorithm
  void solve() {
      // Safety check:
      if(path.size() == 0) { return; }
      
      size_t current_index = 0; 
      Square square = path[0];
      stack<Square> s;
      
      // Add options for first open space
      for(int n = 1; n < 10; ++n) {
          if(!rows[path[0].x][n] && !cols[path[0].y][n]) {
              square.val = n;
              s.push(square);
          }
      }
      
      // Iteratively go through all open spaces,
      // using a stack to backtrack when Sudoku
      // invariants can no longer be satisfied
      while(!s.empty()) {
          square = s.top();
          s.pop();

          for(size_t i = square.index; i <= current_index; ++i) {
            rows[path[i].x][path[i].val] = false;
            cols[path[i].y][path[i].val] = false;
            path[i].val = -1;
          }
          
          path[square.index].val = square.val;
          rows[square.x][square.val] = true;
          cols[square.y][square.val] = true;

          current_index = square.index;
          
          if(current_index == unfilled - 1) {
              path[current_index].val = square.val;
              return;
          }
          
          square = path[square.index + 1];

          for(int n = 1; n < 10; ++n) {
               if(!rows[square.x][n] && !cols[square.y][n]) {
                 square.val = n;
                 s.push(square);
               }
          }
      }
      
      cout << "no solution\n";
  }

  // Print the found solution for sudoku
  void print_solution() {
      size_t i = 0;
      for(size_t row = 0; row < 9; ++row) {
          for(size_t col = 0; col < 9; ++col) {
              if(board[row][col] == -1) {
                  cout << path[i].val << ' ';
                  ++i;
              } else {
                  cout << board[row][col] << ' ';
              }
          }
          cout << '\n';
      }
  }
  
};


#endif
