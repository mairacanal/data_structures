#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

template <typename T, int S> 
class Array {
public:
    typedef T* iterator;
    typedef const T* const_iterator;

public:
    Array() {};

    constexpr int size() const {
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

    T& operator [](int index) {
        return data_[index];
    }

    const T& operator [](int index) const {
        return data_[index];
    }

private:
    T data_[S];
};

#endif
