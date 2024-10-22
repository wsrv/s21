#include <iostream>

#include "s21_multiset.h"

namespace s21 {
template <typename Key>
multiset<Key>::multiset() {}

template <typename Key>
multiset<Key>::multiset(const std::initializer_list<value_type>& items) {
  for (auto it = items.begin(); it != items.end(); it++) this->insert(Key(*it));
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& m) {
  if (this != &m) BinaryTree<Key, Key, Key>::operator=(std::move(m));
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset& other) {
  if (this != &other) BinaryTree<Key, Key, Key>::operator=(other);
  return *this;
}

//________________________________________________Lookup______________________________________________________________
template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  return search(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(const Key& key) {
  return BinaryTree<Key, Key, Key>::insert(key).first;
}
//________________________________________________Support______________________________________________________________

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::search(const Key& key) {
  auto root = BinaryTree<Key, Key, Key>::root;
  auto x = root;
  auto terminal_node = BinaryTree<Key, Key, Key>::terminal_node;

  while (x && x != terminal_node) {
    if (key == x->node_key) return iterator(x);
    if (key > x->node_key) {
      SetVal(root, key);
      x = x->right;
    } else {
      x = x->left;
      SetVal(root, key);
    }
  }
  return iterator(terminal_node);
}

}  // namespace s21