#include "Sudoku.h"
#include <iostream>
#include <stack>

using namespace std;

   // Square: representation of a square on the sudoku board.
   // x : row
   // y : column
   // index : the index in our list of unfilled spaces
   // val : the value in the space
   Sudoku::Square::Square(size_t x, size_t y, size_t i, int v)
   : x(x), y(y), index(i), val(v) {}
   
   
   // Blocks: representation of the 3x3 blocks on the sudoku board,
   // which must each contain numbers 1 - 9 exactly once.
   // Location function will take a row and column and return the 
   // 3x3 block number in which a square belongs
   size_t Sudoku::Blocks::location(size_t row, size_t col) {
       if(row < 3 && col < 3) { return 0; }
       else if(row < 3 && col < 6) { return 1; }
       else if(row < 3 && col < 9) { return 2; }
       else if(row < 6 && col < 3) { return 3; }
       else if(row < 6 && col < 6) { return 4; }
       else if(row < 6 && col < 9) { return 5; }
       else if(row < 9 && col < 3) { return 6; }
       else if(row < 9 && col < 6) { return 7; }
       else { return 8; }
   }   // "Forgive me, I'm ugly!"
   
   // Make it nicer to reference the block for a square at a
   // given row & column
   unordered_map<int, bool>& Sudoku::Blocks::hash(size_t row, size_t col) {
       return v[location(row, col)];
   }

   // Fill in the board when a solution has been found
   void Sudoku::fill_solution() {
       size_t i = 0;
       for(size_t row = 0; row < 9; ++row) {
           for(size_t col = 0; col < 9; ++col) {
               if(board[row][col] == -1) {
                   board[row][col] = path[i].val;
                   ++i;
              }
          }
      }
   }

  // Ctor -- saves a reference to your sudoku board and
  // creates hash tables with your already used values
  Sudoku::Sudoku(vector<vector<int>> &b) : solvable(true), board(b) {
      rows.resize(9);
      cols.resize(9);
      blocks.v.resize(9);

    // Make records of which rows, cols, blocks already contain
    // which numbers (hash on rows & cols & 3x3 blocks) and
    // set up the path for which we still need solutions
    int current_value;
    
    for(size_t row = 0; row < 9; ++row) {
       for(size_t col = 0; col < 9; ++col) {
           current_value = board[row][col];
          if(current_value != -1) {
             // Make sure no row/ col/ 3x3 block contains a number twice
             if(rows[row][current_value] || cols[col][current_value]
                || blocks.hash(row, col)[current_value]) {
                solvable = false;
                return;
             }
             rows[row][current_value] = true;
             cols[col][current_value] = true;
             blocks.hash(row, col)[current_value] = true;
          } else {
             path.push_back(Square(row, col, path.size(), -1));
             ++unfilled;
          }
       }
    }
    
  }
  
  // Function for finding / storing the solution using
  // a backtrackig algorithm
  bool Sudoku::solve() {
      // Did we already find that the board was unsolvable?
      if(!solvable) { return false; }
      
      // Safety check: already solved?
      if(path.size() == 0) { return true; }
      
      size_t current_index = 0; 
      Square square = path[0];
      stack<Square> s;
      
      // Add options for first open square to the search
      for(int n = 1; n < 10; ++n) {
          if(!rows[path[0].x][n] && !cols[path[0].y][n] && 
             !blocks.hash(path[0].x, path[0].y)[n]) {
              square.val = n;
              s.push(square);
          }
      }
      
      // Iteratively go through all open spaces, using a depth first search
      // and backtracking when Sudoku invariants can no longer be satisfied
      while(!s.empty()) {
          // Explore the next option for the next unfilled square
          square = s.top();
          s.pop();

          // If we have backtracked, reset all of the backtracked values to
          // false in their respective row/ col/ 3x3 block hashtables
          for(size_t i = square.index; i <= current_index; ++i) {
            rows[path[i].x][path[i].val] = false;
            cols[path[i].y][path[i].val] = false;
            blocks.hash(path[i].x, path[i].y)[path[i].val] = false;
            path[i].val = -1;
          }
          
          // Fill in the information for the path we're exploring
          path[square.index].val = square.val;
          rows[square.x][square.val] = true;
          cols[square.y][square.val] = true;
          blocks.hash(square.x, square.y)[square.val] = true;

          current_index = square.index;
          
          // Check if we've found a solution
          if(current_index == unfilled - 1) {
              fill_solution();
              return true;
          }
          
          // Add all of the possibilities for the next unfilled square
          square = path[square.index + 1];

          for(int n = 1; n < 10; ++n) {
               if(!rows[square.x][n] && !cols[square.y][n] &&
                  !blocks.hash(square.x, square.y)[n]) {
                 square.val = n;
                 s.push(square);
               }
          }
          
          // Uncomment if you want to see the backtracking
          // algorithm at work!
          
          /*for(size_t i = 0; i < path.size(); ++i) {
              cout << path[i].val << ' ';
          }
          cout << '\n';*/
      }
      
      // Search failed -- no solution possible
      return false;
  }
