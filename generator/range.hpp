#pragma once

#include "generator.hpp"

namespace cor
{
template <typename T>
cor::generator<T> range(T a, T b, size_t s=1)
{
	for (; a<b; a+=s)
	{
		co_yield a;
	}
}

template <typename T>
auto range(T b)
{
	return range(T{}, b);
}
} //cor
