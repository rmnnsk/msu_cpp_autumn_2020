#pragma once

#include <cstdlib>
#include <utility>
#include <stdexcept>
#include "my_iterator.h"

template<class T>
class MyAllocator
{
public:
    MyAllocator() = default;

    T *allocate(std::size_t n)
    {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }
        if (auto ptr = new T[n]) {
            return ptr;
        }
        throw std::bad_alloc();
    }

    void deallocate(T *ptr) noexcept
    {
        delete[] ptr;
    }
};

template<class T, class Allocator = MyAllocator<T>>
class MyVector
{
public:
    using iterator = MyIterator<T>;
    using reverse_iterator = std::reverse_iterator<MyIterator<T>>;


    MyVector()
    {
        capacity_ = START_SIZE;
        data = allocator.allocate(capacity_);
    };

    explicit MyVector(size_t n) : size_(n)
    {
        data = allocator.allocate(n);
        capacity_ = n;
    }

    MyVector(size_t n, const T &default_value) : size_(n), capacity_(n)
    {
        data = allocator.allocate(n);
        for (std::size_t i = 0; i < size_; i++) {
            data[i] = default_value;
        }
    }

    void reserve(std::size_t new_cap)
    {
        if (new_cap <= capacity_) {
            return;
        }
        T *new_ptr = allocator.allocate(new_cap);
        for (std::size_t i = 0; i < size_; i++) {
            new_ptr[i] = std::move(data[i]);
            data[i].~T();
        }
        allocator.deallocate(data);
        data = new_ptr;
        capacity_ = new_cap;
    }

    void resize(std::size_t new_size, const T &val)
    {
        if (new_size < 0) {
            throw std::invalid_argument("bad size");
        }
        if (new_size <= size_) {
            for (int i = size_ - 1; i >= new_size; i--) {
                data[i].~T();
            }
        } else {
            reserve(new_size);
            capacity_ = new_size;
            for (std::size_t i = size_; i < new_size; i++) {
                data[i] = T(val);
            }
        }
        size_ = new_size;

    }

    void resize(std::size_t new_size)
    {
        if (new_size < 0) {
            throw std::invalid_argument("bad size");
        }
        if (new_size <= size_) {
            for (int i = size_ - 1; i >= new_size; i--) {
                data[i].~T();
            }
        } else {
            reserve(new_size);
            capacity_ = new_size;
            for (std::size_t i = size_; i < new_size; i++) {
                data[i] = T{};
            }
        }
        size_ = new_size;

    }

    size_t size() const noexcept
    {
        return size_;
    }

    size_t capacity() const noexcept
    {
        return capacity_;
    }

    bool empty() const noexcept
    {
        return (size_ == 0);
    }

    T &operator[](const int i)
    {
        if (i < 0 or i + 1 > size_) {
            throw std::out_of_range("Index out of range.");
        }
        return data[i];
    };

    const T &operator[](const int i) const
    {
        if (i < 0 or i + 1 > size_) {
            throw std::out_of_range("Index out of range.");
        }
        return data[i];
    }

    void push_back(const T &value)
    {
        if (size_ == capacity_) {
            reserve(2 * size_);
        }
        data[size_++] = value;
    }

    void push_back(T &&value)
    {
        if (size_ == capacity_) {
            reserve(2 * size_);
        }
        data[size_++] = std::move(value);
    }

    void pop_back()
    {
        if (size_ == 0) {
            return;
        }
        data[size_ - 1].~T();
        size_--;
    }

    template<typename ...Args>
    void emplace_back(Args&&... args)
    {
        if (size_ == capacity_) {
            reserve(2 * size_);
        }
        data[size_++] = T(args...);
    }

    void clear() noexcept
    {
        for (std::size_t i = 0; i < size_; i++) {
            data[i].~T();
        }
        size_ = 0;
    }

    iterator begin() const
    {
        return iterator(data);
    }

    iterator end() const
    {
        return iterator(data + size_);
    }

    reverse_iterator rbegin() const
    {
        return reverse_iterator(this->end());
    }

    reverse_iterator rend() const
    {
        return reverse_iterator(this->begin());
    }

    ~MyVector()
    {
        clear();
        allocator.deallocate(data);
    }

private:
    static constexpr size_t START_SIZE = 5;
    size_t size_ = 0;
    size_t capacity_;
    T *data;
    Allocator allocator{};
};

/*
%+ operator[]
%+ push_back
%+ pop_back
%+ emplace_back
%+ empty
%+ size
%+ clear
%+ begin, rbegin
%+ end, rend
%+ resize
%+ reserve
%+ capacity
*/