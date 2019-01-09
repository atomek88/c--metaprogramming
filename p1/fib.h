//
// Created by Tomasz Michalik on 4/5/18.
//

#ifndef HW11_FIB_H
#define HW11_FIB_H
#include <numeric>
#include <vector>
#include <algorithm>
#include <iostream>
using std::ostream;
using std::ostringstream;
using std::streamsize;

namespace mpcs {
    template<unsigned int i>
    class Fib {
    public:
    // enumerated value
        enum {
            value = (Fib<i - 1>::value + Fib<i - 2>::value)
        };
        // add fib number and recurse through fibonacci sequence before I
        static void add_fib(std::vector<unsigned int> &f){
            Fib<i-1>::add_fib(f);
            f.push_back(value);
            }

    };

// set base case 0
    template<>
    class Fib<0> {
    public:
        enum {
            value = 0
        };
        // add 0 to end of vector for base case
        static void add_fib(std::vector<unsigned int> &f){
            f.push_back(value);}
    };

// fib base case for 1
    template<>
    class Fib<1> {
    public:
        enum {
            value = 1
        };
        // add values to vector showing what numbers in this fib #
        static void add_fib(std::vector<unsigned int> &f){
            Fib<0>::add_fib(f);
            f.push_back(value);
            }
    };
}

#endif //HW11_FIB_H
