#include "Vector.hpp"

template <typename T>
void Vector<T>::resize(int new_size) {

  auto aux = std::unique_ptr<T[]>(new T[new_size]);
  capacity_ = new_size;

  for (int i = 0; i < size_; i++)
    aux[i] = data_[i];

  std::swap(data_, aux);

}

template <typename T>
Vector<T>::Vector(int capacity) {

  resize(capacity); 

}

template <typename T>
T Vector<T>::at(int index) const {

  if (index < 0 || index >= size_)
    throw std::out_of_range("This index is out of bounds");
  
  return data_[index];

}

template <typename T>
void Vector<T>::push(T element) {

  if (size_ == capacity_) 
    resize(capacity_ * 2);

  data_[size_++] = element;

}

template <typename T>
void Vector<T>::insert(T element, int index) {

  if (index < 0 || index >= size_)
    throw std::out_of_range("This index is out of bounds");

  auto aux = std::unique_ptr<T[]>(new T[size_ + 1]);

  if (size_ == capacity_)
    resize(capacity_ * 2);

  for (int i = 0; i < index; i++)
    aux[i] = data_[i];

  aux[index] = element;

  for (int i = index; i < size_; i++)
    aux[i + 1] = data_[i];

  size_++;

  std::swap(data_, aux);

}

template <typename T>
void Vector<T>::prepend(T element) {

  auto aux = std::unique_ptr<T[]>(new T[size_ + 1]);

  if (size_ == capacity_)
    resize(capacity_ * 2);

  aux[0] = element;

  for (int i = 0; i < size_; i++)
    aux[i + 1] = data_[i];

  size_++;

  std::swap(data_, aux);

}

template <typename T>
void Vector<T>::pop() {

  if (size_ == 0) return;

  if (size_ < capacity_ / 4)
    resize(capacity_ / 2);

  size_--;

}

template <typename T>
void Vector<T>::drop(int index) {

  if (index < 0 || index >= size_)
    throw std::out_of_range("This index doesn't exists");

  auto aux = std::unique_ptr<T[]>(new T[size_ - 1]);

  if (size_ <= capacity_ / 4)
    resize(capacity_ / 2);

  for (int i = 0; i < index; i++)
    aux[i] = data_[i];

  for (int i = index; i < --size_; i++)
    aux[i] = data_[i + 1];

  std::swap(data_, aux);

}

template <typename T>
void Vector<T>::remove(T element) {

  auto index = find(element);

  if (index != -1)
    drop(index);
  else
    throw std::invalid_argument("This element doesn't exists");

}

template <typename T>
int Vector<T>::find(T element) {

  for (int i = 0; i < size_; i++) 
    if (data_[i] == element)
      return i;

  return -1;

}

template <typename T>
void Vector<T>::clear() {

  resize(SPARE_CAPACITY);
  size_ = 0;

}

