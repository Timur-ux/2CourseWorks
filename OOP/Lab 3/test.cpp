#include <concepts>
#include <type_traits>

template <typename T>
	requires std::is_integral<T>
int fact(T a);