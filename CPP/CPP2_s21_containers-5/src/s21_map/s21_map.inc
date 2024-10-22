#include <iostream>

#include "s21_map.h"

namespace s21 {
template <typename Key, typename T>
map<Key, T>::map() {}

template <typename Key, typename T>
map<Key, T>::map(const std::initializer_list<value_type>& items) {
  for (auto it = items.begin(); it != items.end(); it++) this->insert(*it);
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map&& m) {
  if (this != &m) BinaryTree<Key, T, value_type>::operator=(std::move(m));
  return *this;
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(const map& other) {
  if (this != &other) BinaryTree<Key, T, value_type>::operator=(other);
  return *this;
}

//________________________________________________Element_access______________________________________________________________
template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  return BinaryTree<Key, T, value_type>::Search(true, key);
}

template <typename Key, typename T>
T& map<Key, T>::operator[](Key&& key) {
  return BinaryTree<Key, T, value_type>::Search(true, std::move(key));
}

template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  return BinaryTree<Key, T, value_type>::Search(false, key);
}

template <typename Key, typename T>
const T& map<Key, T>::at(const Key& key) const {
  return BinaryTree<Key, T, value_type>::Search(false, key);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  return BinaryTree<Key, T, value_type>::InsertOrAssign(key, obj);
}

//________________________________________________Support______________________________________________________________

}  // namespace s21