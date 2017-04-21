#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>
#include <unordered_map>

using namespace std;

class Sudoku {
public:

    // Requires: pre-made sudoku board-- a vector<vector<int>>
    // with numbers 1-9 in completed squares and -1 in squares that
    // are unfilled.
    // Modifies: Creates a reference to your sudoku board
    Sudoku(vector<vector<int>> &board);
    
    // Requires: sudoku board constructed as above
    // Modifies: sudoku board, if a solution is found
    // Effects: solves your sudoku board, if a solution
    // is possible. Returns true if a solution was
    // found & false if your board is unsolvable.
    bool solve();
    
private:

    struct Square {
        Square(size_t x, size_t y, size_t i, int v);
        size_t x, y, index;
        int val;
    };
    
    struct Blocks {
        vector<unordered_map<int, bool> > v;
        size_t location(size_t row, size_t col);
        unordered_map<int, bool>& hash(size_t r, size_t c);
    };
    
    bool solvable;
    vector<vector<int>> &board;
    vector<unordered_map<int, bool> > rows;
    vector<unordered_map<int, bool> > cols;
    Blocks blocks;
    vector<Square> path;
    size_t unfilled = 0;
    
    void fill_solution();
};

#endif