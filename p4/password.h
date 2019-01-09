#ifndef PASSWORD_H
#  define PASSWORD_H
#include<string>
#include<stdexcept>
#include<utility>
using std::string;
using std::forward;

namespace mpcs {
bool checkPassword(string s) {
	return s == "C++"; // Dummy implementation
}

template <typename T>
class PasswordProtected {
public:
	template<typename ...Ts>
	PasswordProtected(Ts &&... ts) : t{forward<Ts>(ts)...} {}

	template<typename R, typename ...Params, typename ...Args>
	R operator()(string password, R(T::*f)(Params...), Args &&... args) {
		if (!checkPassword(password))
			throw std::invalid_argument("Bad password");
		return (t.*f)(forward<Args>(args)...); // need to forward the arguments becaause protected by this template wrapping a T
	}
private:
	T t;
};

}
#endif
