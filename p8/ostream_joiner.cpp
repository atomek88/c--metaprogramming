// Created by Tomasz Michalik on 5/22/18.
#include "ostream_joiner.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using namespace mpcs51044;

int
main()
{

	vector<int> fib = { 0, 1, 1, 2, 3, 5, 8, 13, 21 };
    cout << "(";
    copy(fib.begin(), fib.end(), ostream_joiner(cout, ", "));
    cout << ")" << endl << endl;

    return 0;
}