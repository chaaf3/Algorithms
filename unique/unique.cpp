/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Connor Haaf Nick Cali
 * Date        : 2/28/21
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

bool is_all_lowercase(const string &s) {
   

    for (int i = 0; i < (int)s.size(); i++) {
        // check if asci value is in a given range
        if ((int)s[i] < 97 || (int)s[i] > 122) {
        cout << "Error: String must contain only lowercase letters." << endl;
        return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    unsigned holder = 0;
    for  (int i = 0; i < (int)s.size(); i++) {
        unsigned temp = 1;
        temp = temp << ((int)s[i] - 97);
        if (holder & temp){
            cout << "Duplicate letters found.";
            return false;
        }
        holder = holder | temp;
       
    }
    cout << "All letters are unique." << endl;
    return true;
}
    // a = 97
    // a - 97 = 0 // 0 indexed a
    // b - 97 = 1 // index b
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.


int main(int argc, char * const argv[]) {

    if (argc == 0) {
        cout << "Usage: ./unique <string>";
        return 1;
    }
    if (argv[1] == NULL) {
        cerr << "Usage: ./unique <string>";
        return 1;
    }
    if (argc > 2) {
        cerr << "Usage: ./unique <string>";
        return 1;
    }
     if ((strlen(argv[1])) > 26) {
        cerr << "Duplicate letters found." << endl;
    }
    else if (is_all_lowercase(argv[1])) {
        all_unique_letters(argv[1]);
    }
    //else {
    //    is_all_lowercase(argv[1]);
    //}
   

   
    return 0;
   


    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
}