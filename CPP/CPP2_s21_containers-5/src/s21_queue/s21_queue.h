#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_QUEUE_S21_QUEUE_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_QUEUE_S21_QUEUE_H

#include "../s21_list/s21_list.h"

namespace s21 {

template <typename T>
class queue : public list<T> {
 public:
  using value_type = typename list<T>::value_type;
  using reference = typename list<T>::reference;
  using const_reference = typename list<T>::const_reference;
  using size_type = std::size_t;

  queue() : list<T>::list(){};
  queue(std::initializer_list<value_type> const &items)
      : list<T>::list(items){};

  queue(const queue &q) : list<T>::list(q){};  //	copy constructor
  queue(queue &&q) : list<T>::list(q){};       //	move constructor
  ~queue() = default;                          //	destructor

  void push(const_reference value) {
    list<T>::push_back(value);
  };                                     // inserts element at the end
  void pop() { list<T>::pop_front(); };  // removes the first element
};

}  //  namespace s21
#endif
