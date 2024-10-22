#ifndef CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Array Member functions ------------------------------------------------

  array() {}
  array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other);
  ~array() {}
  array<T, N> &operator=(const array &other);
  array<T, N> &operator=(array &&other);

  // Array Element access --------------------------------------------------

  reference at(size_type pos);
  reference operator[](size_type pos) { return arr_[pos]; };
  const_reference at(size_type pos) const;
  const_reference operator[](size_type pos) const { return arr_[pos]; };
  const_reference front();
  const_reference back();
  iterator data() { return arr_; }
  const_iterator data() const { return arr_; }

  // Array Iterators -------------------------------------------------------

  iterator begin() { return arr_; }
  const_iterator begin() const { return arr_; }

  iterator end() { return arr_ + size_; }
  const_iterator end() const { return arr_ + size_; }

  // Array Capacity --------------------------------------------------------

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type max_size() const { return size_; }

  // Array Modifiers -------------------------------------------------------

  void swap(array &other);
  void fill(const_reference value);

 private:
  size_type size_ = N;
  value_type arr_[N];
};

}  // namespace s21

#include "s21_array.inc"

#endif