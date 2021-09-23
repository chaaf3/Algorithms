/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Connor Haaf and Nicholas Cali
 * Version     : 1.0
 * Date        : 4/27/2021
 * Description : Dynamic programming solution to max sum descent problem.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <climits>

using namespace std;

const char DELIMITER = ' ';

int **values, // This is your 2D array of values, read from the file.
    **sums;   // This is your 2D array of partial sums, used in DP.

int num_rows; // num_rows tells you how many rows the 2D array has.
              // The first row has 1 column, the second row has 2 columns, and
              // so on...
int maxSum;
/**
 * Displays the 2D array of values read from the file in the format of a table.
 */

void display_table() {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < i+1; j++) {
            if (values[i][j] <= 9) {
                if (j != 0) {
                    cout << "  " << values[i][j];
                    }
                else {
                    cout << " " << values[i][j];
                }
            }
            else {
                if (j != 0) {
                    cout << " " << values[i][j];
                }
                else {
                    cout << values[i][j];
                }
            }

        }
        cout << endl;
    }
}

/**
 * Returns the maximum sum possible in the triangle of values.
 * By starting at the top of the triangle and moving to adjacent numbers on the
 * row below, this function uses dynamic programming to build up another table
 * of partial sums.
 */
int compute_max_sum() {
    //fills bottm row of sums
    //up and left can be accessed without seg-fault
    if (num_rows == 0) {
        return 0;
    }
    else if (num_rows == 1) {
        return values[0][0];
    }
    sums[0][0] = values[0][0];
    for (int i = 1; i < num_rows; i++) {
        for (int j = 0; j < i+1; j++) {
            if (j==i) {
                sums[i][j] = values[i][j] + sums[i-1][j-1];
            }
            else if (j == 0) {
                sums[i][j] = values[i][j] + sums[i-1][j];
            }
            else if (sums[i-1][j-1] >= sums[i-1][j]) {
                sums[i][j] = values[i][j] + sums[i-1][j-1];
            }
            else {
                sums[i][j] = values[i][j] + sums[i-1][j];
            }
        }
    }
    maxSum = INT_MIN;

    for (int i = 0; i < num_rows; i++) {
        if (sums[num_rows - 1][i] > maxSum) {
            maxSum = sums[num_rows - 1][i];
        }
    }

    // Populate the 2D array of partial sums. It should still work even if
    // num_rows is 0 (i.e. the file was blank).

    // Loop over the last row to find the max sum.

    // Return the max sum.
    return maxSum;
}

/**
 * Returns a vector of ints with the values from the top to the bottom of the
 * triangle that comprise the maximum sum.
 */
vector<int> backtrack_solution() {
    vector<int> solution;
    stack<int> st;
    if (num_rows == 0) {
        return{};
    
    }else if (num_rows == 1){
        return {values[0][0]};
    }

    int jCoord;
    for (int j = 0; j < num_rows; j++) {
        if (sums[num_rows - 1][j] == maxSum) {
            jCoord = j;
        }
    }
    st.push(values[num_rows-1][jCoord]);
    for (int i = num_rows - 1; i > 0; i--) {
        if (jCoord == num_rows - 1) {
            st.push(values[i-1][jCoord]);
        }
        else if (jCoord == i) {
            st.push(values[i-1][jCoord-1]);
            jCoord--;
        }
        else if (sums[i-1][jCoord-1] >= sums[i-1][jCoord]){
            st.push(values[i-1][jCoord-1]);
            jCoord--;
        }
        else {
            st.push(values[i-1][jCoord]);
        }
    }
    for (int i = 0; i < num_rows; i++) {
        solution.push_back(st.top());
        st.pop();
    }

    reverse(solution.begin(), solution.end());
    return solution;
}

/**
 * Reads the contents of the file into the global 2D array 'values'. If
 * successful, the function also allocates memory for the 2D array 'sums'.
 */
bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "'." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while (getline(input_file, line)) {
            data.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    num_rows = data.size();
    string holder;
    sums = new int*[num_rows];
    values = new int*[num_rows];
    //takes us through all strings(lines) in file
    for (int i = 0; i < num_rows; i++) {
        holder = "";
        values[i] = new int[i+1];
        sums[i] = new int[i+1];
        int k = 0;
        for (int j = 0; j < i+1; j++) {
            // j is how many ints in a row
            holder = "";
            //k is for how many digits in a number
            while (data[i][k] != ' ' && data[i][k]!= '\n') {
                holder += data[i][k];
                k++;
            }
            k++;
            values[i][j] = stoi(holder);
        }
    }
    return true;
}

/**
 * Frees up the memory allocated for the 2D array of values and the 2D array of
 * partial sums.
 */
void cleanup() {
    for (int i = 0; i < num_rows; i++){
        delete [] values[i];
        delete [] sums[i];
    }
    delete [] values;
    delete [] sums;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }

    if (num_rows == 0){
        cout << "Max sum: 0" << endl;
        cout << "Values: []" << endl;
        return 0;
    }

    display_table();
    cout << "Max sum: " << compute_max_sum() << endl;
    vector<int> output = backtrack_solution();
    cout << "Values: [" << output.at(num_rows-1);

    for (int i = num_rows - 2; i >= 0; i--){
         cout << ", " << output.at(i);
    }
    cout << "]" << endl;
    cleanup();
    return 0;
}