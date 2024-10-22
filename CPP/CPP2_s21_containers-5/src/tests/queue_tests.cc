#include <gtest/gtest.h>

#include <iostream>
#include <queue>

#include "../s21_queue/s21_queue.h"
using namespace std;

template <typename value_type>
bool compare_queues(s21::queue<value_type> my_queue,
                    std::queue<value_type> std_queue) {
  bool result = true;
  if (my_queue.size() == std_queue.size()) {
    while (!my_queue.empty() && !std_queue.empty()) {
      if (my_queue.front() != std_queue.front()) {
        result = false;
        break;
      }
      my_queue.pop();
      std_queue.pop();
    }
  } else {
    result = false;
  }
  return result;
}

TEST(QueueTest, CompareQueues) {
  s21::queue<int> my_queue{1, 3, 10, -5, 20};
  std::queue<int> std_queue;
  //   std::cout<<my_queue.head_->next_->next_->value_<<std::endl;
  std_queue.push(1);
  std_queue.push(3);
  std_queue.push(10);
  std_queue.push(-5);
  std_queue.push(20);
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
  std_queue.push(20);
  EXPECT_FALSE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, CompareQueues_2) {
  s21::queue<int> my_queue{1, 3, 10, -5, 20};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(3);
  std_queue.push(10);
  std_queue.push(-5);
  std_queue.push(100);
  EXPECT_FALSE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.size(), 0);
  EXPECT_TRUE(my_queue.empty());
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, InitializerqueueConstructor) {
  s21::queue<int> my_queue{1, 2, 3, 7, 9};
  std::initializer_list<int> il = {1, 2, 3, 7, 9};
  std::queue<int> std_queue{il};
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, InitializerqueueConstructor_2) {
  std::initializer_list<int> b;
  s21::queue<int> my_queue{b};
  std::queue<int> std_queue{b};
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> my_queue{1, 2, 3, 7, 9};
  s21::queue<int> my_queue_copy(my_queue);
  std::initializer_list<int> il = {1, 2, 3, 7, 9};
  std::queue<int> std_queue{il};
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueTest, CopyConstructorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> my_queue{1, 2, 3, 7, 20};
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move(std::move(my_queue));
  std::initializer_list<int> il = {1, 2, 3, 7, 20};
  std::queue<int> std_queue{il};
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move(std::move(std_queue));
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueTest, MoveConstructorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move(std::move(my_queue));
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move(std::move(std_queue));
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<int> my_queue{1, 2, 3, 7, 20};
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move = std::move(my_queue);
  std::initializer_list<int> il = {1, 2, 3, 7, 20};
  std::queue<int> std_queue{il};
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move = std::move(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_move, std_queue_move));
}

TEST(QueueTest, MoveAssignmentOperatorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  s21::queue<int> my_queue_move = std::move(my_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  std::queue<int> std_queue_move = std::move(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_move, std_queue_move));
}

TEST(QueueTest, Front) {
  s21::queue<int> my_queue{99, 2, 3, 4, 5};
  std::initializer_list<int> il = {99, 1, 3, 7, 20};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.front(), std_queue.front());
}

TEST(QueueTest, Back) {
  s21::queue<int> my_queue{1, 2, 3, 3, 4, 99};
  std::initializer_list<int> il = {99, 1, 3, 5, 4, 7, 99};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.back(), std_queue.back());
}

TEST(QueueTest, Empty) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
  my_queue.push(2354);
  std_queue.push(2354);
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Size) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue{il};
  EXPECT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueTest, Push) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  my_queue.push(627);
  std_queue.push(627);
  my_queue.push(2354);
  std_queue.push(2354);
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest, Pop) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::initializer_list<int> il = {1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue{il};
  my_queue.pop();
  my_queue.pop();
  std_queue.pop();
  std_queue.pop();
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
  EXPECT_EQ(my_queue.front(), 3);
}

TEST(QueueTest, Swap) {
  s21::queue<int> my_queue1{1, 2, 3, 4, 5};
  s21::queue<int> my_queue2{6, 7, 8, 9, 10, 11};
  my_queue1.swap(my_queue2);

  std::initializer_list<int> il1 = {1, 2, 3, 4, 5};
  std::initializer_list<int> il2 = {6, 7, 8, 9, 10, 11};
  std::queue<int> std_queue1{il1};
  std::queue<int> std_queue2{il2};
  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}

TEST(QueueTest, Swap_2) {
  s21::queue<int> my_queue1{1, 2, 99, 4, 242};
  s21::queue<int> my_queue2;
  my_queue1.swap(my_queue2);

  std::initializer_list<int> il = {1, 2, 99, 4, 242};
  std::queue<int> std_queue1{il};
  std::queue<int> std_queue2;
  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}

TEST(QueueTest2, DefaultConstructor) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.size(), 0);
  EXPECT_TRUE(my_queue.empty());

  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest2, InitializerListConstructor) {
  s21::queue<int> my_queue{1, 2, 3, 7, 9};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std_queue.push(7);
  std_queue.push(9);
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest2, CopyConstructor) {
  s21::queue<int> my_queue{1, 2, 3};
  s21::queue<int> my_queue_copy(my_queue);
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);

  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest2, CopyConstructorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_copy(my_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_copy(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_copy, std_queue_copy));
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest2, MoveConstructorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_move = std::move(my_queue);
  std::queue<int> std_queue;
  std::queue<int> std_queue_move = std::move(std_queue);
  EXPECT_TRUE(compare_queues(my_queue_move, std_queue_move));
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest2, MoveAssignmentOperator) {
  s21::queue<int> my_queue{1, 2, 3};
  s21::queue<int> my_queue_move = my_queue;
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_queue_move = std_queue;
  EXPECT_TRUE(compare_queues(my_queue_move, std_queue_move));
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}
TEST(QueueTest2, MoveAssignmentOperatorEmpty) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue_move = my_queue;
  std::queue<int> std_queue;
  std::queue<int> std_queue_move = std_queue;
  EXPECT_TRUE(compare_queues(my_queue_move, std_queue_move));
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest2, Front) {
  s21::queue<int> my_queue{99, 2, 3, 4, 5};
  std::queue<int> std_queue;
  std_queue.push(99);
  std_queue.push(2);
  std_queue.push(3);
  std_queue.push(4);
  std_queue.push(5);
  EXPECT_EQ(my_queue.front(), std_queue.front());
}

TEST(QueueTest2, Back) {
  s21::queue<int> my_queue{1, 2, 3, 4, 99};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std_queue.push(4);
  std_queue.push(99);
  EXPECT_EQ(my_queue.back(), std_queue.back());
}

TEST(QueueTest2, Empty) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
  my_queue.push(10);
  std_queue.push(10);
  EXPECT_EQ(my_queue.empty(), std_queue.empty());
}

TEST(QueueTest2, Size) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5, 6, 7, 8};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std_queue.push(4);
  std_queue.push(5);
  std_queue.push(6);
  std_queue.push(7);
  std_queue.push(8);
  EXPECT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueTest2, SizeEmpty) {
  s21::queue<int> my_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(my_queue.size(), std_queue.size());
}

TEST(QueueTest2, PopFront) {
  s21::queue<int> my_queue{1, 2, 3, 4, 5};
  my_queue.pop();
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std_queue.push(4);
  std_queue.push(5);
  std_queue.pop();
  EXPECT_TRUE(compare_queues(my_queue, std_queue));
}

TEST(QueueTest2, Swap) {
  s21::queue<int> my_queue1{1, 2, 3, 4, 5};
  s21::queue<int> my_queue2{6, 7, 8, 9, 10, 11};
  my_queue1.swap(my_queue2);

  std::queue<int> std_queue1;
  std_queue1.push(1);
  std_queue1.push(2);
  std_queue1.push(3);
  std_queue1.push(4);
  std_queue1.push(5);
  std::queue<int> std_queue2;
  std_queue2.push(6);
  std_queue2.push(7);
  std_queue2.push(8);
  std_queue2.push(9);
  std_queue2.push(10);
  std_queue2.push(11);

  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}

TEST(QueueTest2, Swap_2) {
  s21::queue<int> my_queue1{1, 5, 8, 100};
  s21::queue<int> my_queue2;
  my_queue1.swap(my_queue2);

  std::queue<int> std_queue1;
  std_queue1.push(1);
  std_queue1.push(5);
  std_queue1.push(8);
  std_queue1.push(100);
  std::queue<int> std_queue2;
  std_queue1.swap(std_queue2);

  EXPECT_TRUE(compare_queues(my_queue1, std_queue1));
  EXPECT_TRUE(compare_queues(my_queue2, std_queue2));
}
