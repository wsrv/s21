#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_VECTOR_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_VECTOR_S21_VECTOR_H

namespace s21 {

// template <typename T>

template <typename T>
class vector {
 public:
  class VectorIterator;
  class VectorConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = vector<T>::VectorIterator;
  using size_type = size_t;
  using iterator_pointer = T *;
  using const_iterator = vector<T>::VectorConstIterator;
  using const_iterator_pointer = const T *;

  vector();
  vector(std::size_t n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v);
  ~vector();
  vector &operator=(vector &&v);
  vector &operator=(const vector &v);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  T *data() noexcept;

  iterator begin();
  const_iterator cbegin() const;
  iterator end();
  const_iterator cend() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  //  public:
  iterator_pointer data_;
  size_type size_;
  size_type capacity_;
};

template <typename T>
class vector<T>::VectorIterator {
 public:
  VectorIterator() = default;
  VectorIterator(iterator_pointer ptr);

  reference operator*();
  VectorIterator &operator++(int);
  VectorIterator &operator--(int);
  VectorIterator &operator++();
  VectorIterator &operator--();
  VectorIterator operator+(int n) const;
  VectorIterator operator-(int n) const;
  ptrdiff_t operator-(const VectorIterator &other) const;
  bool operator==(const VectorIterator &other) const;
  bool operator!=(const VectorIterator &other) const;

 private:
  iterator_pointer ptr_;
};

template <typename T>
class vector<T>::VectorConstIterator : public VectorIterator {
 public:
  VectorConstIterator() = default;
  VectorConstIterator(const_iterator_pointer ptr);

  const_reference operator*() const;
  VectorConstIterator &operator++(int);
  VectorConstIterator &operator--(int);
  VectorConstIterator &operator++();
  VectorConstIterator &operator--();
  VectorConstIterator operator+(int n) const;
  VectorConstIterator operator-(int n) const;
  ptrdiff_t operator-(const VectorConstIterator &other) const;
  bool operator==(const VectorConstIterator &other) const;
  bool operator!=(const VectorConstIterator &other) const;

 private:
  const_iterator_pointer ptr_;
};

}  // namespace s21
#include "s21_vector.inc"
#endif  // VECTOR_H
