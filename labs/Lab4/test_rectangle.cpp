#include <iostream>
#include "Rectangle.h"
using namespace std;

int main(){
	vector<Point2D> points, shared_points;
	Point2D one_point;

	one_point.set(1, 1);
	points.push_back(one_point);
	one_point.set(6, 5);
	points.push_back(one_point);

	one_point.set(3, 1.5);
	points.push_back(one_point);
	one_point.set(8.5, 9);
	points.push_back(one_point);

	one_point.set(3.5, 2);
	points.push_back(one_point);
	one_point.set(5.2, 4.9);
	points.push_back(one_point);
	one_point.set(7.2, 8);
	points.push_back(one_point);
	one_point.set(0.9, 5);
	points.push_back(one_point);

	Rectangle rectangle1(points[0], points[1]);
	Rectangle rectangle2(points[2], points[3]);
	for (int i=4; i<=7; ++i)	
		rectangle1.add_point(points[i]), rectangle2.add_point(points[i]);
	print_rectangle(rectangle1);
	print_rectangle(rectangle2);
	shared_points=points_in_both(rectangle1, rectangle2);
	cout<<"shared_points"<<endl;
	for (int i=0; i<shared_points.size(); ++i)
		cout<<shared_points[i].x()<<','<<shared_points[i].y()<<endl;
	return 0;
}