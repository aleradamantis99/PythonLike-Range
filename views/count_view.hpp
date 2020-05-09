#pragma once

#include <type_traits>
//#include <iterator_traits>
namespace view
{
template <typename T>
struct count_view
{
	count_view(T a, T b, size_t inc = 1): start{a, b, inc} {}
	struct count_sent {};
	struct count_iter
	{
		using difference_type = std::ptrdiff_t;
		using value_type = std::remove_reference_t<T>;
		using reference = const value_type&;
		using iterator_category = std::bidirectional_iterator_tag;
		value_type s{};
		const value_type e{};
		size_t inc = 1;
		value_type operator* ()
		{
			return s;
		}
		count_iter& operator++()
		{
			s += inc;
			return *this;
		}
		count_iter operator++(int)
		{
			count_iter tmp (*this);
			tmp.s+=inc;
			return tmp;
		}
		count_iter& operator--()
		{
			s -= inc;
			return *this;
		}
		count_iter operator--(int)
		{
			count_iter tmp (*this);
			tmp.s -= inc;
			return tmp;
		}
		friend bool operator!=(count_iter a, count_sent)
		{
			return a.s < a.e;
		}
		friend bool operator!=(count_sent, count_iter a)
		{
			return a.s < a.e;
		}
		friend bool operator==(count_iter a, count_sent)
		{
			return a.s >= a.e;
		}
		friend bool operator==(count_sent, count_iter a)
		{
			return a.s >= a.e;
		}
		
	} start;
	
	auto begin() const
	{
		return start;
	}
	
	auto end() const
	{
		return count_sent{};
	}
};
} //view
