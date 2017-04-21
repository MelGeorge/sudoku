# Sudoku Solver

### Written by Mel George. Makefile stolen/ modified from University of Michigan, [EECS 281 Advanced Makefile ](https://gitlab.eecs.umich.edu/eecs281/eecs281_project0.git)

### To use this project as-is:
> 1. Make the executable. Makefile is provided, so simply use: "make"
> 2. Create an input file with your sudoku board. Use one line per file line, spaces between each number, and _ for spaces that are unfilled. Or, use one of the two provided sudoku boards, board.txt & board2.txt .
> 3. Run. Your sudoku board will be read from cin, so file redirection is recommended: "./sudoku < my_input_file.txt"
> 4. Never worry about solving your own sudoku again!

#### For example,
![Run](https://raw.githubusercontent.com/MelGeorge/sudoku/master/screenshots/run_sudoku.png)

#### An example of a well-formed input file:
![Input](https://raw.githubusercontent.com/MelGeorge/sudoku/master/screenshots/input_file.png)

### To use the sudoku solver in your own project:
> 1. Use only Sudoku.h & Sudoku.cpp
> 2. Create a sudoku board (a vector< vector < int > > containing integers 1 - 9 in completed spaces & -1 in unfilled spaces).
> 3. Construct sudoku objects and solve:
> > vector< vector < int > > board;

> > // fill board

> > Sudoku sudoku_instance(board);

> > bool solved = sudoku_instance.solve();

> > if(solved) { /* iterate through solved board & print? */ }

### Backtracking:
> Sudoku has been solved here via a backtracking algorithm. The algorithm tries a number in the first empty space, then a number in the next empty space, then the next, occasionally finding that there are no possible ways to solve the whole puzzle after making these decisions. When it is discovered that no possibilities remain, the search returns to an earlier decision  point where something could have been done differently. Eventually, if the puzzle is solvable, this depth first search algorithm will lead to a solution.

#### Uncomment this for some fun!
![Comment](https://raw.githubusercontent.com/MelGeorge/sudoku/master/screenshots/backtracking_comment.png)

> For some fun, uncomment this bit at the bottom of Sudoku.cpp and see the backtracking algorithm at work!

#### See backtracking at work.
> The positive numbers represent all of the numbers being tried in the unused spaces, while the -1's represent the unfilled numbers where decisions have not been made yet. Notice that sometimes we make decisions, realize that they were bad, and backtrack to a point where there were more -1's so we can try to make better choices!

![Backtracking](https://raw.githubusercontent.com/MelGeorge/sudoku/master/screenshots/backtracking.png)

