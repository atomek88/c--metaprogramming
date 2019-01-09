//
// Created by Tomasz Michalik on 4/5/18.
//
#include "fib.h"
#include <iostream>
#include <vector>

using namespace mpcs;
using namespace std;
Fib<0> fib0;
// testing
Fib<1> fib1;
Fib<5> fib5;

int main() {
    vector<unsigned int> fib_nums;
    Fib<9>::add_fib(fib_nums);
    for (int i = 0; i <= 9; ++i){
        cout << "Fib check: " << i << " = " << fib_nums[i] << endl;
        }
    return 0;
}