#include <iostream>
#include <future>
#include <coroutine>
#include "generator/range.hpp"
#include "vect/range.hpp"
#include "views/range.hpp"
#include <ranges>

namespace views
{
	auto range = [] (auto a, auto b, size_t step = 1) 
	{ 
		using T = decltype(a);
		return std::views::iota(a, b) | 
			std::views::take((b-a)/step) |
			std::views::transform([a, step] (T el)
			{
				return el + (el-a)*(step-1);
			});
	};
}

int main()
{
	for (int i: cor::range(2, 10, 2))
	{
		std::cout << "aa" << i << std::endl;
	}
	
	for (int i: vect::range(2, 10, 2))
	{
		std::cout << "bb" << i << std::endl;
	}
	
	for (int i: std::views::iota(1, 10))
	{
		std::cout << i << std::endl;
	}
	
	for (int i: views::range(2, 10, 2))
	{
		std::cout << "cc" << i << std::endl;
	}
	
	for (int i: view::range(2, 10, 2))
	{
		std::cout << "dd" << i << std::endl;
	}
}
