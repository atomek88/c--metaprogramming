#ifndef FIBONACCI_H
#  define FIBONACCI_H
namespace cspp51045 {

template<int i>
struct Fib {
    static unsigned const value = Fib<i - 1>::value + Fib<i - 2>::value;
};

template<>
struct Fib<0> {
    static unsigned const value = 0;
};

template<>
struct Fib<1> {
    static unsigned const value = 1;
};


}

#endif