//
// Created by Tomasz Michalik on 4/6/18.
//
#include "isReference.h"
#include <iostream>
#include <vector>

using namespace mpcs;
using namespace std;
//int i = 0;
//int& r = i;

int main() {
    cout << "Start" << endl;
    cout << "ref: " << IsReference<int&>::value << endl;
    cout << "r ref: " << IsReference<int&&>::value << endl;
    cout << "int : " << IsReference<int>::value << endl;

    return 0;
}
