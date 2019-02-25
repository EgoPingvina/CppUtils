#pragma once

#include <type_traits>

template<typename T>
constexpr inline bool CheckBit(const T& input, size_t bit)
{
	static_assert(std::is_integral<T>(),
		"The input type has a value other than an integer.");

	return static_cast<bool>(input & (1 << bit));
}

template<typename T>
constexpr inline T SetBit(T input, size_t bit)
{
	static_assert(std::is_integral<T>(),
		"The input type has a value other than an integer.");

	return (bit < sizeof(T) * 8) ?
		input | (1 << bit) :
		input;
}

template<typename T>
constexpr inline T ClearBit(T input, size_t bit)
{
	static_assert(std::is_integral<T>(),
		"The input type has a value other than an integer.");

	return (bit < sizeof(T) * 8) ?
		input & ~(1 << bit) :
		input;
}

template<typename T>
constexpr inline T InvertBit(T input, size_t bit)
{
	static_assert(std::is_integral<T>(),
		"The input type has a value other than an integer.");

	return (bit < sizeof(T) * 8) ?
		input ^ (1 << bit) :
		input;
}