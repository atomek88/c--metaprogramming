#ifndef ROTATE_H
#  define ROTATE_H
#include<utility>

namespace mpcs {
template<typename T>
void rotate(T &a, T &b, T &c)
{
	T tmp{ std::move(a) };
	a = move(b);
	b = move(c);
	c = move(tmp);
}

// Variadic rotate: Tricky
// Something to hold an expanded parameter pack
template<typename ...Ts>
void swallow(Ts ...) {}

template<typename T, typename ...Ts>
void rotate(T &t, Ts &...ts)
{
	// swap(t, ts)...; // ill-formed :(
	swallow((std::swap(t, ts), 1)...);
}

}

#endif
