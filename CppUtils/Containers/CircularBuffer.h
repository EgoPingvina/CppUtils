#pragma once

#include <stdint.h>

#include <stdlib.h>

template <class T, size_t size>
class CircularBuffer
{
public:
    class iterator
    {
    public:
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef int difference_type;

        iterator(CircularBuffer &buffer, size_t index)
            : buffer(buffer), index(index)
        { }

        iterator(CircularBuffer &buffer)
            : buffer(buffer), index(size)
        { }

        self_type operator++()
        {
            ++this->index;

            return *this;
        }

        self_type operator++(int)
        {
            self_type lhs = *this;

            ++(*this);

            return lhs;
        }

        reference operator*() { return this->buffer.GetReference(this->index); }
        pointer operator->() { return  this->buffer.GetReference(this->index); }

        bool operator==(const self_type& rhs) { return this->index == rhs.index; }
        bool operator!=(const self_type& rhs) { return this->index != rhs.index; }
    private:
        CircularBuffer &buffer;

        size_t index;
    };

    CircularBuffer()
        : position(0)
    { }

    void Push(T);

    T Get(size_t index);

    size_t Length() const;

    iterator begin();
    iterator end();
private:
    T buffer[size];

    int position;

    T& GetReference(size_t index);

    friend class iterator;
};

template<class T, size_t size>
inline void CircularBuffer<T, size>::Push(T data)
{
    if (this->position >= size)
        this->position = 0;

    this->buffer[this->position++] = data;
}

template<class T, size_t size>
T CircularBuffer<T, size>::Get(size_t index)
{
    int32_t result = index - this->position + 2;
	int
    return result < 0
        ? this->buffer[size + result]
        : this->buffer[result];
}

template<class T, size_t size>
inline size_t CircularBuffer<T, size>::Length() const
{
    return size;
}

template<class T, size_t size>
typename CircularBuffer<T, size>::iterator CircularBuffer<T, size>::begin()
{
    return                                                                                                                                                                                                                                        (*this, 0);
}

template<class T, size_t size>
typename CircularBuffer<T, size>::iterator CircularBuffer<T, size>::end()
{
    return iterator(*this);
}

template<class T, size_t size>
T & CircularBuffer<T, size>::GetReference(size_t index)
{
    short result = index - this->position + 2;

    return result < 0
        ? this->buffer[size + result]
        : this->buffer[result];
}