#pragma once
#include "count_view.hpp"
namespace view
{
template <typename T>
auto range(T a, T b, size_t s=1)
{
	return count_view{a, b, s};
}

template <typename T>
auto range(T b)
{
	return count_view{T{}, b};
}
} // view
