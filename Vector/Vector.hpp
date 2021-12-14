#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class Vector {

  public:

    typedef T* iterator;
    typedef const T* const_iterator;

    static constexpr int SPARE_CAPACITY = 16;

  private:

    std::unique_ptr<T[]> data_{new T[SPARE_CAPACITY]};
    int size_{0};
    int capacity_{SPARE_CAPACITY};

    void resize(int new_size); 

  public:

    Vector() = default;
    Vector(int capacity); 

    iterator begin() { return &data_[0]; }
    const_iterator begin() const { return &data_[0]; }

    iterator end() { return &data_[size_]; }
    const_iterator end() const { return &data_[size_]; }

    int size() const { return size_; }
    int capacity() const { return capacity_; }
    bool is_empty() const { return !size_; }

    T& operator[](int index) { return data_[index]; }
    const T& operator[](int index) const { return data_[index]; }

    T at(int index) const; 

    void push(T element);
    void insert(T element, int index);
    void prepend(T element);

    void pop();
    void drop(int index);
    void remove(T element);
    void clear();

    int find(T element);

};

