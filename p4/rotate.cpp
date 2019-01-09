#include "rotate.h"
#include <iostream>
using namespace mpcs;
using namespace std;

int main()
{
	int i0{0}, i1{1}, i2{2}, i3{3};

	rotate(i0, i1, i2, i3);
	cout << i0 << i1 << i2 << i3 << endl;
}