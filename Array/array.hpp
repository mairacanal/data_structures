#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

template <typename T, std::size_t S> 
class Array {
public:
    typedef T* iterator;
    typedef const T* const_iterator;

public:
    Array() {};

    constexpr std::size_t size() const {
        return S; 
    }

    iterator begin() {
        return iterator(data_); 
    };

    iterator end() {
        return iterator(data_ + S); 
    };

    const_iterator begin() const {
        return const_iterator(data_); 
    };

    const_iterator end() const {
        return const_iterator(data_ + S); 
    };

    T* data() {
        return data_;
    }

    const T* data() const {
        return data_;
    }

    T& operator [](std::size_t index) {
        return data_[index];
    }

    const T& operator [](std::size_t index) const {
        return data_[index];
    }

private:
    T data_[S];
};

#endif
