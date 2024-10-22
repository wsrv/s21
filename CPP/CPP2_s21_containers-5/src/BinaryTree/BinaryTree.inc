#include <iostream>

#include "BinaryTree.h"

//________________________________________________Member_functions______________________________________________________________

namespace s21 {
template <typename Key, typename T, typename Value>
BinaryTree<Key, T, Value>::BinaryTree() {
  terminal_node = new Node();
  root = terminal_node;
}

template <typename Key, typename T, typename Value>
BinaryTree<Key, T, Value>::BinaryTree(const BinaryTree& other) {
  terminal_node = new Node();
  root = terminal_node;
  root = CopyRecursive(other.root);
}

template <typename Key, typename T, typename Value>
BinaryTree<Key, T, Value>::BinaryTree(BinaryTree&& other) noexcept {
  root = other.root;
  terminal_node = other.terminal_node;
  other.root = nullptr;
  other.terminal_node = nullptr;
}

template <typename Key, typename T, typename Value>
BinaryTree<Key, T, Value>& BinaryTree<Key, T, Value>::operator=(
    BinaryTree&& other) noexcept {
  if (this != &other) {
    root = other.root;
    other.root = nullptr;
  }
  return *this;
}

template <typename Key, typename T, typename Value>
BinaryTree<Key, T, Value>& BinaryTree<Key, T, Value>::operator=(
    const BinaryTree& other) {
  if (this != &other) {
    BinaryTree temp(other);
    FreeNode(root);
    *this = std::move(temp);
  }
  return *this;
}

template <typename Key, typename T, typename Value>
BinaryTree<Key, T, Value>::~BinaryTree() {
  clear();
  if (root) delete root;
}

//________________________________________________Modifiers______________________________________________________________

template <typename Key, typename T, typename Value>
void BinaryTree<Key, T, Value>::clear() {
  if (!root) return;
  FreeTree(root);
  root = terminal_node;
  root->parent = nullptr;
}

template <typename Key, typename T, typename Value>
std::pair<typename BinaryTree<Key, T, Value>::iterator, bool>
BinaryTree<Key, T, Value>::insert(const value_type val) {
  if (size() == MAX_SIZE) throw std::length_error("Tree is full");

  Iterator it_result = Iterator(root);
  std::pair<typename BinaryTree<Key, T, Value>::iterator, bool> res;
  if (root == terminal_node) root = nullptr;

  AddTerminalNode(root, false);
  res = InsertRecursive(root, val, &it_result, false, IsMultiset());
  res.first = it_result;
  AddTerminalNode(root, true);
  return res;
}

template <typename Key, typename T, typename Value>
std::pair<typename BinaryTree<Key, T, Value>::iterator, bool>
BinaryTree<Key, T, Value>::insert(const Key& key, const T& obj) {
  std::pair<Key, T> val = {key, obj};
  return insert(val);
}

template <typename Key, typename T, typename Value>
std::pair<typename BinaryTree<Key, T, Value>::iterator, bool>
BinaryTree<Key, T, Value>::InsertOrAssign(const Key& key, const T& obj) {
  std::pair<Key, T> val = {key, obj};

  Iterator it_result = Iterator(root);
  std::pair<typename BinaryTree<Key, T, Value>::iterator, bool> res;
  if (root == terminal_node) root = nullptr;

  AddTerminalNode(root, false);
  res = InsertRecursive(root, val, &it_result, true);
  res.first = it_result;
  AddTerminalNode(root, true);
  return res;
}

template <typename Key, typename T, typename Value>
template <class... Args>
std::vector<std::pair<typename BinaryTree<Key, T, Value>::iterator, bool>>
BinaryTree<Key, T, Value>::insert_many(Args&&... args) {
  std::vector<std::pair<typename BinaryTree<Key, T, Value>::iterator, bool>>
      vec;
  for (const auto& arg : {args...}) vec.push_back(this->insert(arg));

  return vec;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::iterator BinaryTree<Key, T, Value>::erase(
    iterator it) {
  if (!it.node) throw std::out_of_range("Iterator not found");
  if (it.node == terminal_node) return Iterator(terminal_node);

  auto lef = it.node->left;
  auto rig = it.node->right;
  if (lef && rig)
    it = DeleteNodeAll(it);
  else if (!lef && rig)
    it = DeleteNodeRight(it);
  else if (lef && !rig)
    it = DeleteNodeLeft(it);
  else if (!lef && !rig)
    it = DeleteNodeNull(it);

  GetBalanceFactor(root);
  while (!CheckBalance()) {
    for (auto it1 = Iterator(begin()); it1.node != terminal_node; it1++)
      it1.node = Nurlanization(it1.node);
  }
  return it;
}

template <typename Key, typename T, typename Value>
void BinaryTree<Key, T, Value>::swap(BinaryTree& other) noexcept {
  auto first = other.root;
  other.root = root;
  root = first;

  std::swap(terminal_node, other.terminal_node);
}

template <typename Key, typename T, typename Value>
void BinaryTree<Key, T, Value>::merge(BinaryTree& other) {
  for (iterator it = other.begin(); it != other.end();) {
    if (insert(*it).second)
      it = other.erase(it);
    else
      it++;
  }
}

//________________________________________________Lookup______________________________________________________________
template <typename Key, typename T, typename Value>
bool BinaryTree<Key, T, Value>::contains(const Key& key) const {
  auto x = root;
  while (x && x != terminal_node) {
    if (key == GetKey(x->node_key)) return true;
    if (key > GetKey(x->node_key))
      x = x->right;
    else
      x = x->left;
  }
  return false;
}
//________________________________________________Iterators______________________________________________________________
template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::iterator
BinaryTree<Key, T, Value>::begin() {
  if (!root) return root;
  iterator beg(root);
  while (beg.node->left) beg.node = beg.node->left;
  return beg;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::const_iterator
BinaryTree<Key, T, Value>::begin() const {
  if (!root) return root;
  const_iterator beg(root);
  while (beg.node->left) beg.node = beg.node->left;
  return beg;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::iterator BinaryTree<Key, T, Value>::end() {
  auto x = root;
  while (x->right) x = x->right;
  return x;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::const_iterator
BinaryTree<Key, T, Value>::end() const {
  auto x = root;
  while (x->right) x = x->right;
  return x;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::Iterator&
BinaryTree<Key, T, Value>::Iterator::operator++() noexcept {
  if (!node) return *this;

  if (node->right) {
    node = node->right;
    while (node->left) node = node->left;
  } else {
    if (node->parent->right == node)
      while (node->parent && node->parent->right == node) node = node->parent;

    if (node->parent)
      node = node->parent;
    else
      while (node->right) node = node->right;
  }
  return *this;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::Iterator
BinaryTree<Key, T, Value>::Iterator::operator++(int) {
  if (!node) return *this;
  Iterator temp(*this);
  operator++();
  return temp;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::Iterator&
BinaryTree<Key, T, Value>::Iterator::operator--() noexcept {
  if (!node) return *this;

  if (node->left) {
    node = node->left;
    while (node->right) node = node->right;
  } else {
    if (node->parent->left == node)
      while (node->parent->parent && node->parent->left == node) {
        node = node->parent;
      }
    node = node->parent;
  }
  return *this;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::Iterator
BinaryTree<Key, T, Value>::Iterator::operator--(int) {
  if (!node) return Iterator(*this);
  Iterator temp = *this;
  operator--();
  return temp;
}

template <typename Key, typename T, typename Value>
bool BinaryTree<Key, T, Value>::Iterator::operator==(const iterator& it) {
  return node == it.node;
}

template <typename Key, typename T, typename Value>
bool BinaryTree<Key, T, Value>::Iterator::operator!=(const iterator& it) {
  return node != it.node;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::Iterator&
BinaryTree<Key, T, Value>::Iterator::operator=(const iterator& it) noexcept {
  node = it.node;
  return *this;
}

//________________________________________________Capacity______________________________________________________________
template <typename Key, typename T, typename Value>
bool BinaryTree<Key, T, Value>::empty() const {
  return !root->left && !root->right;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::size_type BinaryTree<Key, T, Value>::size()
    const {
  size_type res = 0;
  if (root)
    for (auto it = begin(); it != end(); it++) res++;
  return res;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::size_type
BinaryTree<Key, T, Value>::max_size() const {
  return MAX_SIZE;
}

//________________________________________________Support______________________________________________________________
template <typename Key, typename T, typename Value>
std::pair<typename BinaryTree<Key, T, Value>::iterator, bool>
BinaryTree<Key, T, Value>::InsertRecursive(Node* x, value_type val,
                                           Iterator* it_result, bool permission,
                                           bool multisetOn) {
  std::pair<iterator, bool> pair;
  if (!x || x == terminal_node) {
    Node* new_node = new Node(val);
    if (!root || root == terminal_node) root = new_node;
    it_result->node = new_node;
    return std::pair<iterator, bool>(Iterator(new_node), true);
  }
  if (GetKey(val) == GetKey(x->node_key)) {
    if (!permission) {
      if (multisetOn) {
        pair =
            InsertRecursive(x->right, val, it_result, permission, multisetOn);
        x->right = pair.first.node;
        x->right->parent = x;
      } else {
        it_result->node = x;
        return std::pair<iterator, bool>(Iterator(x), false);
      }
    } else
      SetVal(x, val);  // x->node_key.second = val.second;
  } else {
    if (GetKey(val) < GetKey(x->node_key)) {
      pair = InsertRecursive(x->left, val, it_result, permission, multisetOn);
      x->left = pair.first.node;
      x->left->parent = x;
    }

    if (GetKey(val) > GetKey(x->node_key)) {
      pair = InsertRecursive(x->right, val, it_result, permission, multisetOn);
      x->right = pair.first.node;
      x->right->parent = x;
    }
  }

  GetBalanceFactor(x);

  return std::pair<iterator, bool>(Iterator(Nurlanization(x)), pair.second);
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::Node*
BinaryTree<Key, T, Value>::Nurlanization(Node* x) {
  if (x->balanceFactor < -1) {
    if (x->left->balanceFactor > 0) x->left = RotateLeft(x->left);
    return RotateRight(x);
  }
  if (x->balanceFactor > 1) {
    if (x->right->balanceFactor < 0) x->right = RotateRight(x->right);
    return RotateLeft(x);
  }
  return x;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::Node* BinaryTree<Key, T, Value>::RotateLeft(
    Node* x) {
  Node* p = x->right;
  if (x->parent && x->parent->left == x) x->parent->left = p;
  if (x->parent && x->parent->right == x) x->parent->right = p;
  p->parent = x->parent;
  x->right = p->left;
  p->left = x;
  x->parent = p;
  if (p->parent == nullptr) root = p;
  GetBalanceFactor(p);
  GetBalanceFactor(x);
  return p;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::Node*
BinaryTree<Key, T, Value>::RotateRight(Node* x) {
  Node* q = x->left;
  if (x->parent && x->parent->left == x) x->parent->left = q;
  if (x->parent && x->parent->right == x) x->parent->right = q;
  q->parent = x->parent;
  x->left = q->right;
  q->right = x;
  x->parent = q;
  if (!q->parent) root = q;
  GetBalanceFactor(q);
  GetBalanceFactor(x);
  return q;
}

template <typename Key, typename T, typename Value>
int BinaryTree<Key, T, Value>::GetBalanceFactor(Node* node) {
  if (!node || node == terminal_node) return 0;
  if (node->left) node->left->parent = node;
  if (node->right) node->right->parent = node;

  int left_height = GetHeight(node->left);
  int right_height = GetHeight(node->right);
  node->balanceFactor = -left_height + right_height;
  GetBalanceFactor(node->left);
  GetBalanceFactor(node->right);
  return node->balanceFactor;
}

template <typename Key, typename T, typename Value>
int BinaryTree<Key, T, Value>::GetHeight(Node* node) {
  if (!node || node == terminal_node) return 0;
  int left_height = GetHeight(node->left);
  int right_height = GetHeight(node->right);
  return 1 + std::max(left_height, right_height);
}

template <typename Key, typename T, typename Value>
void BinaryTree<Key, T, Value>::AddTerminalNode(Node* node, bool add) {
  if (!node || node == terminal_node) return;

  while (node->right) node = node->right;

  if (add) {
    node->right = terminal_node;
    terminal_node->parent = node;
  } else
    node->parent->right = nullptr;
}

template <typename Key, typename T, typename Value>
void BinaryTree<Key, T, Value>::FreeTree(Node* x) {
  if (!x || x == terminal_node) return;
  FreeTree(x->left);
  FreeTree(x->right);
  delete x;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::iterator
BinaryTree<Key, T, Value>::DeleteNodeAll(iterator it) {
  auto nod = it.node;
  auto lef = it.node->left;
  auto rig = it.node->right;
  auto par = it.node;
  if (it.node->parent) par = it.node->parent;
  nod = rig;

  if (!nod->left) {
    if (it.node == it.node->parent->left) {
      par->left = nod;
    }
    if (it.node == it.node->parent->right) par->right = nod;
    nod->parent = par;

    nod->left = lef;
    lef->parent = nod;

  } else {
    while (nod->left) nod = nod->left;
    if (it.node == root) {
      nod->parent->left = nullptr;
      root = nod;
      nod->parent = nullptr;
    } else if (it.node == it.node->parent->left) {
      nod->parent->left = nullptr;
      nod->parent = par;
      par->left = nod;
    } else if (it.node == it.node->parent->right) {
      nod->parent->left = nullptr;
      nod->parent = par;
      par->right = nod;
    }
    if (nod->right) {
      nod->right->right = rig;
      rig->parent = nod->right;
    } else {
      nod->right = rig;
      rig->parent = nod;
    }
    lef->parent = nod;
    nod->left = lef;
  }

  delete it.node;

  return Iterator(nod);
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::iterator
BinaryTree<Key, T, Value>::DeleteNodeRight(iterator it) {
  auto nod = it.node;
  auto par = it.node->parent;
  auto lef = it.node->left;
  auto rig = it.node->right;

  if (it.node->parent) {
    nod = rig;
    if (it.node->parent->right == it.node) it.node->parent->right = nod;
    if (it.node->parent->left == it.node) it.node->parent->left = nod;

    nod->parent = par;
    nod->left = lef;

  } else {
    root = it.node->right;
    it.node->right->parent = nullptr;
    nod = root;
  }
  delete it.node;
  return Iterator(nod);
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::iterator
BinaryTree<Key, T, Value>::DeleteNodeLeft(iterator it) {
  auto nod = it.node;
  auto par = it.node->parent;
  auto rig = it.node->right;
  if (it.node->parent) {
    if (it.node->parent->right == it.node)
      it.node->parent->right = it.node->left;
    if (it.node->parent->left == it.node) it.node->parent->left = it.node->left;
    nod = par;
    it.node->left->parent = nod;
  } else {
    root = it.node->left;
    it.node->left->parent = nullptr;
    nod = it.node->left;
    nod->right = rig;
    rig->parent = nod;
  }
  delete it.node;
  return Iterator(nod);
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::iterator
BinaryTree<Key, T, Value>::DeleteNodeNull(iterator it) {
  auto nod = it.node;
  if (it.node->parent) {
    if (it.node->parent->right == it.node)
      it.node->parent->right = it.node->right;
    else
      it.node->parent->left = it.node->left;

    while (nod->parent &&
           (GetKey(nod->parent->node_key) < GetKey(it.node->node_key)))
      nod = nod->parent;
    nod = nod->parent;

  } else {
    root = it.node->right;
    nod = it.node->right;
  }

  delete it.node;
  return Iterator(nod);
}

template <typename Key, typename T, typename Value>
bool BinaryTree<Key, T, Value>::CheckBalance() {
  iterator it = begin();
  for (iterator it = begin(); it != end(); it++)
    if (abs(GetBalanceFactor(it.node)) > 1) return false;
  return true;
}

template <typename Key, typename T, typename Value>
typename BinaryTree<Key, T, Value>::Node*
BinaryTree<Key, T, Value>::CopyRecursive(Node* x) {
  if (!x || x == terminal_node) return nullptr;
  Node* next = new Node(x->node_key);
  next->left = CopyRecursive(x->left);
  if (next->left) next->left->parent = next;
  next->right = CopyRecursive(x->right);
  if (next->right) next->right->parent = next;
  return next;
}

template <typename Key, typename T, typename Value>
T& BinaryTree<Key, T, Value>::Search(bool add, const Key& key) {
  auto x = root;
  while (x && x != terminal_node) {
    if (key == x->node_key.first) return x->node_key.second;
    if (key > x->node_key.first)
      x = x->right;
    else
      x = x->left;
  }
  if (add) {
    auto res = insert(Key(key), T());
    return res.first.node->node_key.second;
  } else
    throw std::out_of_range("Key not found");
  return root->node_key.second;
}

// template <typename Key, typename T, typename Value>
// void BinaryTree<Key, T, Value>::SimplePrintTree(
//     typename BinaryTree<Key, T, Value>::Node* x, int level) {
//   if (x == nullptr) return;
//   SimplePrintTree(x->right, level + 3);
//   for (int i = 0; i < level; i++) std::cout << " ";
//   std::cout << "\033[92m" << GetKey(x->node_key) << "\033[0m["
//             << GetVal(x->node_key) << "]" << std::endl;
//   SimplePrintTree(x->left, level + 3);
// }

// template <typename Key, typename T, typename Value>
// void BinaryTree<Key, T, Value>::PrintTree(
//     typename BinaryTree<Key, T, value_type>::Node* x, int level) {
//   if (x == nullptr) return;
//   PrintTree(x->right, level + 3);
//   for (int i = 0; i < level; i++) std::cout << " ";
//   if (!x->parent && (!x->left && !x->right)) {
//     std::cout << "\033[92m" << GetVal(x->node_key) << "\033[0m[NULL]"
//               << "[NULL]"
//               << "[NULL]" << std::endl;
//   } else if (x->parent && !x->left && !x->right) {
//     std::cout << "\033[92m" << GetVal(x->node_key) << "\033[0m["
//               << GetVal(x->parent->node_key) << "][NULL]"
//               << "[NULL]" << std::endl;
//   } else if (x->parent && x->left && !x->right) {
//     std::cout << "\033[92m" << GetVal(x->node_key) << "\033[0m["
//               << GetVal(x->parent->node_key) << "]["
//               << GetVal(x->left->node_key) << "][NULL]" << std::endl;
//   } else if (x->parent && !x->left && x->right) {
//     std::cout << "\033[92m" << GetVal(x->node_key) << "\033[0m["
//               << GetVal(x->parent->node_key) << "][NULL]["
//               << GetVal(x->right->node_key) << "]" << std::endl;
//   } else if (x->parent && x->left && x->right) {
//     std::cout << "\033[92m" << GetVal(x->node_key) << "\033[0m["
//               << GetVal(x->parent->node_key) << "]["
//               << GetVal(x->left->node_key) << "][" <<
//               GetVal(x->right->node_key)
//               << "]" << std::endl;
//   } else if (!x->parent && x->left && x->right) {
//     std::cout << "\033[92m" << GetVal(x->node_key) << "\033[0m[NULL]["
//               << GetVal(x->left->node_key) << "][" <<
//               GetVal(x->right->node_key)
//               << "]" << std::endl;
//   } else if (!x->parent && !x->left && x->right) {
//     std::cout << "\033[92m" << GetVal(x->node_key) << "\033[0m[NULL][NULL]["
//               << GetVal(x->right->node_key) << "]" << std::endl;
//   } else if (!x->parent && x->left && !x->right) {
//     std::cout << "\033[92m" << GetVal(x->node_key) << "\033[0m[NULL]["
//               << GetVal(x->left->node_key) << "][NULL]" << std::endl;
//   }
//   PrintTree(x->left, level + 3);
// }
}  // namespace s21