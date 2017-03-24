#ifndef _POLYGONS_H_
#define _POLYGONS_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "utilities.h"
using namespace std;


class Polygon {
public:
  Polygon (){}
  Polygon (const string& iname, const vector<Point>& points);
  virtual ~Polygon() {}
  virtual string getName() const;
  virtual bool HasAllEqualSides() const;
  virtual bool HasAllEqualAngles() const;
  virtual bool HasARightAngle() const;
  virtual bool HasAnObtuseAngle() const;
  virtual bool HasAnAcuteAngle() const;
  virtual bool Convex() const;  
  virtual bool IsConvex() const;
  virtual bool IsConcave() const;
  
  // Representitives
  string name;
  vector<Point> vertices;
};

class Triangle: public Polygon {
public:
  Triangle (){}
  Triangle (const string& iname, const vector<Point>& points);
};

class IsoscelesTriangle: virtual public Triangle {
public:
  IsoscelesTriangle (){} 
  IsoscelesTriangle (const string& iname, const vector<Point>& points);
};

class RightTriangle: virtual public Triangle {
public:
  RightTriangle (){}
  RightTriangle (const string& iname, const vector<Point>& points);
};

class IsoscelesRightTriangle: public RightTriangle, public IsoscelesTriangle {
public:
  IsoscelesRightTriangle (){}
  IsoscelesRightTriangle (const string& iname, const vector<Point>& points);
};

class ObtuseTriangle: virtual public Triangle {
public:
  ObtuseTriangle (){}
  ObtuseTriangle (const string& iname, const vector<Point>& points);
};

class IsoscelesObtuseTriangle: public ObtuseTriangle, public IsoscelesTriangle {
public:
  IsoscelesObtuseTriangle (){}
  IsoscelesObtuseTriangle (const string& iname, const vector<Point>& points);
};

class EquilateralTriangle: public IsoscelesTriangle {
public:
  EquilateralTriangle (){}
  EquilateralTriangle (const string& iname, const vector<Point>& points);
};

class Quadrilateral: public Polygon {
public:
  Quadrilateral (){}
  Quadrilateral (const string& iname, const vector<Point>& points);
};

class Trapezoid: virtual public Quadrilateral {
public:
  Trapezoid (){}
  Trapezoid (const string& iname, const vector<Point>& points);
};

class Kite: virtual public Quadrilateral {
public:
  Kite (){}
  Kite (const string& iname, const vector<Point>& points);
};

class Arrow: public Quadrilateral {
public:
  Arrow (){}
  Arrow (const string& iname, const vector<Point>& points);
};

class Parallelogram: virtual public Trapezoid {
public:
  Parallelogram (){}
  Parallelogram (const string& iname, const vector<Point>& points);
};

class IsoscelesTrapezoid: virtual public Trapezoid {
public:
  IsoscelesTrapezoid (){}
  IsoscelesTrapezoid (const string& iname, const vector<Point>& points);
};

class Rhombus: public Kite, virtual public Parallelogram {
public:
  Rhombus (){}
  Rhombus (const string& iname, const vector<Point>& points);
};

class Rectangle: public IsoscelesTrapezoid, virtual public Parallelogram {
public:
  Rectangle (){}
  Rectangle (const string& iname, const vector<Point>& points);
};

class Square: public Rectangle, public Rhombus {
public:
  Square (){}
  Square (const string& iname, const vector<Point>& points);
};

#endif