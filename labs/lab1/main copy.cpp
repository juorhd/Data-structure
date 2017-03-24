//
//  main.cpp
//  checkpoint 3
//
//  Created by 胡栋 on 8/31/16.
//  Copyright © 2016 Rpi. All rights reserved.
//

#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function
using namespace std;


int main()
{
    int number;
    float a[101];
    float sum=0, average;
    cin>>number;
    for (int i=1; i<=number; i++)
    {
        cin>>a[i]; sum+=a[i];
    }
    average=sum/number; cout<<average<<" ";
    for (int i=1; i<=number; i++)
        if (a[i] < average )
            cout<<a[i]<<" ";
    return 0;
}
