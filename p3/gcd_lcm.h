#ifndef GCD_LCM_H
#  define GCD_LCM_H
#include <utility>

namespace mpcs {
    //  gcd constexp func evaluated if vars known, else calls gcd_lcm
	int constexpr gcd(int a, int b) {
		if (b == 0)
			return a;
		return gcd(b, a%b);
	}
    // gcd lcm function returning pair
	std::pair<int, int> constexpr gcd_lcm(int a, int b) {
		int d = gcd(a, b);
		return { d, a*b / d };
	}

}
#endif