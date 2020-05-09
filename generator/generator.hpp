#pragma once
// Heavily based on https://github.com/roger-dv/cpp20-coro-generator, 
// but slightly less secure and simpler
#include <coroutine>
#include <memory>
#include <iostream>

namespace cor {

template<typename T>
class generator {
public:
	struct promise_type;	//implemented below
	struct generator_iterator;
	using handle_type = std::coroutine_handle<promise_type>;
private:
	handle_type coro;
public:
	explicit generator(handle_type h) : coro(h) {}
	generator(const generator &) = delete;
	
	generator(generator &&oth) noexcept : coro(oth.coro) {
		oth.coro = nullptr;
	}
	generator &operator=(const generator &) = delete;
	generator &operator=(generator &&other) noexcept {
		coro = other.coro;
		other.coro = nullptr;
		return *this;
	}
	~generator() {
		if (coro) {
			coro.destroy();
		}
	}

	bool next() {
		coro.resume();
		return not coro.done();
	}
	
	auto begin()
	{	
		next();
		return generator_iterator{coro};
	}
	struct sentinel{};
	auto end()
	{
		return sentinel{};
	}
};
template <typename T>
class generator<T>::generator_iterator
{
	handle_type handle;

public:
	using iterator_category = std::input_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = promise_type::value_type;
	using reference = promise_type::reference_type;
	using pointer = promise_type::pointer_type;
	
	explicit generator_iterator(handle_type h = nullptr): handle(h) 
	{
	}
	auto operator++()
	{
		handle.resume();
		return *this;
	}
	void operator++(int)
	{
		operator++();
	}
	reference operator* () const
	{
		return handle.promise().value();
	}
	friend bool operator!=(const generator_iterator& iter, sentinel)
	{
		return not iter.handle.done();
	}
	
};

template <typename T>
struct generator<T>::promise_type
{
public:
	using value_type = std::remove_reference_t<T>;
	using reference_type = std::conditional_t<std::is_reference_v<T>, T, T&>;
	using pointer_type = value_type*;

private:
	pointer_type current_value{};
	friend class generator;
public:
	promise_type() = default;
	~promise_type() = default;
	promise_type(const promise_type&) = delete;
	promise_type(promise_type&&) = delete;
	promise_type &operator=(const promise_type&) = delete;
	promise_type &operator=(promise_type&&) = delete;

	auto initial_suspend() {
		return std::suspend_always{};
	}
	decltype(auto) value() const {
		return static_cast<reference_type>(*current_value);
	}
	auto final_suspend() {
		return std::suspend_always{};
	}

	auto get_return_object() {
		return generator{handle_type::from_promise(*this)};
	}

	auto return_void() {
		return std::suspend_never{};
	}

	auto yield_value(value_type& some_value) {
		current_value = std::addressof(some_value);
		return std::suspend_always{};
	}

	void unhandled_exception() {
		std::exit(1);
	}
};

} // cor
