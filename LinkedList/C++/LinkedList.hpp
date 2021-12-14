#pragma once

#include <iterator>
#include <memory>

template<typename T>
class List {
    private:
        class iterator;
        class const_iterator;

        struct Node;

        std::shared_ptr<Node> head_;
        std::shared_ptr<Node> tail_;
        int size_ = 0;

    public:
        List();
        List(List&& initial);
        List(const List& initial);

        List& operator=(const List& other);
        List& operator=(List&& other);

        iterator begin() { return { head_->next_ }; };
        iterator end() { return { tail_ }; };

        const_iterator begin() const { return { head_->next_ }; };
        const_iterator end() const { return { tail_ }; };

        int size() const { return size_; };
        bool is_empty() const { return !size_; };

        T at(iterator itr) const;
        T at(const_iterator itr) const;
        T operator[](int index) const;

        void push_front(const T& element);
        void pop_front();

        void push_back(const T& element);
        void pop_back();

        T& front() { return *begin(); };
        const T& front() const { return *begin(); };

        T& back() { return *(--end()); };
        const T& back() const { return *(--end()); };

        void reverse();

        void remove(const T& element);
        void clear();

        iterator insert(iterator itr, const T& element);
        iterator insert(iterator itr, T&& element);

        iterator erase(iterator itr);

        ~List() = default;

};
