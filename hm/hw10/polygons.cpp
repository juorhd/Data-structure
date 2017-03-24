#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "polygons.h"
#include "utilities.h"
using namespace std;

Polygon::Polygon ( const string& Polygon_name, const vector<Point>& pts ) {
  name = Polygon_name;
  vertices = pts;
}

string Polygon::getName() const { return name; }

bool Polygon::HasAllEqualSides() const {
  //set the last side of the polygon as the standard side
  double len = DistanceBetween( vertices[vertices.size()-1], vertices[0] );
  for ( int i=1; i<vertices.size(); i++ ) {
    
  double len2 = DistanceBetween( vertices[i-1], vertices[i] );
  //check if each side is equal 
  if ( !( EqualSides( len, len2 )) )
    return false;
  }
  return true;
}

bool Polygon::HasAllEqualAngles() const {
  //set the last angle of the polygon as the standard angle
  double angle = Angle ( vertices[vertices.size()-2],
                        vertices[vertices.size()-1], vertices[0] );
  //compare the last two angles
  double angle2= Angle ( vertices[vertices.size()-1], vertices[0], vertices[1] );
  if ( !( EqualAngles( angle, angle2 )) )
    return false;
  for ( int i=2; i<vertices.size(); i++ ) {
    double angle3= Angle( vertices[i-2], vertices[i-1], vertices[i] );
    //check if each angle is equal 
    if ( !( EqualAngles( angle,angle3 )) )
      return false;
  }
  return true;
}

bool Polygon::HasARightAngle() const {
  //check the last two angles
  double angle = Angle ( vertices[vertices.size()-2],
                        vertices[vertices.size()-1], vertices[0] );
  if ( RightAngle( angle ))
    return true;

  angle = Angle ( vertices[vertices.size()-1], vertices[0], vertices[1] );
  if ( RightAngle( angle ))
    return true;

  for ( int i=2; i<vertices.size(); i++ ) {
    double angle = Angle( vertices[i-2], vertices[i-1], vertices[i] );
    //check all angles
    if ( RightAngle( angle ))
      return true;
  }
  return false;
}

bool Polygon::HasAnObtuseAngle() const {
  //check the last two angles
  double angle = Angle ( vertices[vertices.size()-2],
                        vertices[vertices.size()-1], vertices[0] );
  if ( ObtuseAngle( angle ))
    return true;

  angle = Angle ( vertices[vertices.size()-1], vertices[0], vertices[1] );
  if ( ObtuseAngle( angle ))
    return true;

  for ( int i=2; i<vertices.size(); i++ ) {
    double angle = Angle( vertices[i-2], vertices[i-1], vertices[i] );
    //check all angles
    if ( ObtuseAngle( angle ))
      return true;
  }
  return false;
}


bool Polygon::HasAnAcuteAngle() const {
  //check the last two angles
  double angle = Angle ( vertices[vertices.size()-2],
                        vertices[vertices.size()-1], vertices[0] );
  if ( AcuteAngle( angle ))
    return true;

  angle = Angle ( vertices[vertices.size()-1], vertices[0], vertices[1] );
  if ( AcuteAngle( angle ))
    return true;

  for ( int i=2; i<vertices.size(); i++ ) {
    double angle = Angle( vertices[i-2], vertices[i-1], vertices[i] );
    //check all angles
    if ( AcuteAngle( angle ))
      return true;
  }
  return false;
}

//helper function
bool Polygon::Convex() const {
  //check the last two angles
  double angle = Angle ( vertices[vertices.size()-2],
                        vertices[vertices.size()-1], vertices[0] );
  if ( ReflexAngle( angle ))
	  return false;

  angle = Angle ( vertices[vertices.size()-1], vertices[0], vertices[1] );
  if ( ReflexAngle( angle ))
	  return false;

  for ( int i=2; i<vertices.size(); i++ ) {
	  double angle = Angle( vertices[i-2], vertices[i-1], vertices[i] );
	  //check all angles
    if ( ReflexAngle( angle ))
	    return false;
  }
  return true;
}


bool Polygon::IsConvex() const {
  return this->Convex();
}

bool Polygon::IsConcave() const {
  return ( !( this->Convex()) );
}

//below are the constructors for all the classes
Triangle::Triangle ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 3 )
	  throw 0;
  name = Polygon_name;
  vertices = pts;    
}

IsoscelesTriangle::IsoscelesTriangle ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 3 )
	  throw 0;
  
  double s1 = DistanceBetween( pts[0], pts[1] );
  double s2 = DistanceBetween( pts[0], pts[2] );
  double s3 = DistanceBetween( pts[1], pts[2] );
  
  if ( !( EqualSides( s1,s2 ) || EqualSides( s1,s3 ) || EqualSides( s2,s3 )) )
	  throw 0;
  name = Polygon_name;
  vertices = pts;
}

RightTriangle::RightTriangle ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 3 )
	  throw 0;//throw if not triangle
  
  double a1 = Angle( pts[2],pts[0],pts[1] );
  double a2 = Angle( pts[0],pts[1],pts[2] );
  double a3 = Angle( pts[1],pts[2],pts[0] );
  
  if ( !( ( RightAngle( a1 )) || ( RightAngle( a2 )) || ( RightAngle( a3 )) ))
	  throw 0;// if no right angle
  name = Polygon_name;
  vertices = pts;
}

IsoscelesRightTriangle::IsoscelesRightTriangle ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 3 )
	  throw 0;//throw if not triangle
  
  double s1 = DistanceBetween( pts[0], pts[1] );
  double s2 = DistanceBetween( pts[0], pts[2] );
  double s3 = DistanceBetween( pts[1], pts[2] );
  
  if ( !( EqualSides( s1,s2 ) || EqualSides( s1,s3 ) || EqualSides( s2,s3 )) )
	  throw 0;//throw if none of the two edges are equal
  
  double a1 = Angle( pts[2],pts[0],pts[1] );
  double a2 = Angle( pts[0],pts[1],pts[2] );
  double a3 = Angle( pts[1],pts[2],pts[0] );
  
  if ( !( ( RightAngle( a1 )) || ( RightAngle( a2 )) || ( RightAngle( a3 )) ))
	  throw 0;// if no right angle
  name = Polygon_name;
  vertices = pts;
}

ObtuseTriangle::ObtuseTriangle ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 3 )
	  throw 0;//throw if not triangle
  
  double a1 = Angle( pts[2],pts[0],pts[1] );
  double a2 = Angle( pts[0],pts[1],pts[2] );
  double a3 = Angle( pts[1],pts[2],pts[0] );
  
  if ( !( ( ObtuseAngle( a1 )) || ( ObtuseAngle( a2 )) || ( ObtuseAngle( a3 )) ))
	  throw 0;// throw if no obtuse angle
  name = Polygon_name;
  vertices = pts;
}

IsoscelesObtuseTriangle::IsoscelesObtuseTriangle ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 3 )
	  throw 0;//throw if not triangle
  
  double s1 = DistanceBetween( pts[0], pts[1] );
  double s2 = DistanceBetween( pts[0], pts[2] );
  double s3 = DistanceBetween( pts[1], pts[2] );
  
  if ( !( EqualSides( s1,s2 ) || EqualSides( s1,s3 ) || EqualSides( s2,s3 )) )
	  throw 0;//throw if none of the two edges are equal
  
  double a1 = Angle( pts[2],pts[0],pts[1] );
  double a2 = Angle( pts[0],pts[1],pts[2] );
  double a3 = Angle( pts[1],pts[2],pts[0] );
  
  if ( !( ( ObtuseAngle( a1 )) || ( ObtuseAngle( a2 )) || ( ObtuseAngle( a3 )) ))
	  throw 0;//throw if no obtuse angle
  name = Polygon_name;
  vertices = pts;
}

EquilateralTriangle::EquilateralTriangle ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 3 )
	  throw 0;//throw if not triangle
  
  double s1 = DistanceBetween( pts[0], pts[1] );
  double s2 = DistanceBetween( pts[0], pts[2] );
  double s3 = DistanceBetween( pts[1], pts[2] );
  
  if ( !( EqualSides( s1,s2 ) && EqualSides( s1,s3 )) ) 
	  throw 0;//throw if the sides are not all equal
  name = Polygon_name;
  vertices = pts;
}

Quadrilateral::Quadrilateral ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 4 )
	  throw 0;//throw if not quad	
  name = Polygon_name;
  vertices = pts;
}

Trapezoid::Trapezoid ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 4 )
	  throw 0;//throw if not quad

  Vector a( pts[0],pts[1] );
  Vector b( pts[1],pts[2] );
  Vector c( pts[2],pts[3] );
  Vector d( pts[3],pts[0] );

  if ( !( Parallel( a,c ) || Parallel( b,d )) )
	  throw 0;//at least two sides parallel
  name = Polygon_name;
  vertices = pts;
}

Kite::Kite ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 4 )
	  throw 0;//throw if not quad

  double s1 = DistanceBetween( pts[0], pts[1] );
  double s2 = DistanceBetween( pts[1], pts[2] );
  double s3 = DistanceBetween( pts[2], pts[3] );
  double s4 = DistanceBetween( pts[3], pts[0] );

  if ( !( ( ( s1==s2 ) && ( s3==s4 )) || ( ( s2==s3 ) && ( s1==s4 )) ))
	  throw 0;//two contiguous sides equal
  name = Polygon_name;
  vertices = pts;
}

Arrow::Arrow ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 4 )
	  throw 0;//throw if not quad

  double s1 = DistanceBetween( pts[0], pts[1] );
  double s2 = DistanceBetween( pts[1], pts[2] );
  double s3 = DistanceBetween( pts[2], pts[3] );
  double s4 = DistanceBetween( pts[3], pts[0] );

  if ( !( ( ( s1==s2 ) && ( s3==s4 )) || ( ( s2==s3 ) && ( s1==s4 )) ))
	  throw 0;//two contiguous sides equal

  double a1 = Angle( pts[3],pts[0],pts[1] );
  double a2 = Angle( pts[0],pts[1],pts[2] );
  double a3 = Angle( pts[1],pts[2],pts[3] );
  double a4 = Angle( pts[2],pts[3],pts[0] );

  if ( !( ReflexAngle( a1 ) || ReflexAngle( a2 ) || ReflexAngle( a3 ) || ReflexAngle( a4 )) )
	  throw 0;//arrow has an angle larger than 180
  name = Polygon_name;
  vertices = pts;
}

Parallelogram::Parallelogram ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 4 )
	  throw 0;//throw if not quad	

  Vector a( pts[0],pts[1] );
  Vector b( pts[1],pts[2] );
  Vector c( pts[2],pts[3] );
  Vector d( pts[3],pts[0] );

  if ( !( Parallel( a,c ) && Parallel( b,d )) )
	  throw 0;//two sides parallel
  name = Polygon_name;
  vertices = pts;
}

IsoscelesTrapezoid::IsoscelesTrapezoid ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 4 )
	throw 0;//throw if not quad	

  double s1 = DistanceBetween( pts[0], pts[1] );
  double s2 = DistanceBetween( pts[1], pts[2] );
  double s3 = DistanceBetween( pts[2], pts[3] );
  double s4 = DistanceBetween( pts[3], pts[0] );

  if ( !( ( ( s1==s3 ) && ( s2!=s4 )) || ( ( s2==s4 ) && ( s1!=s3 )) ))
	  throw 0;//one of the two pairs of opposite sides should be equal
  name = Polygon_name;
  vertices = pts;
}

Rhombus::Rhombus ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 4 )
	  throw 0;//throw if not quad	

  double s1 = DistanceBetween( pts[0], pts[1] );
  double s2 = DistanceBetween( pts[1], pts[2] );
  double s3 = DistanceBetween( pts[2], pts[3] );
  double s4 = DistanceBetween( pts[3], pts[0] );

  if ( !( EqualSides( s1,s2 ) && EqualSides( s1,s3 ) && ( EqualSides( s1,s4 )) )) 
	  throw 0;//throw if the sides are not all equal
  name = Polygon_name;
  vertices = pts;
}

Rectangle::Rectangle ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 4 )
	  throw 0;//throw if not quad

  double a1 = Angle( pts[3],pts[0],pts[1] );
  double a2 = Angle( pts[0],pts[1],pts[2] );
  double a3 = Angle( pts[1],pts[2],pts[3] );
  double a4 = Angle( pts[2],pts[3],pts[0] );

  if ( !( ( RightAngle( a1 )) && ( RightAngle( a2 )) && ( RightAngle( a3 )) && ( RightAngle( a4 )) ))
	  throw 0;//if angles not right
  name = Polygon_name;
  vertices = pts;
}

Square::Square ( const string& Polygon_name, const vector<Point>& pts ){
  if ( pts.size() != 4 )
	  throw 0;//throw if not quad

  double s1 = DistanceBetween( pts[0], pts[1] );
  double s2 = DistanceBetween( pts[1], pts[2] );
  double s3 = DistanceBetween( pts[2], pts[3] );
  double s4 = DistanceBetween( pts[3], pts[0] );

  if ( !( EqualSides( s1,s2 ) && EqualSides( s1,s3 ) && ( EqualSides( s1,s4 )) )) 
	  throw 0;//throw if the sides are not all equal

  double a1 = Angle( pts[3],pts[0],pts[1] );
  double a2 = Angle( pts[0],pts[1],pts[2] );
  double a3 = Angle( pts[1],pts[2],pts[3] );
  double a4 = Angle( pts[2],pts[3],pts[0] );

  if ( !( ( RightAngle( a1 )) && ( RightAngle( a2 )) && ( RightAngle( a3 )) && ( RightAngle( a4 )) ))
	  throw 0;//if angles not right
  name = Polygon_name;
  vertices = pts;
}
