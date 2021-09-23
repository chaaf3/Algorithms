/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Connor Haaf and Nick Cali
 * Date        : 3/8/21
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;


vector< vector<int> > get_ways(int num_stairs) {
    vector< vector <int> > ways;
    vector<int> emptyAdder;
    if (num_stairs <= 0) {
        ways.push_back(emptyAdder);
    }else {
        for (int i = 1; i < 4; i++) {
            if (num_stairs >= i) {
                vector< vector <int> > result = get_ways(num_stairs - i);
                for (int j = 0; j < (int)result.size(); j++) {
                    result[j].insert(result[j].begin(), i);
                }
                ways.insert(ways.end(), result.begin(), result.end());
            }
        }
    }
    return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    cout << ways.size() << " ways to climb " << ways[0].size() << " stairs." << endl;
    for (int i = 0; i < (int)ways.size(); i++) {
        if ((int)ways.size() >= 10 && i < 9) {
            cout << " ";
        }
        cout << i + 1 << ". [";
        for (int j = 0; j < (int)ways[i].size(); j++) {
            cout << ways[i][j];
            if (j != (int)ways[i].size() - 1){
                cout << ", ";
            }
        }
        cout << "]";
        if (i != (int)ways.size() - 1) {
            cout << endl;
        }
    }
}

int main(int argc, char * const argv[]) {
    if (argc <= 1) {
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    else if (argc > 2) {
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    int stairs;
    istringstream iss;
    iss.str(argv[1]);
     if ( !(iss >> stairs)) {
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    else if (stairs <= 0) {
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    else if (stairs == 1) {
        cout <<"1 way to climb 1 stair." << endl;
        cout << "1. [1]" << endl;
        return 1;
    }
    else {
        vector<vector<int>> answer = get_ways(stairs);
        display_ways(answer);
        return 1;
    }
}