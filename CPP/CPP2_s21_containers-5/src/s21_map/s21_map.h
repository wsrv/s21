#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_MAP_S21_MAP_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_MAP_S21_MAP_H

#include "../BinaryTree/BinaryTree.h"

namespace s21 {
template <typename Key, typename T>
class map : public BinaryTree<Key, T, std::pair<const Key, T>> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator =
      typename BinaryTree<Key, T, std::pair<const Key, T>>::Iterator;
  using const_iterator =
      typename BinaryTree<Key, T, std::pair<const Key, T>>::Const_Iterator;

 public:
  map();  // Конструктор по умолчанию
  map(std::initializer_list<value_type> const &items);
  map(const map &m) : BinaryTree<Key, T, value_type>(m){};  // copy constructor
  map(map &&m)
      : BinaryTree<Key, T, value_type>(std::move(m)){};  // move constructor
  ~map() = default;
  map &operator=(map &&m);  // assignment operator overload for moving object
  map &operator=(
      const map &m);  // assignment operator overload for copying object

 public:  // Element access
  T &operator[](const Key &key);
  T &operator[](Key &&key);
  T &at(const Key &key);
  const T &at(const Key &key) const;
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);

 protected:  // support
  Key GetKey(value_type val) const override { return Key(val.first); }
  //    T GetVal(value_type val) override { return T(val.second); }
  void SetVal(typename BinaryTree<Key, T, value_type>::Node *fir,
              value_type sec) override {
    fir->node_key.second = sec.second;
  }
  bool IsMultiset() { return 0; };
};

};  // namespace s21

#include "s21_map.inc"
#endif