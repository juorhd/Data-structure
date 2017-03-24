void Searchsolution(Board &board, vector<Point> &P, vector<vector<Point> > &solution, bool &find, int &count, bool &all){
  if ( !all && find ) return;
  if (P.size()==0) {                //if find that means all the points in the set have been used
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
  while ( ptrn!=P.end() && (*ptrn).value_() == chr ){
  	int xxn = (*ptrn).x_();
  	int yyn = (*ptrn).y_();
  	if (abs(xx-xxn)+abs(yy-yyn)>len || (abs(xx-xxn)+abs(yy-yyn)+len)%2!=0 ){
  	  ptrn++;
  	  continue;
  }
  bool findpath=false;
  vector<Point> path;    //vector to store point
  vector<vector<Point> > pathset;  //vector to store path
  vector<Board> boardset; //vector to store board
  Pathsearch(board, boardset, yy, xx , xxn, yyn, len, findpath, path, pathset, all);
  if (findpath){
    for (int j=0; j<pathset.size(); ++j){ //for each path stored in board, we search for next point.
      solution.push_back(pathset[j]);
      vector<Point>::iterator ptr_tmp=ptr;
      vector<Point>::iterator ptrn_tmp=ptrn;
      Point p1 = *ptr;
      Point p2 = *prtn;
      P.erase(ptr);
      P.erase(ptrn);
      Searchsolution(Board &board, vector<Point> &P, vector<vector<Point> > &solution, bool &find, int &count, bool &all)
      if ( !all && find ) return;
      solution.pop_back();   //pop the path for future search
      P.insert(ptr_tmp, p1);
      P.insert(ptrn_tmp, p2);
  }
}




