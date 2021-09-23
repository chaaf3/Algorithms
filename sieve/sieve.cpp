/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Connor Haaf, Nick Cali
 * Date        : Febuary 19, 2021
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_, max_prime_width;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
    void makeNumArray();
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit}, num_primes_{NULL}, max_prime_{NULL}, max_prime_width{NULL} {
        
    sieve();
    num_primes_ = count_num_primes();
}


void PrimesSieve::display_primes() const {
    
    cout << "Primes up to " << limit_ << ":" << endl;
    // given code for primes_per_row
    const int max_prime_width = num_digits(max_prime_),
    primes_per_row = 80 / (max_prime_width + 1);
    int indexHolder = 2;
    int rowCounter = primes_per_row;
    if (num_primes_ < primes_per_row) {
        while (indexHolder <= max_prime_) {
            while (!is_prime_[indexHolder]) {
                indexHolder++;
            }
            cout << indexHolder;
            if (indexHolder != max_prime_) {
            cout << " ";
            }
            indexHolder++;
        }
    }
    while (indexHolder <= max_prime_) {
        if (rowCounter == 0) {
            cout << endl;
            rowCounter = primes_per_row;
        }
        while (!is_prime_[indexHolder]) {
            indexHolder++;
        }
        if (num_digits(indexHolder) < max_prime_width) {
            int difference = max_prime_width - num_digits(indexHolder);
            for (int i = 0; i < difference; i++) {
                cout << " ";
            }
        }
        cout << indexHolder;
        if (indexHolder != max_prime_ && rowCounter != 1) {
        cout << " ";
        }
        rowCounter--;
        indexHolder++;
    }

    // while (indexHolder <= max_prime_) {
    //     for (int i = 0; i < primes_per_row; i++) {
    //         while (!is_prime_[indexHolder]) {
    //             indexHolder++;
    //         }
    //         int spaceHolder = num_digits(indexHolder);
    //         while (spaceHolder < max_prime_width) {
    //             cout << " ";
    //             spaceHolder++;
    //         }
    //         cout << indexHolder;
    //         indexHolder++;
    //         cout << " ";
    //     }
    //     cout << endl;
    // }
    
}

int PrimesSieve::count_num_primes() const {
    int primes = 0;
    for (int i = 0; i < limit_ + 1; i++) {
        if (is_prime_[i]) {
            primes++;
        }
    }
    return primes;
}

void PrimesSieve::sieve() {
    is_prime_[0] = false;
    is_prime_[1] = false;
    for (int i = 2; i < limit_ + 1; i++) {
        is_prime_[i] = true;
    }
    for (int i = 2; i < sqrt(limit_ + 1); i++) {
        if (is_prime_[i]) {
            for (int j = i*i; j < limit_ + 1; j += i) {
                is_prime_[j] = false;
            }
    }
}
for (int i = 2; i < limit_ + 1; i++) {
    if (is_prime_[i] == true) {
        max_prime_ = i;
    }
}
}
// pass in the largest prime
int PrimesSieve::num_digits(int num) {
    int lengthHolder = 1;
    while ((num / 10) >= 1) {
        lengthHolder++;
        num /= 10;
    }
    return lengthHolder;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;
    
    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve obj(limit);
    cout << endl;
    cout << "Number of primes found: " << obj.num_primes() << endl;
    obj.display_primes();
    return 0;
}
