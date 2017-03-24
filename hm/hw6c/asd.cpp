
  vector<Point>::iterator p1=ptr;
  while ( (*p1).value_()==chr ){
    while ( !(*p1).visit_() && p1+1!=P.end() && (*(p1+1)).value_()==chr ) p1++;
    if ( p1==P.end() || (*p1).value_()!=chr ) break;
    bool findmatch=false;
    vector<Point>::iterator p2=ptr;
    while ( (*p2).value_()==chr ){
      while ( !(*p2).visit_() && p2+1!=P.end() && (*(p2+1)).value_()==chr ) p2++;
      if ( p2==P.end() || (*p2).value_()!=chr ) break;
      if ( p1==p2 ){
        p2++;
        continue;
      }
      if ( abs( (*p1).x_()-(*p2).x_() )+abs( (*p1).y_()-(*p2).y_() )<=len 
        && (abs( (*p1).x_()-(*p2).x_() )+abs( (*p1).y_()-(*p2).y_() ) + len)%2 == 0 )
        findmatch = true;
      if (findmatch) break;
      if ( (p2+1)!=P.end() && (*(p2+1)).value_()==chr ) p2++;

    }
    if (!findmatch) return;
    if ( (p1+1)!=P.end() && (*(p1+1)).value_()==chr ) p1++;
      else break;
  }