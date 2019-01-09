#include <iostream>
#include "IndentStream.h"
// Created by Tomasz Michalik on 5/12/18.
using namespace std;
using namespace cspp51044;

int main()
{
	IndentStream ins(cout);
	ins << "int" << endl;
	ins << "fib(int n) {" << indent << endl;
	ins << "if (n == 0) " << indent << endl;
	ins << "return 0;" << unindent << endl;
	ins << "if (n == 1) " << indent << endl;
	ins << "return 1;" << unindent << endl;
	ins << "return fib(n-2) + fib(n-1);" << unindent << endl;
	ins << "}" << endl;
	return 0;
}