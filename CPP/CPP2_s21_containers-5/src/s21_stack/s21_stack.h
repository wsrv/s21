#ifndef CPP2_S21_CONTAINERS_3_SRC_S21_STACK_S21_STACK_H
#define CPP2_S21_CONTAINERS_3_SRC_S21_STACK_S21_STACK_H

#include "../s21_list/s21_list.h"

namespace s21 {

template <typename T>
class stack : public list<T> {
 public:
  using value_type = typename list<T>::value_type;
  using reference = typename list<T>::reference;
  using const_reference = typename list<T>::const_reference;
  using size_type = std::size_t;

  stack() : list<T>::list(){};
  stack(std::initializer_list<value_type> const &items) : list<T>::list(items) {
    list<T>::reverse();
  };

  stack(const stack &s) : list<T>::list(s){};  //	copy constructor
  stack(stack &&s) : list<T>::list(s){};       //	move constructor
  ~stack() = default;                          //	destructor

  void push(const_reference value) {
    list<T>::push_front(value);
  };                                     // inserts element at the end
  void pop() { list<T>::pop_front(); };  // removes the first element
  const_reference top() { return list<T>::front(); };
};

}  //  namespace s21
#endif