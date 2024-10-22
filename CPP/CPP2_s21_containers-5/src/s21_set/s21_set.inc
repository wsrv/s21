#include <iostream>

#include "s21_set.h"

namespace s21 {
template <typename Key>
set<Key>::set() {}

template <typename Key>
set<Key>::set(const std::initializer_list<value_type>& items) {
  for (auto it = items.begin(); it != items.end(); it++) this->insert(Key(*it));
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& m) {
  if (this != &m) BinaryTree<Key, Key, Key>::operator=(std::move(m));
  return *this;
}

template <typename Key>
set<Key>& set<Key>::operator=(const set& other) {
  if (this != &other) BinaryTree<Key, Key, Key>::operator=(other);
  return *this;
}

//________________________________________________Lookup______________________________________________________________
template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  return search(key);
}

//________________________________________________Support______________________________________________________________

template <typename Key>
typename set<Key>::iterator set<Key>::search(const Key& key) {
  auto root = BinaryTree<Key, Key, Key>::root;
  auto x = root;
  auto terminal_node = BinaryTree<Key, Key, Key>::terminal_node;

  while (x && x != terminal_node) {
    if (key == x->node_key) return iterator(x);
    if (key > x->node_key) {
      SetVal(root, key);
      x = x->right;
    } else {
      SetVal(root, key);
      x = x->left;
    }
  }
  return iterator(terminal_node);
}

}  // namespace s21