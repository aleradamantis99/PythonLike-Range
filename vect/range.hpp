#pragma once

#include <vector>

namespace vect
{
template<typename T>
auto range(T a, T b, size_t s=1)
{
	std::vector<T> v((b-a)/s); //Use push_back is substraction is not supported
	for (auto& e: v)
	{
		e = a;
		a += s;
	}
	
	return v;
}

template <typename T>
auto range(T b)
{
	return range(T{}, b);
}
} //cor
