int constexpr fib(size_t n)
{ // constexpr fibonacci function taking size_t of n
	if (n < 2)
		return n;
	return fib(n - 1) + fib(n - 2); // recursive
}

int main()
{
	int constexpr n = 12;
	// assert statement that fib returns correct value
	static_assert(fib(n) == 144);
}