#include <cassert>
#include <iostream>

#include "board.h"
using namespace std;

// CONSTRUCTOR
Board::Board(int w, int h) {
  height_ = h;
  width_ = w;
  board = vector<vector<char> >(h,vector<char>(w,' '));
  flag = vector<vector<bool> >(h,vector<bool>(w,true));
}

// ACCESSOR
char Board::get(int y, int x) const { 
  assert (y >= 0 && board.size());
  assert (x >= 0 && board[y].size());
  return board[y][x]; 
}

bool Board::getflag(int y, int x) const {
  if ( y>=height_ || x>=width_ || y<0 || x<0 ) return false;
  return flag[y][x];
}


// helper function for set
char IntToChar(int v) {
  assert (v >= 1 && v <= 30);
  if (v <= 9) {
    return char('0' + v);
  } else {
    // A = 10
    // B = 11
    // C = 12
    // etc
    return char('A' + (v-10));
  }
}


// MODIFIER
void Board::set(int x, int y, int v) {
  assert (x < width_);
  assert (y < height_);
  assert(board[y][x] == ' ');
  board[y][x] = IntToChar(v);
}

ostream& operator<<(ostream& ostr, const Board &b) {
  // top frame
  ostr << "+" << string(b.width(),'-') << "+" << endl;
  for (int y = b.height()-1; y >= 0; y--) {
    ostr << "|";
    // each row
    for (int x = 0; x < b.width(); x++) {
      ostr << b.get(y,x);
    }
    ostr << "|" << endl;
  }
  // bottom frame
  ostr << "+" << string(b.width(),'-') << "+" << endl;
  return ostr;
}











