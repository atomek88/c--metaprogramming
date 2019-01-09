#include "gcd_lcm.h"
#include <utility>
#include <iostream>
using namespace mpcs;
using namespace std;

int main()
{
	// static_assert(gcd_lcm(10, 24) == pair{2, 120}, "gcd_lcm test failed"); // C++17. See https://wandbox.org/permlink/6JkY8Cii5VqQZafC
	if(gcd_lcm(10, 24) != pair<int, int>{2, 120}) // C++14
		cout << "gcd_lcm test failed\n";
	return 0;
}