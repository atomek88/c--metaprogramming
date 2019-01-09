#ifndef TUPLE_H
#  define TUPLE_H
#include<utility>
#include<type_traits>
#include"variadic_examples.h"
#include<tuple>
namespace mpcs {
// First try at tuple
template<typename ...Ts> struct Tuple1;

template<> struct Tuple1<> {};

template<typename T, typename ...Ts>
struct Tuple1<T, Ts...>
{
	Tuple1(T const &t, Ts const &... ts) : val(t), restOfVals(ts...) {}
	T val;
	Tuple1<Ts...> restOfVals;
};

// Indirect through a class because can't partially specialize template function

template<int i, typename ...Ts>
struct Getter1;

template<typename ...Ts>
struct Getter1<0, Ts...> {
	static auto &get(Tuple1<Ts...> &tup) {
		return tup.val;
	}
};

template<int i, typename T, typename ...Ts>
struct Getter1<i, T, Ts...> {
	static auto &get(Tuple1<T, Ts...> &tup) {
		return Getter1<i-1, Ts...>::get(tup.restOfVals);
	}
};

template<int i, typename ...Ts>
auto &get(Tuple1<Ts...> &tup) {
	return Getter1<i, Ts...>::get(tup);
}

// Tuple2 is almost identical to tuple1 except it uses the empty base optimization
// for better space utilization as demonstrated in Tuple.cpp
template<typename ...Ts> struct Tuple2;

template<> struct Tuple2<> {};

template<typename T, typename ...Ts>
struct Tuple2<T, Ts...> : public Tuple2<Ts...>
{
	Tuple2(T const &t, Ts const &... ts) : Tuple2<Ts...>(ts...), val(t) {}
	Tuple2(T &&) = default;
	Tuple2& operator=(const Tuple2<T>&);
	Tuple2& operator=(Tuple2<T>&&);
	T val;
};

// Indirect through a class because can't partially specialize template arguments

template<int i, typename ...Ts>
struct Getter2;

template<typename T, typename ...Ts>
struct Getter2<0, T, Ts...> {
	static auto &get(Tuple2<T, Ts...> &tup) {
		return tup.val;
	}
};

template<int i, typename T, typename ...Ts>
struct Getter2<i, T, Ts...> {
	static auto &get(Tuple2<T, Ts...> &tup) {
		return Getter2<i - 1, Ts...>::get(static_cast<Tuple2<Ts...>&>(tup));
	}
};

template<int i, typename ...Ts>
auto &
get(Tuple2<Ts...> &tup) {
	return Getter2<i, Ts...>::get(tup);
}

// Add indexing by type
template<typename T, typename ...Ts>
auto &
get(Tuple2<Ts...> &tup) {
	static_assert(Count<T, Tuple2<Ts...>>::value != 0, "Nonexistent type selection in tuple");
	static_assert(Count<T, Tuple2<Ts...>>::value == 1, "Ambiguous type selection in tuple");
	return get<IndexOf<std::tuple<Ts...>, T>::value>(tup);
}

/* TypeTuple is a simple tuple implementation that supports addressing by type, but
// is not good for addressing by index. Although not ideal for tuples, we will
// make use of this approach in the factories we create next week.
template<typename T> struct Holder {
	T val;
};
// inherits from holder just to get T val of value
template<typename ...Ts>
struct TypeTuple : public Holder<Ts>... {
};
// get implementation has a T head and tail(remainder of tuple
template<typename T, typename ...Ts>
T &get(TypeTuple<Ts...>) { 
	return static_cast<Holder<T> *>(this)->val; // pointer here to deref itself and get its value
}
*/


}

#endif