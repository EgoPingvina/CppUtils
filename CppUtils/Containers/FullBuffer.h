#pragma once

#include <array>

#include <stddef.h>

template<class T, size_t size>
class FullBuffer
{
public:
    enum { Capacity = size };

	using IteratorType = typename std::array<T, size>::iterator;

    FullBuffer();

    void Add(const T& data);
    void Reset();
    bool IsFull() const;
    size_t Size() const;

    T & operator()(size_t index);

    T & Last();

	IteratorType begin();
	IteratorType end();

	size_t LastItemIndex() const;
private:
	std::array<T, size> data;

    size_t position;
};

template<class T, size_t size>
inline FullBuffer<T, size>::FullBuffer()
    : position(0)
{ }

template<class T, size_t size>
inline void FullBuffer<T, size>::Add(const T& data)
{
    if (this->position >= size) return;

    this->data[this->position++] = data;
}

template<class T, size_t size>
inline void FullBuffer<T, size>::Reset()
{
    this->position = 0;
}

template<class T, size_t size>
inline bool FullBuffer<T, size>::IsFull() const
{
    return this->position == size;
}

template<class T, size_t size>
inline size_t FullBuffer<T, size>::Size() const
{
    return size;
}

template<class T, size_t size>
inline T & FullBuffer<T, size>::operator()(size_t index)
{
    return this->data[index];
}

template<class T, size_t size>
inline size_t FullBuffer<T, size>::LastItemIndex() const
{
	return this->position == 0
		? this->position
		: this->position - 1;
}

template<class T, size_t size>
inline T & FullBuffer<T, size>::Last()
{
    return this->position == 0
        ? this->data[this->position]
        : this->data[this->position - 1];
}

template<class T, size_t size>
inline typename FullBuffer<T, size>::IteratorType FullBuffer<T, size>::begin()
{
    return this->data.begin();
}

template<class T, size_t size>
inline typename FullBuffer<T, size>::IteratorType FullBuffer<T, size>::end()
{
    return this->data.end();
}
