/* 
Name  sqrt.cpp
Author Connor Haaf
Version  1.0
Date Febuary 8, 2021
Description : Computes the sqrt of a number to a given accuracy.
Pledge : I pledge my honor that I have abided by the Stevens Honor System.
*/
#include <iostream>
#include <sstream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <math.h>
using namespace std;
double sqrt(double num, double epsilon) {

    if(num < 0) {
        return numeric_limits<double>::quiet_NaN();
    }
    if (num == 0) {
        return num;
    }
    if (num == 1) {
        return num;
    }
    
    double last_guess = 11;
    double next_guess = num;
    while ((abs(last_guess - next_guess)) > epsilon) {
        last_guess = next_guess;
        next_guess = ((last_guess + (num / next_guess)) / 2);
    }
    return next_guess;
}
int main(int argc, char* const argv[]) {
    double num, ep;
    
    if (argc > 3 || argc < 2) {
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }
    
    istringstream iss;

    iss.str(argv[1]);
    if ( !(iss >> num)) {
        cerr << "Error: Value argument must be a double." << endl;
        return 1; 
    }
    if (num < 0) {
        cerr << "nan" << endl;
        return 1;
    }
    iss.clear();
    if (argc == 3) {
        iss.str(argv[2]);
        if ( !(iss >> ep)) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1; 
        }
        if (ep <= 0) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1; 
        }
    }
    else {
        ep = 1e-7;
    }
    cout << fixed << setprecision(8) << sqrt(num, ep) << endl;
    return 0;
    

}