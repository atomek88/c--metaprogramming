//
// Created by Tomasz Michalik on 4/5/18.
//

#ifndef HW11_ISREFERENCE_H
#define HW11_ISREFERENCE_H
#include <memory>
#include <numeric>
#include <type_traits>
#include <iterator>
#include <iostream>

namespace mpcs {

template<typename T>
struct IsReference : public std::false_type{};

template<typename T>
struct IsReference<T&> : public std::true_type{};

template<typename T>
struct IsReference<T&&> : public std::true_type{};
// used constexpr solution as well, blotted out for submission
//template<typename T>
//int constexpr bool IsReferenceV<T> = isReference<T>::value;

}

#endif //HW11_ISREFERENCE_H
