#include <iostream>
// #include <list>

#include "s21_list.h"
// --------------------------------------------------------------------Functions
namespace s21 {

template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  change_end();
}

template <typename T>
list<T>::list(size_type n) : list() {
  if (n >= max_size()) {
    throw std::out_of_range("Limit of the container is exceeded");
  }
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
  change_end();
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (const auto& item : items) {
    push_back(item);
    change_end();
  }
}

template <typename T>
list<T>::list(const list& l) : list() {
  Node* current = l.head_;
  for (size_type i = 0; i != l.size_; i++) {
    push_back(current->value_);
    current = current->next_;
  }
}

template <typename T>
list<T>::list(list&& l) {
  size_ = std::exchange(l.size_, 0);
  head_ = std::exchange(l.head_, nullptr);
  tail_ = std::exchange(l.tail_, nullptr);
  end_ = std::exchange(l.end_, nullptr);
}

template <typename T>
list<T>::~list() {
  clear();
  delete end_;
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& l) {
  size_ = std::exchange(l.size_, 0);
  head_ = std::exchange(l.head_, nullptr);
  tail_ = std::exchange(l.tail_, nullptr);
  end_ = std::exchange(l.end_, nullptr);
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& l) {
  if (this != &l) {
    while (!empty()) {
      pop_front();
    }
    Node* current = l.list_.head;
    while (current) {
      push_back(current->value);
      current = current->next;
    }
  }
  return *this;
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  return head_->value_;
}

template <class value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  return tail_->value_;
}

template <class value_type>
typename list<value_type>::reference list<value_type>::front() {
  return head_->value_;
}

template <class value_type>
typename list<value_type>::reference list<value_type>::back() {
  return tail_->value_;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(end_);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
  return const_iterator(head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  return const_iterator(end_);
}

template <typename T>
bool list<T>::empty() const {
  return (head_ == nullptr);
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node* current = pos.ptr_;
  Node* add = new Node(value);
  if (empty()) {
    add->next_ = end_;
    add->prev_ = end_;
    head_ = add;
    tail_ = add;
  } else {
    if (current == head_)
      head_ = add;
    else if (current == end_)
      tail_ = add;

    add->next_ = current;
    add->prev_ = current->prev_;
    current->prev_->next_ = add;
    current->prev_ = add;
  }
  size_++;
  change_end();
  return iterator(add);
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  Node* current = pos.ptr_;
  if (!empty() && current != end_) {
    if (current == head_) {
      if (current->next_ && current->next_ != end_)
        head_ = current->next_;
      else
        head_ = end_;
    } else if (current == tail_) {
      if (current->prev_ && current->prev_ != end_)
        tail_ = current->prev_;
      else
        tail_ = end_;
    }
    current->prev_->next_ = current->next_;
    current->next_->prev_ = current->prev_;
    delete current;
    size_--;
  } else {
    throw std::invalid_argument("Invalid argument");
  }
  change_end();
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  size_++;
  change_end();
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }
  if (size_ == 1) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    tail_ = tail_->prev_;
    delete tail_->next_;
    tail_->next_ = nullptr;
  }
  size_--;
  change_end();
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  if (empty()) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->next_ = head_;
    head_->prev_ = new_node;
    head_ = new_node;
  }
  size_++;
  change_end();
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("list is empty");
  }
  if (size_ == 1) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    head_ = head_->next_;
    delete head_->prev_;
    head_->prev_ = nullptr;
  }
  size_--;
  change_end();
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
}

template <typename T>
void list<T>::merge(list& other) {
  Node* my_node = other.head_;
  while (my_node != other.tail_) {
    this->push_back(my_node->value_);
    my_node = my_node->next_;
  }
  if (my_node) this->push_back(my_node->value_);
  if (size_ != other.size_ && other.head_ != nullptr) sort();
  if (my_node) other.clear();
}

template <class T>
void list<T>::reverse() {
  if (size_ > 1) {
    Node* start = head_;
    Node* fin = tail_;
    for (size_type step = 0; step < size_ / 2; step++) {
      std::swap(start->value_, fin->value_);
      start = start->next_;
      fin = fin->prev_;
    }
  }
}

template <typename T>
void list<T>::unique() {
  if (!empty()) {
    for (iterator it_last = begin(); it_last != end();) {
      if (!it_last.ptr_) return;
      iterator it_next = it_last;
      it_next++;
      if (*it_last == *it_next) {
        erase(it_next);
      } else
        ++it_last;
    }
  }
}

template <typename T>
void list<T>::splice(iterator pos, list& other) {
  if (!other.empty()) {
    if (pos == nullptr) {
      Node* my_node = other.head_;
      while (my_node != other.tail_) {
        push_back(my_node->value_);
        my_node = my_node->next_;
      }
      push_back(my_node->value_);
      other.clear();
    } else {
      for (iterator it = other.begin(); it != other.end(); ++it)
        insert(pos, *it);
    }
    other.clear();
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    for (size_type j = 0; j < size_; j++) {
      Node* my_node = head_;
      while (my_node != tail_) {
        if (my_node->value_ > my_node->next_->value_)
          std::swap(my_node->value_, my_node->next_->value_);
        my_node = my_node->next_;
      }
    }
  }
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(iterator pos, Args&&... args) {
  for (const auto& arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_back(arg);
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_front(arg);
  }
}

template <typename T>
void list<T>::change_end() {
  if (end_) {
    end_->next_ = head_;
    end_->prev_ = tail_;
    end_->value_ = size();
    if (head_) head_->prev_ = end_;

    if (tail_) {
      tail_->next_ = end_;
    }
  }
}
}  // namespace s21
