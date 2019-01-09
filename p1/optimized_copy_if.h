#ifndef OPTIMIZED_COPY_H
#define OPTIMIZED_COPY_H
#include<type_traits>
#include<iterator>
using std::iterator_traits;
using std::integral_constant;
using std::true_type;
using std::enable_if_t;
using std::remove_const_t;
using std::is_trivially_copy_constructible_v;
using std::is_pointer_v;

namespace mpcs {

	template<typename I1, typename I2>
	I2 optimized_copy(I1 first, I1 last, I2 out)
	{
		if constexpr (is_pointer_v(I1) && is_same_v(I2)
			&& is_trivially_copy_constructible_v(typename I2::value_type)) {
			memcpy(out, first, (last - first) * sizeof(T));
			return out + (last - first);
		} else {
			for (; first != last; ++out, ++first)
				*out = *first;
			return out;
		}
	}
}
#endif // !OPTIMIZED_COPY_H
