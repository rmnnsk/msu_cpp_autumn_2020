#pragma once

#include <cstdlib>
#include <utility>
#include <stdexcept>

template<class T>
class MyIterator;

template<typename T>
MyIterator<T> operator+(const MyIterator<T> &iter, int n);

template<typename T>
MyIterator<T> operator-(const MyIterator<T> &iter, int n);

template<class T>
class MyIterator : public std::iterator<std::random_access_iterator_tag, T>
{
private:
    T *ptr;
public:
    explicit MyIterator(T *ptr) : ptr(ptr) {};

    bool operator==(const MyIterator &other) const
    {
        return ptr == other.ptr;
    }

    bool operator!=(const MyIterator &other) const
    {
        return ptr != other.ptr;
    }

    T &operator*() const
    {
        return *ptr;
    }

    T *operator->() const
    {
        return ptr;
    }

    MyIterator operator++(int)
    {
        auto tmp = *this;
        ptr++;
        return tmp;
    }

    MyIterator &operator++()
    {
        ptr++;
        return *this;
    }

    MyIterator operator--(int)
    {
        auto tmp = *this;
        ptr--;
        return tmp;
    }

    MyIterator &operator--()
    {
        ptr--;
        return *this;
    }

    MyIterator &operator+=(const int n)
    {
        ptr += n;
        return *this;
    }

    MyIterator &operator-=(const int n)
    {
        ptr -= n;
        return *this;
    }

    bool operator<(const MyIterator<T> &other) const
    {
        return ptr < other.ptr;
    }

    bool operator<=(const MyIterator<T> &other) const
    {
        return (*this == other) || (*this < other);
    }

    bool operator>(const MyIterator<T> &other) const
    {
        return !(*this <= other);
    }

    bool operator>=(const MyIterator<T> &other) const
    {
        return !(*this < other);
    }

    friend MyIterator<T> operator+<T>(const MyIterator<T> &iter, int n);

    friend MyIterator<T> operator-<T>(const MyIterator<T> &iter, int n);

    T &operator[](const int idx)
    {
        return *(ptr + idx);
    }

    const T &operator[](const int idx) const
    {
        return *(ptr + idx);
    }
};

template<typename T>
MyIterator<T> operator+(const MyIterator<T> &iter, const int n)
{
    return MyIterator(iter.ptr + n);
}

template<typename T>
MyIterator<T> operator-(const MyIterator<T> &iter, const int n)
{
    return MyIterator(iter.ptr - n);
}
