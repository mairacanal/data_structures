#include "LinkedList.hpp"

template <typename T>
struct List<T>::Node {
    T value_;
    std::weak_ptr<Node> prev_;
    std::shared_ptr<Node> next_;

    Node(const T& value = T {}, std::shared_ptr<Node> prev = nullptr,
        std::shared_ptr<Node> next = nullptr)
        : value_ { value }
        , prev_ { prev }
        , next_ { next } {};

    Node(T&& value, std::shared_ptr<Node> prev = nullptr,
        std::shared_ptr<Node> next = nullptr)
        : value_ { std::move(value) }
        , prev_ { prev }
        , next_ { next } {};
};

template <typename T>
class List<T>::const_iterator {

public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    std::shared_ptr<Node> current_;

    const_iterator()
        : current_ { nullptr } {};
    const_iterator(std::shared_ptr<Node> current)
        : current_ { current } {};

    const T& operator*() const { return current_->value_; }

    const_iterator& operator++()
    {
        current_ = current_->next_;
        return *this;
    }

    const_iterator operator++(int)
    {
        const_iterator prev = *this;
        ++(*this);
        return prev;
    }

    const_iterator& operator+(const int& addition)
    {
        for (int i = 0; i < addition; i++)
            ++(*this);
        return *this;
    }

    const_iterator& operator--()
    {
        current_ = current_->prev_.lock();
        return *this;
    }

    const_iterator operator--(int)
    {
        const_iterator prev = *this;
        --(*this);
        return prev;
    }

    const_iterator& operator-(const int& subtraction)
    {
        for (int i = 0; i < subtraction; i++)
            --(*this);
        return *this;
    }

    bool operator==(const const_iterator& other) const
    {
        return current_ == other.current_;
    }

    bool operator!=(const const_iterator& other) const
    {
        return !(*this == other);
    }
};

template <typename T>
class List<T>::iterator : public List<T>::const_iterator {

public:
    iterator()
        : const_iterator { nullptr } {};
    iterator(std::shared_ptr<Node> current)
        : const_iterator { current } {};

    T& operator*() { return this->current_->value_; };

    const T& operator*() const { return const_iterator::operator*(); };

    iterator& operator++()
    {
        this->current_ = this->current_->next_;
        return *this;
    }

    iterator operator++(int)
    {
        iterator prev = *this;
        ++(*this);
        return prev;
    }

    iterator& operator+(const int& addition)
    {
        for (int i = 0; i < addition; i++)
            ++(*this);
        return *this;
    }

    iterator& operator--()
    {
        this->current_ = this->current_->prev_.lock();
        return *this;
    }

    iterator operator--(int)
    {
        iterator prev = *this;
        --(*this);
        return prev;
    }

    iterator& operator-(const int& subtraction)
    {
        for (int i = 0; i < subtraction; i++)
            --(*this);
        return *this;
    }
};

template <typename T>
List<T>::List()
{
    head_ = std::make_shared<Node>();
    tail_ = std::make_shared<Node>();

    head_->next_ = tail_;
    tail_->prev_ = head_;
}

template <typename T>
List<T>::List(const List& initial)
{
    List();

    for (auto& element : initial)
        push_back(element);
}

template <typename T>
List<T>::List(List&& initial)
    : head_ { initial.head_ }
    , tail_ { initial.tail_ }
    , size_ { initial.size_ }
{
    initial.size_ = 0;
    initial.head_ = nullptr;
    initial.tail_ = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(const List& other)
{
    List copy = other;
    std::swap(*this, copy);
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other)
{
    std::swap(size_, other.size_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);

    return *this;
}

template <typename T>
T List<T>::at(iterator itr) const
{
    return *itr;
}

template <typename T>
T List<T>::at(const_iterator itr) const
{
    return *itr;
}

template <typename T>
T List<T>::operator[](int index) const
{
    return at(begin() + index);
}

template <typename T>
void List<T>::push_front(const T& element)
{
    insert(begin(), element);
}

template <typename T>
void List<T>::pop_front()
{
    erase(begin());
}

template <typename T>
void List<T>::push_back(const T& element)
{
    insert(end(), element);
}

template <typename T>
void List<T>::pop_back()
{
    erase(--end());
}

template <typename T>
void List<T>::reverse()
{
    iterator leftItr = begin();
    iterator rightItr = --end();

    while (leftItr != rightItr)
        std::swap((leftItr++).current_->value_, (rightItr--).current_->value_);
}

template <typename T>
void List<T>::remove(const T& element)
{
    iterator itr;

    for (itr = begin(); *itr != element; itr++) {
    };
    erase(itr);
}

template <typename T>
void List<T>::clear()
{
    while (!is_empty()) {
        pop_back();
    }
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& element)
{

    std::shared_ptr<Node> current = itr.current_;

    current->prev_.lock()->next_ = std::make_shared<Node>(element,
        current->prev_.lock(), current);
    current->prev_ = current->prev_.lock()->next_;

    size_++;
    return { current->prev_.lock() };
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T&& element)
{

    std::shared_ptr<Node> current = itr.current_;

    current->prev_.lock()->next_ = std::make_shared<Node>(std::move(element),
        current->prev_.lock(), current);
    current->prev_ = current->prev_.lock()->next_;

    size_++;
    return { current->prev_.lock() };
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{

    std::shared_ptr<Node> current = itr.current_;
    iterator returnValue { current->next_ };

    current->prev_.lock()->next_ = current->next_;
    current->next_->prev_ = current->prev_.lock();

    size_--;
    return returnValue;
}
