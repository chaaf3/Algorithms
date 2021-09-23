/*******************************************************************************
 * Name    : inversioncounter.cpp
 * Author  : Connor Haaf and Nick Cali
 * Version : 1.0
 * Date    : March 31, 2021
 * Description : Computes the number inversions with mergesort.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;
// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);
/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long invcount = 0; 
    for (int i = 0; i < length -1;i++){
        for (int j = i+1; j <length; j++){
            if (array[i] > array[j]){
                invcount++;
            }
        }
    }
    return invcount;
}
/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int* result = new int[length];
    unsigned long count = mergesort(array, result, 0, length-1);
    delete [] result;
    return count;
}
static long mergesort(int array[], int scratch[], int low, int high) {
    unsigned long count = 0;
    int mid;
    int l;
    int h;
    if (low < high){
        mid = low + (high - low) /2;
        count += mergesort(array, scratch, low, mid);
        count += mergesort(array, scratch, mid+1, high);
        l = low;
        h = mid + 1;
        for(int k = low; k<=high; k++){
            if  ((l <= mid) &&  ((h > high || (array[l]) <= array[h]))){
                scratch[k] = array[l];
                l += 1;
            }else{
                count += mid - l + 1;
                scratch[k] = array[h];
                h += 1;
            }
        }
        for (int i = low; i <= high; i++){
            array[i] = scratch[i];
        }
    }
    return count;
}
int main(int argc, char *argv[]) {
    istringstream ss;
    string slow;
    if (!(argc == 1 || argc == 2)){
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }
    if (argc == 2){
        ss.str(argv[1]);
        ss >> slow;
        if (slow != "slow"){
            cout << "Error: Unrecognized option '" << slow  << "'." << endl;
            return 1;
        }
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;
    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
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
    if (values.size() == 0){
        cout << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    long inversion_count;
    if (argc == 1){
        inversion_count = count_inversions_fast(&values[0], values.size());
    }else{
        inversion_count = count_inversions_slow(&values[0], values.size());
    }
    // TODO: produce output
    cout << "Number of inversions: " << inversion_count << endl;
    return 0;
}

