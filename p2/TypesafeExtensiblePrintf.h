#ifndef TYPESAFE_EXTENSIBLE_PRINTF
#  define TYPESAFE_EXTENSIBLE_PRINTF
#include<iostream>
#include<string>
#include<stdexcept>
#include<iomanip>
using std::string;
using std::cout;
using std::invalid_argument;
namespace mpcs51044 {
void myPrintf(string format) { 
	auto percent = format.find_first_of("%");
	if (percent != string::npos)
		throw invalid_argument("Too few arguments to printf");
	cout << format;
}

template<typename H, typename ...Ts>
void myPrintf(string format, H const &h, Ts const &...ts) {
  auto percent = format.find_first_of("%");
  if(percent == string::npos)
    throw invalid_argument("Too many arguments to printf");
  cout << format.substr(0, percent);
  if (percent > 0 && format[percent - 1] == '\\')
	  cout << "%"; // \% is a percent sign
  else
	cout << std::forward<H>(h);
  myPrintf(format.substr(percent + 1), ts...);
}
}
#endif