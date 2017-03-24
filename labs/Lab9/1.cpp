#include <iostream>
#include <map>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
	std::ifstream in_str(argv[1]);
	int s;
	std::map<int, int> counters;

	while(in_str >> s)
		++counters[s];

	int max = 0;
	std::map<int, int>::const_iterator it;
	for (it = counters.begin(); it != counters.end(); ++it)
		if (it->second > max)
			max = it->second;

	for (it = counters.begin(); it != counters.end(); ++it)
		if (it->second == max)
			std::cout << it->first << ' ';
	std::cout << std::endl;

	return 0;
}