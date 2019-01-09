#include "password.h"
#include <iostream>
#include <tuple>
using namespace mpcs;
using namespace std;

struct S { 
	S(int, string) {}
	void f(int &i, double d) {
		cout << "f called" << endl;
	}
	void g(tuple<int, int> &&) {
		cout << "g called" << endl;
	}
};

int main()
{
	string pw;
	cout << "Password? ";
	cin >> pw;
	PasswordProtected<S> s{3, "foo" };
	int i{ 5 };
	s(pw, &S::f, i, 2.1); // OK 
	s("bar", &S::g, tuple<int, int>{2, 3}); // Exception: Bad password
}
