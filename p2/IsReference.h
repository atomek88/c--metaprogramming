#ifndef IS_REFERENCE_H
#define IS_REFERENCE_H
#include<type_traits>
namespace mpcs {
template<typename T> struct is_reference : public std::false_type {};
template<typename T> struct is_reference<T &> : public std::true_type {};
template<typename T> struct is_reference<T &&> : public std::true_type {};

template<typename T>
int const is_reference_v = is_reference<T>::value;
}

#endif