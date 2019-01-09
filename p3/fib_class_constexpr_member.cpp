template<int i>
// template creating a compile time evalution of scruct Fib
struct Fib
{ // struct is an object 'wrapper around the recursive evaluation of the static in member variable
// which is the evaluation of n-1 n-2 of this N fib, then calls lower classes
	static int constexpr value{ Fib<i - 1>::value + Fib<i - 2>::value };
};
 // specializes instances or base cases for fib
template<>
struct Fib<0> {
	static int constexpr value{ 0 };
};

template<>
struct Fib<1> {
	static int constexpr value{ 1 };
};

int main()
{
	// Doesn't work with const instead of constexpr because only compile-time constant expressions can
	// be used as template arguments
	int ff6 = Fib<Fib<6>::value>::value; 
}