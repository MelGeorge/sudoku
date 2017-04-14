#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include "Sudoku.h"
#include <fstream>

using namespace std;

int main() {
  cout << "Welcome to Sudoku Solver! Stuck?\n";
  
  ifstream infile;
  infile.open("board.txt");
  
  ofstream outfile;
  outfile.open("out.txt");
  Sudoku sudoku(infile, outfile);
  
  sudoku.solve();
  
  infile.close();
  outfile.close();
  
  return 0;
}