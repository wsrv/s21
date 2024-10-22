#include <gtest/gtest.h>

#include <iostream>
#include <stack>

#include "../s21_stack/s21_stack.h"
using namespace std;

template <typename value_type>
bool compare_stacks(s21::stack<value_type> my_stack,
                    std::stack<value_type> std_stack) {
  bool result = true;
  if (my_stack.size() == std_stack.size()) {
    while (!my_stack.empty() && !std_stack.empty()) {
      if (my_stack.top() != std_stack.top()) {
        result = false;
        break;
      }
      my_stack.pop();
      std_stack.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(stackTest, Comparestacks) {
  s21::stack<int> my_stack({1, 3, 10, -5, 20});
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(3);
  std_stack.push(10);
  std_stack.push(-5);
  std_stack.push(20);
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
  std_stack.push(20);
  EXPECT_FALSE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest, Comparestacks_2) {
  s21::stack<int> my_stack({1, 3, 10, -5, 20});
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(3);
  std_stack.push(10);
  std_stack.push(-5);
  std_stack.push(100);
  EXPECT_FALSE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest, DefaultConstructor) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(my_stack.size(), 0);
  EXPECT_TRUE(my_stack.empty());
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest, InitializerstackConstructor) {
  s21::stack<int> my_stack{1, 2, 3, 7, 9};
  std::initializer_list<int> il = {1, 2, 3, 7, 9};
  std::stack<int> std_stack{il};
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest, InitializerstackConstructor_2) {
  std::initializer_list<int> b;
  s21::stack<int> my_stack{b};
  std::stack<int> std_stack{b};
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest, CopyConstructor) {
  s21::stack<int> my_stack{1, 2, 3, 7, 9};
  s21::stack<int> my_stack_copy(my_stack);
  std::initializer_list<int> il = {1, 2, 3, 7, 9};
  std::stack<int> std_stack{il};
  std::stack<int> std_stack_copy(std_stack);
  EXPECT_TRUE(compare_stacks(my_stack_copy, std_stack_copy));
}

TEST(stackTest, CopyConstructorEmpty) {
  s21::stack<int> my_stack;
  s21::stack<int> my_stack_copy(my_stack);
  std::stack<int> std_stack;
  std::stack<int> std_stack_copy(std_stack);
  EXPECT_TRUE(compare_stacks(my_stack_copy, std_stack_copy));
}

TEST(stackTest, MoveConstructor) {
  s21::stack<int> my_stack{1, 2, 3, 7, 20};
  s21::stack<int> my_stack_copy(my_stack);
  s21::stack<int> my_stack_move(std::move(my_stack));
  std::initializer_list<int> il = {1, 2, 3, 7, 20};
  std::stack<int> std_stack{il};
  std::stack<int> std_stack_copy(std_stack);
  std::stack<int> std_stack_move(std::move(std_stack));
  EXPECT_TRUE(compare_stacks(my_stack_copy, std_stack_copy));
}

TEST(stackTest, MoveConstructorEmpty) {
  s21::stack<int> my_stack;
  s21::stack<int> my_stack_copy(my_stack);
  s21::stack<int> my_stack_move(std::move(my_stack));
  std::stack<int> std_stack;
  std::stack<int> std_stack_copy(std_stack);
  std::stack<int> std_stack_move(std::move(std_stack));
  EXPECT_TRUE(compare_stacks(my_stack_copy, std_stack_copy));
}

TEST(stackTest, MoveAssignmentOperator) {
  s21::stack<int> my_stack{1, 2, 3, 7, 20};
  s21::stack<int> my_stack_copy(my_stack);
  s21::stack<int> my_stack_move = std::move(my_stack);
  std::initializer_list<int> il = {1, 2, 3, 7, 20};
  std::stack<int> std_stack{il};
  std::stack<int> std_stack_copy(std_stack);
  std::stack<int> std_stack_move = std::move(std_stack);
  EXPECT_TRUE(compare_stacks(my_stack_move, std_stack_move));
}

TEST(stackTest, MoveAssignmentOperatorEmpty) {
  s21::stack<int> my_stack;
  s21::stack<int> my_stack_copy(my_stack);
  s21::stack<int> my_stack_move = std::move(my_stack);
  std::stack<int> std_stack;
  std::stack<int> std_stack_copy(std_stack);
  std::stack<int> std_stack_move = std::move(std_stack);
  EXPECT_TRUE(compare_stacks(my_stack_move, std_stack_move));
}

TEST(stackTest, Empty) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(my_stack.empty(), std_stack.empty());
  my_stack.push(2354);
  std_stack.push(2354);
  EXPECT_EQ(my_stack.empty(), std_stack.empty());
}

TEST(stackTest, Size) {
  s21::stack<int> my_stack{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7, 8};
  std::stack<int> std_stack{il};
  EXPECT_EQ(my_stack.size(), std_stack.size());
}

TEST(stackTest, Push) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;
  my_stack.push(627);
  std_stack.push(627);
  my_stack.push(2354);
  std_stack.push(2354);
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest, Swap) {
  s21::stack<int> my_stack1{1, 2, 3, 4, 5};
  s21::stack<int> my_stack2{6, 7, 8, 9, 10, 11};
  my_stack1.swap(my_stack2);

  std::initializer_list<int> il1 = {1, 2, 3, 4, 5};
  std::initializer_list<int> il2 = {6, 7, 8, 9, 10, 11};
  std::stack<int> std_stack1{il1};
  std::stack<int> std_stack2{il2};
  std_stack1.swap(std_stack2);

  EXPECT_TRUE(compare_stacks(my_stack1, std_stack1));
  EXPECT_TRUE(compare_stacks(my_stack2, std_stack2));
}

TEST(stackTest, Swap_2) {
  s21::stack<int> my_stack1{1, 2, 99, 4, 242};
  s21::stack<int> my_stack2;
  my_stack1.swap(my_stack2);

  std::initializer_list<int> il = {1, 2, 99, 4, 242};
  std::stack<int> std_stack1{il};
  std::stack<int> std_stack2;
  std_stack1.swap(std_stack2);

  EXPECT_TRUE(compare_stacks(my_stack1, std_stack1));
  EXPECT_TRUE(compare_stacks(my_stack2, std_stack2));
}

TEST(stackTest2, DefaultConstructor) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(my_stack.size(), 0);
  EXPECT_TRUE(my_stack.empty());

  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest2, InitializerListConstructor) {
  s21::stack<int> my_stack{1, 2, 3, 7, 9};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(7);
  std_stack.push(9);
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest2, CopyConstructor) {
  s21::stack<int> my_stack{3, 2, 1};
  s21::stack<int> my_stack_copy(my_stack);
  std::stack<int> std_stack;
  std_stack.push(3);
  std_stack.push(2);
  std_stack.push(1);

  std::stack<int> std_stack_copy(std_stack);
  EXPECT_TRUE(compare_stacks(my_stack_copy, std_stack_copy));
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest2, CopyConstructorEmpty) {
  s21::stack<int> my_stack;
  s21::stack<int> my_stack_copy(my_stack);
  std::stack<int> std_stack;
  std::stack<int> std_stack_copy(std_stack);
  EXPECT_TRUE(compare_stacks(my_stack_copy, std_stack_copy));
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest2, MoveConstructorEmpty) {
  s21::stack<int> my_stack;
  s21::stack<int> my_stack_move = std::move(my_stack);
  std::stack<int> std_stack;
  std::stack<int> std_stack_move = std::move(std_stack);
  EXPECT_TRUE(compare_stacks(my_stack_move, std_stack_move));
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest2, MoveAssignmentOperator) {
  s21::stack<int> my_stack{1, 2, 3};
  s21::stack<int> my_stack_move = my_stack;
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_stack_move = std_stack;
  EXPECT_TRUE(compare_stacks(my_stack_move, std_stack_move));
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest2, MoveAssignmentOperatorEmpty) {
  s21::stack<int> my_stack;
  s21::stack<int> my_stack_move = my_stack;
  std::stack<int> std_stack;
  std::stack<int> std_stack_move = std_stack;
  EXPECT_TRUE(compare_stacks(my_stack_move, std_stack_move));
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest2, Front) {
  s21::stack<int> my_stack{99, 2, 3, 4, 5};
  std::stack<int> std_stack;
  std_stack.push(99);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);
  std_stack.push(5);
  EXPECT_EQ(my_stack.top(), std_stack.top());
}

TEST(stackTest2, Empty) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(my_stack.empty(), std_stack.empty());
  my_stack.push(10);
  std_stack.push(10);
  EXPECT_EQ(my_stack.empty(), std_stack.empty());
}

TEST(stackTest2, Size) {
  s21::stack<int> my_stack{1, 2, 3, 4, 5, 6, 7, 8};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);
  std_stack.push(5);
  std_stack.push(6);
  std_stack.push(7);
  std_stack.push(8);
  EXPECT_EQ(my_stack.size(), std_stack.size());
}

TEST(stackTest2, SizeEmpty) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(my_stack.size(), std_stack.size());
}

TEST(stackTest2, PopFront) {
  s21::stack<int> my_stack{1, 2, 3, 4, 5};
  my_stack.pop();
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);
  std_stack.push(5);
  std_stack.pop();
  EXPECT_TRUE(compare_stacks(my_stack, std_stack));
}

TEST(stackTest2, Swap) {
  s21::stack<int> my_stack1{1, 2, 3, 4, 5};
  s21::stack<int> my_stack2{6, 7, 8, 9, 10, 11};
  my_stack1.swap(my_stack2);

  std::stack<int> std_stack1;
  std_stack1.push(1);
  std_stack1.push(2);
  std_stack1.push(3);
  std_stack1.push(4);
  std_stack1.push(5);
  std::stack<int> std_stack2;
  std_stack2.push(6);
  std_stack2.push(7);
  std_stack2.push(8);
  std_stack2.push(9);
  std_stack2.push(10);
  std_stack2.push(11);

  std_stack1.swap(std_stack2);

  EXPECT_TRUE(compare_stacks(my_stack1, std_stack1));
  EXPECT_TRUE(compare_stacks(my_stack2, std_stack2));
}

TEST(stackTest2, Swap_2) {
  s21::stack<int> my_stack1{1, 5, 8, 100};
  s21::stack<int> my_stack2;
  my_stack1.swap(my_stack2);

  std::stack<int> std_stack1;
  std_stack1.push(1);
  std_stack1.push(5);
  std_stack1.push(8);
  std_stack1.push(100);
  std::stack<int> std_stack2;
  std_stack1.swap(std_stack2);

  EXPECT_TRUE(compare_stacks(my_stack1, std_stack1));
  EXPECT_TRUE(compare_stacks(my_stack2, std_stack2));
}
