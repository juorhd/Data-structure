#include <iostream>
#include <algorithm>
#include <vector>
#include "time.h"

using namespace std;

int main(){

	Time t1(11, 30, 59);
	Time t2(11, 30, 58);
	Time t3(11, 31, 00);
	Time t4(12, 30, 59);
	Time t5(12, 31, 00);
	Time t6(13, 31, 01);

	vector <Time> times;
	times.push_back(t1);
	times.push_back(t2);
	times.push_back(t3);
	times.push_back(t4);
	times.push_back(t5);
	times.push_back(t6);
	sort ( times.begin(), times.end(), IsEarlierThan );
	for (int i=0; i<times.size(); i++) times[i].PrintAmPm();

	return 0;
}
