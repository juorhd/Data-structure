//
//  main.cpp
//  lab9
//
//  Created by 623 on 15/4/1.
//  Copyright (c) 2015年 623. All rights reserved.
//

#include <iostream>
#include <map>

bool sortMap(const std::pair<int, int> &p1, const std::pair<int, int> &p2)
{
    return p1.second > p2.second;
}

int main()
{
    std::cout << "Check1: How many numbers? " << std::endl;
    int n, num;
    std::cin >> n;
    std::map<int, int> counters;
    std::cout << "Enter the numbers: " << std::endl;
    for (int i=0; i<n; ++i)
    {
        std::cin >> num;
        ++counters[num];
    }
    
    std::cout << "Check2: How many numbers? " << std::endl;
    int n, num;
    std::cin >> n;
    std::map<int, int> counters;
    std::cout << "Enter the numbers: " << std::endl;
    for (int i=0; i<n; ++i)
    {
        std::cin >> num;
        if (counters.find(num) == counters.end())
            counters.insert(std::make_pair(num, 1));
        else counters.find(num)->second++;
    }
    
    
    std::map<int, int>::iterator it;
    //sort(counters.begin(), counters.end(), sortMap);
    
    int max = 1;
    for (it = counters.begin(); it != counters.end(); ++it)
    {
        if (it->second > max) max = it->second;
    }
    
    std::cout << "Mode(s): ";
    for (it = counters.begin(); it != counters.end(); ++it)
    {
        if (it->second == max) std::cout << it->first << ", ";
    }
}
