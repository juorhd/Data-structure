#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unistd.h>

#include "board.h"
using namespace std;

int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};  

class Point{    //a class for storing the numbers on the board
public:
  Point(int y1, int x1): x(x1), y(y1), value(' ') {}
	Point(int y1, int x1, char chr): x(x1), y(y1), value(chr) {}
	int x_()const{return x;}
	int y_()const{return y;}
  char value_()const{return value;}

private:
	int x,y;
  char value;
};

int CharToInt(char v){    // a function to change char to int
  if (v <= '9' && v >= '0')
    return int(v - '0');
  else return int(v - 'A' + 10);
}

bool sortbysize(const vector<Point> &p1, const vector<Point> &p2){  // a function in sort to sort the stored path in ascending size
	if ( p1.size() == p2.size() ){
		if ( p1[0].x_() == p2[0].x_() )
			return p1[0].y_() < p2[0].y_();
		return p1[0].x_() < p2[0].x_();
	}
 	return p1.size() < p2.size(); 
}

bool sortbyvalue(const Point &p1, const Point &p2){ // a function in sort to sort the stored point in ascending order
  if (p1.value_() == p2.value_()){
    if ( p1.x_() == p2.x_() )
      return p1.y_() < p2.y_();
    return p1.x_() < p2.x_();
  }
  return p1.value_()<p2.value_(); 
}


void printsolution(vector<vector<Point> > &points, Board &board){  //print function
  sort(points.begin(), points.end(), sortbysize);
  cout<<"Solution:"<<endl;
  for(int i=0; i<points.size(); ++i){
    for( vector<Point>::iterator ri=points[i].begin(); ri!=points[i].end(); ++ri)
      cout<<'('<<(*ri).x_()<<','<<(*ri).y_()<<')';
    cout<<endl;
  }
    // PRINT FUNCTION
    cout << "+" << string(board.width(),'-') << "+" << endl;
    for (int y = board.height()-1; y >= 0; y--) {
      cout << "|";
      for (int x = 0; x < board.width(); x++) 
        if ( board.getflag(y,x)==false ) cout<<'X';
        else cout<<' ';
        cout << "|" << endl;
      }
    cout << "+" << string(board.width(),'-') << "+" << endl<<endl;
}

void Pathsearch(Board &board, vector<Board> &boardset, int y1, int x1, int y2, int x2, int length, 
          bool &findpath, vector<Point> &path, vector<vector<Point> > &pathset, bool &all){
  if ( length == 0 ){         //if find that means the searchlength=0 
    findpath = true; 
    board.setflagfalse(y1,x1);   //mark the point visited
    boardset.push_back(board);
    Point point(y1, x1);
    path.push_back(point);    //add point to the path.
    pathset.push_back(path);  //add path to the pathset.
    path.pop_back();          
    board.setflagtrue(y1,x1); //mark the point unvisited for future solution
    return;
  }
  board.setflagfalse(y1, x1);
  for (int i=0; i<4; ++i){
    int xx = x1+dir[i][0];    //go for 4 directions.
    int yy = y1+dir[i][1];
    if ( board.getflag(yy, xx) && length-1>=0 && (abs(xx-x2)+abs(yy-y2)<=length-1)
          && (board.get(yy, xx)==' ' || (length==1&&yy==y2&&xx==x2)) ){  //add some limitations for future recursive search.
      Point point(y1, x1);    
      path.push_back(point);  //add point to the path.
      Pathsearch(board, boardset, yy, xx, y2, x2, length-1, findpath, path, pathset, all);
      path.pop_back();     //after recurtion, pop the point for future solution
    }
  }
  board.setflagtrue(y1, x1);    
}

void Searchsolution(Board &board, vector<Point> &P, vector<vector<Point> > &solution, bool &find, int &count, bool &all){
  if ( !all && find ) return;
  if ( P.size()==0 ) {                //if find that means all the points in the set have been used
    printsolution(solution, board);
    count++;
    find=true;
    return;
  }
  vector<Point>::iterator ptr=P.begin();
  char chr = (*ptr).value_();
  int len = CharToInt(chr)-1;
  int xx = (*ptr).x_();
  int yy = (*ptr).y_();
  vector<Point>::iterator ptrn=ptr+1;
  for (; ptrn!=P.end() && (*ptrn).value_() == chr; ptrn++){
    int xxn = (*ptrn).x_();
    int yyn = (*ptrn).y_();
    if (abs(xx-xxn)+abs(yy-yyn)>len || (abs(xx-xxn)+abs(yy-yyn)+len)%2!=0 ) continue;
    bool findpath=false;
    vector<Point> path;    //vector to store point
    vector<vector<Point> > pathset;  //vector to store path
    vector<Board> boardset; //vector to store board
    Pathsearch(board, boardset, yy, xx , yyn, xxn, len, findpath, path, pathset, all);
    if (findpath){
     Point p1((*ptr).y_(),(*ptr).x_(),(*ptr).value_());
     Point p2((*ptrn).y_(),(*ptrn).x_(),(*ptrn).value_());
     P.erase(ptrn);
     P.erase(ptr);
     for (int j=0; j<pathset.size(); ++j){ //for each path stored in board, we search for next point.
       solution.push_back(pathset[j]);
       Searchsolution(boardset[j], P, solution, find, count, all);
       if ( !all && find ) return;
       solution.pop_back();   //pop the path for future search
       }
      P.insert( ptr, p1);
      P.insert( ptrn, p2 );
    }
  }
}

int main(int argc, char* argv[]) {

  // parse the arguments
  if (argc < 2) {
    cerr << "USAGE:  " << argv[0] << " <puzzlefile>" << endl;
    cerr << "        " << argv[0] << " <puzzlefile> find_all_solutions" << endl;
    exit(0);
  }
  bool all_solutions = false;
  if (argc > 2) {
    assert (argc == 3);
    assert (string(argv[2]) == string("find_all_solutions"));
    all_solutions = true;
  }

  // open the file
  ifstream istr(argv[1]);
  if (!istr.good()) {
    cerr << "ERROR!  cannot open " << argv[1] << endl;
    exit(0);
  }

  // read the file
  string token;
  istr >> token;
  assert (token == "width");
  int width,height;
  istr >> width;
  istr >> token;
  assert (token == "height");
  istr >> height;
  assert (width > 0);
  assert (height > 0);
  int x,y,v;

  // create the board
  Board board(width,height);
  while (istr >> x >> y >> v) {
    assert (x >= 0 && x < width);
    assert (y >= 0 && y < height);
    board.set(x,y,v);
  }

  // print the original puzzle board
  cout << board << endl;
  vector<Point> pointset;
  vector<vector<Point> > solution;
  for (int i=0; i<height; ++i)
	 for (int j=0; j<width; ++j){
		 if ( board.get(i, j)!=' ' ){
      if ( board.get(i, j)=='1' ){   // 1 could only connect with itself
        Point pt(i, j, board.get(i, j));
        board.setflagfalse(i, j);
        vector<Point> path;
        path.push_back(pt);
        solution.push_back(path);
        continue;
        }
      Point pt(i, j, board.get(i, j));
      pointset.push_back(pt);
     }
	}
  sort(pointset.begin(), pointset.end(), sortbyvalue);  // sort the points by its number, from smaller to greater
  bool findsolution=false;
  int count=0;
  Searchsolution(board, pointset, solution, findsolution, count, all_solutions);
  if(all_solutions)
    if (findsolution) 
      cout<<"Found "<<count<<" solution(s)"<<endl;
  if (!findsolution) cout<<"No solutions"<<endl;
  return 0;
}



