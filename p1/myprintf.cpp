#include "myprintf.h"
#include<iostream>
using namespace std;

using namespace mpcs;
template<typename T, typename U>
struct MyPair {
	MyPair(T t, U u) : first{ t }, second{ u } {}
	T first;
	U second;
	
};
template<typename T, typename U>
inline ostream &operator<<(ostream &os, MyPair<T, U> p)
{
	os << "( " << p.first << ", " << p.second << ")";
	return os;
}

int main()
{
	MyPair<int, double> mpid{ 1, 2.3 };
	printf("Testing: %d, %d", 32, mpid);
}