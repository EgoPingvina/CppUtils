#pragma once

#include "NumericConvertions.hpp"

using namespace NumericConvertions;

/// <summary>
/// Число в закольцованном интервале (аббревиатура от "number in the looped interval")
/// </summary>
template<typename T, int32_t min = 0, int32_t max = 0> class NuLI;

template<typename T, int32_t min, int32_t max>
class NuLI
{
	static_assert(std::is_arithmetic<T>::value, "Argument type isn't arithmethic");

	template<typename T1, typename T2, int32_t min, int32_t max>
	friend inline NuLI<T1> operator+(const NuLI<T1>& leftOperand, const NuLI<T2, min, max>& rightOperand);

private:

	static constexpr int32_t min = min;

	static constexpr int32_t max = max;

	static constexpr int32_t length = max - min;

	T current;

	inline void Normalize(T& value)
	{
		while (value < min)
			value += length;

		while (value > max)
			value -= length;
	}

public:

	NuLI(T value, bool isNeedLimit = true)
		: current(isNeedLimit
			? limiter<min, max, T>(value)
			: value)
	{ }

	inline NuLI<T, min, max> operator+(const T& other)
	{
		T result = this->current + other;
		this->Normalize(result);

		return NuLI(result);
	}

	inline NuLI<T, min, max> operator-(const T& other)
	{
		T result = this->current - other;
		this->Normalize(result);

		return NuLI(result);
	}

	inline NuLI<T, min, max> operator+(const NuLI<T, min, max>& other)
	{
		return this->operator+(other.current);
	}

	inline NuLI<T, min, max> operator-(const NuLI<T, min, max>& other)
	{
		return this->operator-(other.current);
	}
};

template<typename T>
class NuLI<T>
{
	static_assert(std::is_arithmetic<T>::value, "Argument type isn't arithmethic");

	template<typename T1, typename T2, int32_t min, int32_t max>
	friend inline NuLI<T1> operator+(const NuLI<T1>& leftOperand, const NuLI<T2, min, max>& rightOperand);

private:

	const T min, max, length;

	T current;

	inline void Normalize(T& value)
	{
		while (value < this->min)
			value += this->length;

		while (value > this->max)
			value -= this->length;
	}

public:

	NuLI(T value, T min, T max, bool isNeedLimit = true)
		: current(isNeedLimit
			? limiter<T>(min, max, value)
			: value)
		, min(min)
		, max(max)
		, length(max - min)
	{ }

	inline NuLI<T> operator+(const T& other)
	{
		T result = this->current + other;
		this->Normalize(result);

		return NuLI(result, this->min, this->max);
	}

	inline NuLI<T> operator-(const T& other)
	{
		T result = this->current - other;
		this->Normalize(result);

		return NuLI(result, this->min, this->max);
	}

	inline NuLI<T> operator+(const NuLI<T>& other)
	{
		static_assert(this->min == other.min && this->max == other.max, "Limits are not equal");

		return this->operator+(other.current);
	}

	inline NuLI<T> operator-(const NuLI<T>& other)
	{
		static_assert(this->min == other.min && this->max == other.max, "Limits are not equal");

		return this->operator-(other.current);
	}
};

template<typename T1, typename T2, int32_t min, int32_t max>
inline NuLI<T1> operator+(const NuLI<T1>& leftOperand, const NuLI<T2, min, max>& rightOperand)
{
	static_assert(((T2)leftOperand.min == (T1)rightOperand.min
		&& (T2)leftOperand.max == (T1)rightOperand.max, "Types are not convertable and limits are not equal");

	NuLI<T1> result(rightOperand.current, rightOperand.min, rightOperand.max);
	return result + leftOperand;
}