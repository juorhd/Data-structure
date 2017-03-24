//
//  main.cpp
//  quadratic
//
//  Created by 胡栋 on 8/31/16.
//  Copyright © 2016 Rpi. All rights reserved.
//

#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function


// Returns true if the candidate root is indeed a root of the polynomial a*x*x + b*x + c = 0
bool check_root(int a, int b, int c, float root) {
    // plug the value into the formula
    float check = a * root * root + b * root + c;
    // see if the absolute value is zero (within a small tolerance)
    if (fabs(check) > 0.0001) {
        std::cerr << "ERROR:  " << root << " is not a root of this formula." << std::endl;
        return false;
    } else {
        return true;
    }
}

/* Use the quadratic formula to find the two real roots of polynomial.   Returns
 true if the roots are real, returns false if the roots are imaginary.  If the roots
 are real, they are returned through the reference parameters root_pos and root_neg. */
bool find_roots(int a, int b, int c, float &root_pos, float &root_neg) {
    // compute the quantity under the radical of the quadratic formula
    int radical = b*b - 4*a*c;
    // if the radical is negative, the roots are imaginary
    if (radical < 0) {
        std::cerr << "ERROR:  Imaginary roots" << std::endl;
        return false;
    }
    float sqrt_radical = sqrt(radical);
    // compute the two roots
    root_pos = (-b + sqrt_radical) / (2*a);
    root_neg = (-b - sqrt_radical) / (2*a); 
    return true;
}

int main() {
    // We will loop until we are given a polynomial with real roots
        std::cout << "Enter 3 integer coefficients to a quadratic function: x*x + b*x + c = 0" << std::endl;
        int b_array[5], c_array[5];
        for (int i=0; i<5; i++)
            std::cin>>b_array[i]>>c_array[i];
        // create a place to store the roots
        float root_1, root_2;
        for (int i=0; i<5; i++)
        {
            bool success = find_roots(1,b_array[i],c_array[i], root_1,root_2);
            // If the polynomial has imaginary roots, skip the rest of this loop and start over
            if (!success) continue;
            std::cout << "The roots are: " << root_1 << " and " << root_2 << std::endl;
            // Check our work...
            if (check_root(1,b_array[i],c_array[i], root_1) && check_root(1,b_array[i],c_array[i], root_2)) {
                // Verified roots, break out of the while loop
                continue;
            } else
                std::cerr << "ERROR:  Unable to verify one or both roots." << std::endl;
                // if the program has an error, we choose to exit with a
                // non-zero error code
            
        }
        // by convention, main should return zero when the program finishes normally
        return 0;
}