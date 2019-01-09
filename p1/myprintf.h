#include<iostream>
#include<stdexcept>
// see http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2087.pdf
// modify printf to create type safe printf for c++
namespace mpcs {
	template <typename T, typename... Args>
	void printf(char const *s, T const &value, Args const &... args)
	{
		while (*s) {
			if (*s == '%' && *++s != '%') {
				// ignore the character that follows the ‘%’: we already know the type!
				std::cout << value;
				return printf(++s, args...);
			}
			std::cout << *s++;
		}
		throw std::runtime_error("extra arguments provided to printf");
	}

	void printf(char const *s)
	{
		while (*s) {
			if (*s == '%' && *++s != '%')
				throw std::runtime_error("invalid format string : missing arguments");
			std::cout << *s++;
		}
	}
}