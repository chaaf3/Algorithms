/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Connor Haaf
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 4/2/21
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

size_t lomuto_partition(int array[], size_t left, size_t right) {
    size_t pivot, smallBoundry;
    pivot = array[left];
    smallBoundry = left;
    for (size_t i = left + 1; i <= right; i++) {
        if (array[i] < (int)pivot) {
            smallBoundry++;
            swap(array[smallBoundry], array[i]);
        }
    }
    swap(array[left], array[smallBoundry]);
    return smallBoundry;
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
    // k is the goal k'th smallest element
    size_t smallBoundry = lomuto_partition(array, left, right);
    if (smallBoundry == k - 1) {
        return array[smallBoundry];
    }
    else if (smallBoundry > k - 1) {
        return quick_select(array, left, smallBoundry-1, k);
    }
    else {
        return quick_select(array, smallBoundry+1, right, k);
    }
}

int quick_select(int array[], const size_t length, size_t k) {
    return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    // TODO - error checking k against the size of the input
    if (k > num_values) {
        cout << "Error: Cannot find smallest element ";
        cout <<  k;
        cout << " with only ";
        cout << num_values;
        if (num_values == 1) {
            cout << " value.";
            return 0;
        }
        cout << " values.";
        return 0;
    }

    // TODO - call the quick_select function and display the result
    int* array = &values[0];
    cout << "Smallest element ";
    cout << k;
    cout << ": ";
    cout << quick_select(array, num_values, k);
    return 0;
}
