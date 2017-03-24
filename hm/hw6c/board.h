#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <string>

class Board {
public:
  // CONSTRUCTOR
  Board(int w, int h);
  // ACCESSORS
  int width() const { return width_; }
  int height() const { return height_; }
  char get(int y, int x) const; 
  bool getflag(int y, int x) const;

  // MODIFIER
  void set(int x, int y, int v);
  void setflagtrue(int y, int x){ flag[y][x]=true; }
  void setflagfalse(int y, int x){ flag[y][x]=false; }

private:
  // REPRESENTATION
  int height_;
  int width_;
  std::vector<int> value;
  std::vector<std::vector<char> > board;
  std::vector<std::vector<bool> > flag;
};

// PRINT FUNCTION
std::ostream& operator<<(std::ostream& ostr, const Board &b);

// SORT FUNCTION
bool cmp (const Board& board);

#endif
