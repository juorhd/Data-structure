#include <vector>
#include <set>
#include <iostream>
#include <math.h>
#include <cassert>
#include "sudoku.h"

using std::set;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

// ======================================================
// A program to solve very simple Sudoku puzzles
// ======================================================

int main() {
    
    int size;
    while (cin >> size) {
        // Read in the board size and create an empty board
        Sudoku board(size);
        
        // Read in and set the known positions in the board
        char c;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> c;
                if (c != '.') {
                    board.Set(i,j,c-'0');
                }
            }
        }
        // The iterative solving routine
        while (1) {
            
            // Is the puzzle is already solved?
            if (board.IsSolved()) {
                cout << "\nPuzzle is solved:" << endl;
                board.Print();
                break;
            }
            
            // Is the puzzle impossible?
            if (board.Impossible()) {
                cout << "\nCannot solve this puzzle:" << endl;
                board.Print();
                break;
            }
            
            // Try to reduce the number of choices in one or more board cells
            // by propagating known values within each row, column, and quadrant
            int changed = 0;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (board.KnownValue(i,j))
                        changed += board.Propagate(i,j);
                }
            }
            
            // If nothing changed this iteration, give up
            if (changed == 0) {
                cout << "\nPuzzle is too difficult for this solver!" << endl;
                board.Print();
                break;
            }
        }
    }
}

// ======================================================

// Construct an empty board
Sudoku::Sudoku(int s) {
    // set the size
    size = s;
    quadrant_size = (int)sqrt(size);
    assert (quadrant_size*quadrant_size == s);
    
    
    // You need to finish this function!
    
    std::vector< std::set<int> > tmp;
    for (int i=0; i<s; ++i)
    {
        tmp.clear();
        for (int j=0; j<s; ++j)
        {
            std::set<int> tmp0;
            tmp0.clear();
            for (int k=0; k<s; ++k)
                tmp0.insert(k+1);
            tmp.push_back( tmp0 );
        }
        board.push_back(tmp);
    }
}

// To construct the puzzle, set the value of a particular cell
void Sudoku::Set(int i, int j, int value) {
    // make sure the value is one of the legal values
    assert (board[i][j].find(value) != board[i][j].end());
    board[i][j].clear();
    board[i][j].insert(value);
}

// Does the cell have exactly one legal value?
bool Sudoku::KnownValue(int i, int j) const {
    return (board[i][j].size() == 1);
}

// If there is exactly one number in each cell of the grid, the puzzle is solved!
bool Sudoku::IsSolved() const {
    
    
    // You need to write this function
    bool solved = true;
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            if (!KnownValue(i,j)){
                solved = false;
                break;
            }
        }
        if (solved == false) break;
    }
    return solved;
}

// If there are no legal choices in one or more cells of the grid, the puzzle is impossible
bool Sudoku::Impossible() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j].size() == 0)
                return true;
        }
    }
    return false;
}

// print out the solution
void Sudoku::Print() const {
    int solved = IsSolved();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int count = size+1;
            for (set<int>::iterator itr = board[i][j].begin(); itr != board[i][j].end(); itr++) {
                count--;
                cout << *itr;
            }
            if (!solved) {
                // if it's not solved, print out spaces to separate the values
                for (int k = 0; k < count; k++) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}


// Propagate information from this cell along columns & rows &
// within quadrant. Return the number of cells that changed.
int Sudoku::Propagate(int i, int j) {
    
    
    // You need to write this function
    int change(0);
    std::set<int>::iterator it;
    if (KnownValue(i,j)){
        it  = board[i][j].begin();
        for (int c=0; c<size; c++){
            if (c != j)
                if (board[i][c].find(*it) != board[i][c].end()){
                    change++;
                    board[i][c].erase(*it);
                }
        }
        
        for (int r=0; r<size; ++r){
            if (r != i)
                if (board[r][j].find(*it) != board[r][j].end()){
                    change++;
                    board[r][j].erase(*it);
                }
        }
        int row = (i/quadrant_size)*quadrant_size;
        int column = (j/quadrant_size)*quadrant_size;
        for (int r=row; r<row+quadrant_size; ++r){
            for (int c=column; c<column+quadrant_size; ++c)
                if (r != i && c != j)
                    if (board[r][c].find(*it) != board[r][c].end()){
                        change++;
                        board[r][c].erase(*it);
                    }
        }
        return change;
        
    }
    else return 0;
    
}