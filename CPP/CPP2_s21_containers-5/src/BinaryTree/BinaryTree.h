#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_MAP_BINARYTREE_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_MAP_BINARYTREE_H

// #include <memory>
#include <vector>

namespace s21 {
template <typename Key, typename T, typename Value>
class BinaryTree {
 protected:
  class Node;
  class Iterator;
  class Const_Iterator;

 protected:
  Node* root;
  Node* terminal_node;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = Value;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = Const_Iterator;
  using size_type = size_t;
  using pointer = value_type*;

 public:  // Member functions
  BinaryTree();
  BinaryTree(const BinaryTree& other);
  BinaryTree(BinaryTree&& other) noexcept;
  ~BinaryTree();
  BinaryTree& operator=(const BinaryTree& other);
  BinaryTree& operator=(BinaryTree&& other) noexcept;

 public:             // Iterators
  iterator begin();  // returns an iterator to the beginning
  const_iterator begin() const;
  iterator end();  // returns an iterator to the end
  const_iterator end() const;

 public:  // Capacity
  bool empty() const;
  size_type size() const;  // const
  size_type max_size() const;

 public:  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type val);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  iterator erase(iterator it);
  void swap(BinaryTree& other) noexcept;
  void merge(BinaryTree& other);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 public:  // Lookup
  bool contains(const Key& key = Key()) const;

 protected:  // suport
  std::pair<iterator, bool> InsertOrAssign(const Key& key, const T& obj);
  Node* RotateLeft(Node* x);
  Node* RotateRight(Node* x);
  Node* Nurlanization(Node* x);
  void AddTerminalNode(Node* x, bool add);
  int GetHeight(Node* x);
  int GetBalanceFactor(Node* x);
  // virtual T GetVal(value_type val) { return T(); };
  virtual Key GetKey(value_type val) const = 0 /*{ return Key(); }*/;
  virtual void SetVal(Node* fir, value_type sec) = 0 /*{ return; }*/;
  virtual bool IsMultiset() = 0 /*{ return 0; }*/;
  std::pair<iterator, bool> InsertRecursive(Node* x, value_type val,
                                            Iterator* it_result,
                                            bool permission,
                                            bool multisetOn = false);
  void FreeTree(Node* x);
  iterator DeleteNodeAll(iterator it);
  iterator DeleteNodeRight(iterator it);
  iterator DeleteNodeLeft(iterator it);
  iterator DeleteNodeNull(iterator it);
  bool CheckBalance();
  T& Search(bool add, const Key& key);
  Node* CopyRecursive(Node* x);
  // void SimplePrintTree(typename BinaryTree<Key, T, value_type>::Node* root,
  //                      int level = 0);
  // void PrintTree(typename BinaryTree<Key, T, value_type>::Node* root,
  //                int level = 0);

 private:  // constants
  size_type MAX_SIZE = 100;

 protected:
  class Node {
   public:
    Node* left;
    Node* right;
    Node* parent;
    int balanceFactor = 0;
    value_type node_key;
    std::size_t size;

   public:
    Node()
        : left(nullptr),
          right(nullptr),
          parent(nullptr),
          balanceFactor(0),
          node_key(value_type()),
          size(0) {}

    Node(value_type val)
        : left(nullptr),
          right(nullptr),
          parent(nullptr),
          node_key(value_type(val)) {}
  };

 protected:
  class Iterator {
   public:
    friend class BinaryTree<Key, T, value_type>;
    Iterator() : node(nullptr){};
    Iterator(const Iterator& other) : node(other.node){};
    Iterator(Node* newnode) : node(newnode){};
    ~Iterator() = default;

   public:
    iterator& operator=(const iterator& it) noexcept;
    iterator& operator++() noexcept;
    iterator operator++(int);
    iterator& operator--() noexcept;
    iterator operator--(int);
    bool operator==(const iterator& it);  // const
    bool operator!=(const iterator& it);
    pointer operator->() const {
      return node ? &(node->node_key) : throw std::exception();
    };
    reference operator*() {
      if (node)
        return node->node_key;
      else
        throw std::exception();
    };

   protected:
    Node* node = nullptr;
  };

 protected:
  class Const_Iterator : public Iterator {
   public:
    friend class BinaryTree<Key, T, value_type>;
    friend class Iterator;

    Const_Iterator() : Iterator(){};
    Const_Iterator(Node* newnode) : Iterator(newnode){};
    ~Const_Iterator() = default;
    const_reference operator*() const { return Iterator::operator*(); };
  };
};
};  // namespace s21
#include "BinaryTree.inc"
#endif