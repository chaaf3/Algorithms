/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Connor Haaf and Nick Cali
 * Date        : 3/25/21
 * Description : Solves the famous waterjug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
   
    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
   
    int getA() {
        return a;
    }
    int getB() {
        return b;
    }
    int getC() {
        return c;
    }
    void resetVars(int _a, int _b, int _c) {
        a = _a;
        b = _b;
        c = _c;
    }
    State*  getParent() {
        return parent;
    }
    void setParent(State* hold) {
        parent = hold;
    }
    void setString(int ammount, string from, string to) {
        string pour = "Pour ";
        string gal;
        if (ammount == 1) {
           gal = " gallon from ";
        }
        else {
            gal = " gallons from ";
        }
        string t = " to ";
        string per = ".";
        stringstream iss;
        iss << ammount;
        string hold = iss.str();
        directions = pour + hold + gal + from + t + to + per;
    }
   
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << directions + " (" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};



string bfs(int a, int b, int c, int capA, int capB, int capC) {
    State ***array = new State**[capA+1];
    for (int i = 0; i < capA + 1; i++) {
        array[i] = new State*[capB+1];
        fill(array[i], array[i] + capB+1, nullptr);
    }
    State *first = new State( 0, 0, capC, "Initial state.");
    
    queue<State*> q;
    q.push(first);
    while (q.size() != 0){
        State* current = q.front();
        q.pop();
        if (current->getA() == a && current->getB() == b){
            stack<State *> answer;
            answer.push(current);
            while (current->getParent() != nullptr) {
                current = current->getParent();
                answer.push(current);
            }
            while (answer.size() > 0) {
                if (answer.size() == 1) {
                    State* temp;
                temp = answer.top();
                cout << temp->to_string() << endl;
                return "";
                }
                else {
                    State* temp;
                    temp = answer.top();
                    cout << temp->to_string() << endl;
                    answer.pop();
                }
            }
            return "";
        }
        if (array[current->getA()][current->getB()] == nullptr) {
            array[current->getA()][current->getB()] = current;
            //try the 6 watys of pouring water into current
            //c to a
            if (current->getC() == 0) {
            }
            else if (current->getA() == capA) {
            }
            else {
                State *adder = new State(0, 0, 0, "work");
                if (current->getC() > capA - current->getA()) {
                    adder -> setString(capA - current->getA(), "C", "A");
                    adder->resetVars(capA, current->getB(), current->getC() - (capA - current->getA()));
                }
                if (current->getC() == capA - current->getA()){
                    adder -> setString(capA - current->getA(), "C", "A");
                    adder->resetVars(capA, current->getB(), 0);
                }
                if (current->getC() < capA - current->getA()) {
                    adder -> setString(current->getC(), "C", "A");
                    adder->resetVars(current->getA() + current->getC(), current->getB(), 0);
                }
                adder -> setParent(current);
                q.push(adder);
            }
            //b to a
            if (current->getB() == 0) {
            }
            else if (current->getA() == capA) {
            }
            else {
                State *adder = new State(0, 0, 0, "work");
                if (current->getB() > capA - current->getA()) {
                    adder -> setString(capA - current->getA(), "B", "A");
                    adder->resetVars(capA, current->getB() - (capA - current->getA()), current->getC());
                }
                if (current->getB() == capA - current->getA()){
                    adder -> setString(capA - current->getA(), "B", "A");
                    adder->resetVars(capA, 0, current->getC());
                }
                if (current->getB() < capA - current->getA()) {
                    adder -> setString(current->getB(), "B", "A");
                    adder->resetVars(current->getA() + current->getB(), 0, current->getC());
                }
                adder -> setParent(current);
                q.push(adder);
            }
            //c to b
            if (current->getC() == 0) {
            }
            else if (current->getB() == capB) {
            }
            else {
                State *adder = new State(0, 0, 0, "work");
                if (current->getC() > capB - current->getB()) {
                    adder -> setString(capB - current->getB(), "C", "B");
                    adder->resetVars(current->getA(), capB, current->getC() - (capB - current->getB()));
                }
                if (current->getC() == capB - current->getB()){
                    adder -> setString(capB - current->getB(), "C", "B");
                    adder->resetVars(current->getA(), capB, 0);
                }
                if (current->getC() < capB - current->getB()) {
                    adder -> setString(current->getC(), "C", "B");
                    adder->resetVars(current->getA(), current->getB() + current->getC(), 0);
                }
                adder -> setParent(current);
                q.push(adder);
            }
            //a to b
            if (current->getA() == 0) {
            }
            else if (current->getB() == capB) {
            }
            else {
                State *adder = new State(0, 0, 0, "work");
                if (current->getA() > capB - current->getB()) {
                    adder -> setString(capB - current->getB(), "A", "B");
                    adder->resetVars(current->getA() - (capB - current->getB()), capB, current->getC());
                }
                if (current->getA() == capB - current->getB()){
                    adder -> setString(capB - current->getB(), "A", "B");
                    adder->resetVars(0, capB, current->getC());
                }
                if (current->getA() < capB - current->getB()) {
                    adder -> setString(current->getA(), "A", "B");
                    adder->resetVars(0, current->getA() + current->getB(), current->getC());
                }
                adder -> setParent(current);
                q.push(adder);
            }
            //b to c
            if (current->getB() == 0) {
            }
            else if (current->getC() == capC) {
            }
            else {
                State *adder = new State(0, 0, 0, "work");
                if (current->getB() > capC - current->getC()) {
                    adder -> setString(capC - current->getC(), "B", "C");
                    adder->resetVars(current->getA(), current->getB() - (capC - current->getC()), capC);
                }
                if (current->getB() == capC - current->getC()){
                    adder -> setString(capC - current->getC(), "B", "C");
                    adder->resetVars(current->getA(), 0, capC);
                }
                if (current->getB() < capC - current->getC()) {
                    adder -> setString(current->getB(), "B", "C");
                    adder->resetVars(current->getA(), 0, current->getC() + current->getB());
                }
                adder -> setParent(current);
                q.push(adder);
            }
            //a to c
            if (current->getA() == 0) {
            }
            else if (current->getC() == capC) {
            }
            else {
                State *adder = new State(0, 0, 0, "work");
                if (current->getA() > capC - current->getC()) {
                    adder -> setString(capC - current->getC(), "A", "C");
                    adder->resetVars(current->getA() - (capC - current->getC()), current->getB(), capC);
                }
                if (current->getA() == capC - current->getC()){
                    adder -> setString(capC - current->getC(), "A", "C");
                    adder->resetVars(0, current->getB(), capC);
                }
                if (current->getA() < capC - current->getC()) {
                    adder -> setString(current->getA(), "A", "C");
                    adder->resetVars(0, current->getB(), current->getA() + current->getC());
                }
                adder -> setParent(current);
                q.push(adder);
            }
        }
       
    }
    return "No solution.";
}

int main(int argc, char * const argv[]) {
    if (argc != 7) {
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    int capA, capB, capC, goalA, goalB, goalC;
    istringstream iss;
    
    iss.str(argv[1]);
    if ( !(iss >> capA) || capA <= 0) {
        cout << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();
    
    iss.str(argv[2]);
    if ( !(iss >> capB) || capB <=  0 ) {
        cout << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[3]);
    if ( !(iss >> capC) || capC <=  0) {
        cout << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
        return 1;
    }
    iss.clear();   

    iss.str(argv[4]);
    if ( !(iss >> goalA) || goalA < 0) {
        cout << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[5]);
    if ( !(iss >> goalB) || goalB < 0) {
        cout << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[6]);
    if ( !(iss >> goalC) || goalC < 0) {
        cout << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[1]);
    if (goalA > capA) {
        cout << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[2]);
    if (goalB > capB) {
        cout << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    iss.clear();

    iss.str(argv[3]);
    if (goalC > capC) {
        cout << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    iss.clear();
    
    if  ((goalA + goalB + goalC) != capC) {
        cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    iss.clear();
    string holder =  bfs(goalA, goalB, goalC, capA, capB, capC);
    if (holder =="No solution.") {
        cout << "No solution.";
    }
    return 1;

}

