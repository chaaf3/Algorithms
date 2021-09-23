/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Connor Haaf
 * Version     : 1.0
 * Date        : 5/03/2021
 * Description : use red black trees to find occurances of a word
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include "rbtree.h"
#include "node.h"
#include "tree.h"
#include "treeprinter.h"

using namespace std;

int limit;
vector<string> data;
// the loaded each
vector<string> dataVals;
RedBlackTree<string, int> *answers[26];

void fill_rbtrees() {
    for (int i = 0; i < 26; i++) {
        answers[i] = new RedBlackTree<string, int>();
    }
    for (int i = 0; i < (int)dataVals.size(); i++) {
        int index = (int)(dataVals[i].at(0)) - 97;
        if (answers[index]->find(dataVals[i]) != answers[index]->end()) {
            Node<string, int> temp = *(answers[index]->find(dataVals[i]));
            temp.set_value(temp.value() + 1);
        }
        else {
            answers[index]->insert(dataVals[i], 1);
        }

    }
}
queue<string> mostCommon() {
    queue<string> finalAnswer;
    queue<int> finalAnswerOccurance;
    Node<string, int> largest;
    for (int i = 0; i < limit; i++) {
        for (int j = 0; j < 26; j++) {
            Node<string, int> temp = *(answers[j]->begin());
            //temp is the root of each rbtree
            while (temp.right != nullptr) {
                temp = *(temp.right);
            }
            if (temp.value() > largest.value()) {
                largest = temp;
            }
            
        }
        finalAnswer.push(largest.key());
        finalAnswerOccurance.push(largest.value());
        largest.set_value(-1);
    }
    return finalAnswer;
}

bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "' for input." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while (getline(input_file, line)) {
            data.push_back(line);
        }
        // data has all the lines as a string
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
        for (int i = 0; i < (int)data.size(); i++) {
            int k = 0;
            string holder = "";
            //k is for how many letters in a word
            while (k < (int)data[i].size() && data[i][k] != ' ' && data[i][k]!= '\n') {
                holder += data[i][k];
                k++;
            }
            k++;
            dataVals.push_back(holder);
        }
    return true;
}

int main(int argc, char * const argv[]) {
    if (argc == 1) {
        cerr << "Usage: " << argv[0] << " <filename> [limit]" << endl;
        return 1;
    }
    istringstream iss;
    if (argc == 3) {
        iss.str(argv[2]);
        if ( !(iss >> limit)) {
            cerr << "Error: Invalid limit '" << argv[2] << "' received." << endl;
        }
        else if (limit < 0) {
            cerr << "Error: Invalid limit '" << argv[2] << "' received." << endl;
        }
    }
    else {
        limit = 10;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }
    
    fill_rbtrees();
    queue<string> answer = mostCommon();
    while (!answer.empty()) {
        cout << answer.front() << " ";
    }
}