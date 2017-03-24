#include <iostream>
#include <map>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
	std::ifstream in_str(argv[1]);
	int s;
	std::map<int, int> counters;
	int tmp;

	while(in_str >> s) {
		if (counters.find(s) == counters.end() )
			counters.insert(std::make_pair(s, 1));
		else {
			tmp = (counters.find(s))->second + 1;
			counters.erase(counters.find(s));
			counters.insert(std::make_pair(s, tmp));
		}
	}

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