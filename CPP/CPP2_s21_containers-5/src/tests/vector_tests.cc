#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../s21_vector/s21_vector.h"
using namespace std;

TEST(VectorTest, DefaultConstructor_EmptyVector) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, DefaultConstructor_Size) {
  s21::vector<int> v(0);
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);

  s21::vector<int> v1(200);
  EXPECT_FALSE(v1.empty());
  EXPECT_EQ(v1.size(), 200);
  for (size_t i = 0; i < v1.size(); ++i) EXPECT_EQ(v1[i], 0);
}

TEST(VectorTest, DefaultConstructor_List) {
  s21::vector<int> v{};
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);

  s21::vector<int> v1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_FALSE(v1.empty());
  EXPECT_EQ(v1.size(), 10);
  for (size_t i = 0; i < v1.size(); ++i) EXPECT_EQ(v1[i], i);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> v1;
  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);

  s21::vector<int> v3 = {1, 2, 3};
  s21::vector<int> v4(v3);
  EXPECT_EQ(v4.size(), v3.size());
  for (size_t i = 0; i < v3.size(); ++i) EXPECT_EQ(v4[i], v3[i]);
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);

  s21::vector<int> v3 = {0, 1, 2};
  s21::vector<int> v4(std::move(v3));
  EXPECT_EQ(v4.size(), 3);
  for (size_t i = 0; i < v4.size(); ++i) EXPECT_EQ(v4[i], i);
  EXPECT_TRUE(v3.empty());
}

TEST(VectorTest, Destructor) {
  s21::vector<int>* v = new s21::vector<int>();
  delete v;
  s21::vector<int>* v1 = new s21::vector<int>{1, 2, 3};
  delete v1;
}

TEST(VectorTest, MoveAssignmentOperator) {
  s21::vector<int> v1;
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0);

  s21::vector<int> v3 = {0, 1, 2};
  s21::vector<int> v4;
  v4 = std::move(v3);
  EXPECT_EQ(v4.size(), 3);
  for (size_t i = 0; i < v4.size(); ++i) EXPECT_EQ(v4[i], i);
  EXPECT_TRUE(v3.empty());

  s21::vector<int> v5;
  s21::vector<int> v6 = {4, 5, 6};
  v6 = std::move(v5);
  EXPECT_TRUE(v6.empty());
  EXPECT_EQ(v6.size(), 0);

  s21::vector<int> v7 = {0, 1, 2};
  s21::vector<int> v8 = {4, 5, 6};
  v8 = std::move(v7);
  EXPECT_EQ(v8.size(), 3);
  for (size_t i = 0; i < v8.size(); ++i) EXPECT_EQ(v8[i], i);
  EXPECT_TRUE(v7.empty());
}

TEST(VectorTest, At) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(4), 5);
  EXPECT_THROW(v.at(5), std::out_of_range);
  EXPECT_THROW(v.at(10), std::out_of_range);
}

TEST(VectorTest, IndexOperator) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
  EXPECT_THROW(v[5], std::out_of_range);
  EXPECT_THROW(v[10], std::out_of_range);
}

TEST(VectorTest, ConstIndexOperator) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
  EXPECT_THROW(v[5], std::out_of_range);
  EXPECT_THROW(v[10], std::out_of_range);
}

TEST(VectorTest, FrontConst) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.front(), 1);

  const s21::vector<int> v1;
  EXPECT_THROW(v1.front(), std::out_of_range);
}

TEST(VectorTest, BackConst) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.back(), 5);

  const s21::vector<int> v1;
  EXPECT_THROW(v1.back(), std::out_of_range);
}

TEST(VectorTest, Data) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  int* dataPtr = v.data();
  EXPECT_EQ(*dataPtr, 1);
  *dataPtr = 10;
  EXPECT_EQ(v[0], 10);

  s21::vector<int> v1;
  int* dataPtr1 = v1.data();
  EXPECT_EQ(dataPtr1, nullptr);
}

TEST(VectorTest, Begin) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  *it = 10;
  EXPECT_EQ(v[0], 10);

  s21::vector<int> v1;
  auto it1 = v1.begin();
  EXPECT_EQ(it1, v1.end());
}

TEST(VectorTest, End) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  EXPECT_EQ(*(it - 1), 5);

  s21::vector<int> v1;
  auto it1 = v1.end();
  EXPECT_EQ(it1, v1.begin());
}

TEST(VectorTest, ConstBegin) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.cbegin();
  EXPECT_EQ(*it, 1);

  const s21::vector<int> v1;
  auto it1 = v1.cbegin();
  EXPECT_EQ(it1, v1.cend());
}

TEST(VectorTest, ConstEnd) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.cend();
  EXPECT_EQ(*(it - 1), 5);

  s21::vector<int> v1;
  auto it1 = v1.cend();
  EXPECT_EQ(it1, v1.cbegin());
}

TEST(VectorTest, Empty) {
  const s21::vector<int> v;
  EXPECT_TRUE(v.empty());

  const s21::vector<int> v1 = {1, 2, 3};
  EXPECT_FALSE(v1.empty());
}

TEST(VectorTest, Size) {
  const s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);

  const s21::vector<int> v1 = {1, 2, 3};
  EXPECT_EQ(v1.size(), 3);
}

TEST(VectorTest, MaxSize) {
  const s21::vector<int> v;
  EXPECT_GT(v.max_size(), 0);
}

TEST(VectorTest, Capacity) {
  const s21::vector<int> v;
  EXPECT_EQ(v.capacity(), 0);

  const s21::vector<int> v1 = {1, 2, 3};
  EXPECT_GE(v1.capacity(), v1.size());
}

TEST(VectorTest, Reserve) {
  s21::vector<int> v;
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
  std::vector<int> v_o;
  v_o.reserve(10);
  EXPECT_EQ(v.capacity(), v_o.capacity());
  s21::vector<int> v1 = {0, 1, 2, 3, 4, 5};
  std::vector<int> v_o1 = {0, 1, 2, 3, 4, 5};

  v1.reserve(3);
  v_o1.reserve(3);
  for (size_t i = 0; i < v1.size(); ++i) EXPECT_EQ(v1[i], i);
  EXPECT_EQ(v1.capacity(), 6);
  // EXPECT_EQ(v1.capacity(), v_o1.capacity());
}

TEST(VectorTest, ShrinkToFit) {
  s21::vector<int> v;
  v.shrink_to_fit();
  std::vector<int> vo;
  vo.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.capacity(), vo.capacity());

  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> vo1 = {1, 2, 3, 4, 5};
  v1.pop_back();
  v1.shrink_to_fit();
  vo1.pop_back();
  vo1.shrink_to_fit();
  EXPECT_EQ(v1.capacity(), 4);
  EXPECT_EQ(v1.capacity(), vo1.capacity());
}

TEST(VectorTest, Clear) {
  s21::vector<int> v;
  std::vector<int> vo;
  v.clear();
  vo.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.size(), vo.size());

  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> vo1 = {1, 2, 3, 4, 5};
  v1.clear();
  vo1.clear();
  EXPECT_TRUE(v1.empty());
  EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, Insert) {
  s21::vector<int> v = {2, 3, 4};
  auto it = v.insert(v.begin(), 1);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(*it, 1);

  s21::vector<int> v1 = {1, 3, 4};
  auto it1 = v1.insert(v1.begin() + 1, 2);
  EXPECT_EQ(v1.size(), 4);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(*it1, 2);

  s21::vector<int> v2 = {1, 2, 3};
  auto it2 = v2.insert(v2.end(), 4);
  EXPECT_EQ(v2.size(), 4);
  EXPECT_EQ(v2[3], 4);
  EXPECT_EQ(*it2, 4);

  s21::vector<int> v3;
  auto it3 = v3.insert(v3.begin(), 1);
  EXPECT_EQ(v3.size(), 1);
  EXPECT_EQ(v3[0], 1);
  EXPECT_EQ(*it3, 1);
}

TEST(VectorTest, Erase) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.erase(v.begin());
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 2);

  s21::vector<int> v1 = {1, 2, 3, 4};
  v1.erase(v1.begin() + 1);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[1], 3);

  s21::vector<int> v2 = {1, 2, 3, 4};
  v2.erase(v2.end() - 1);
  EXPECT_EQ(v2.size(), 3);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, PushBack) {
  s21::vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v[0], 1);

  s21::vector<int> v1 = {1, 2, 3};
  v1.push_back(4);
  EXPECT_EQ(v1.size(), 4);
  EXPECT_EQ(v1[3], 4);
}

TEST(VectorTest, PopBack) {
  s21::vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.back(), 2);

  s21::vector<int> v1;
  v1.pop_back();
  EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, Swap) {
  s21::vector<int> v1 = {1, 2};
  s21::vector<int> v2 = {3, 4};
  v1.swap(v2);
  EXPECT_EQ(v1.size(), 2);
  EXPECT_EQ(v2.size(), 2);
  EXPECT_EQ(v1[0], 3);
  EXPECT_EQ(v1[1], 4);
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);

  s21::vector<int> v3;
  s21::vector<int> v4 = {1, 2};
  v3.swap(v4);
  EXPECT_EQ(v3.size(), 2);
  EXPECT_FALSE(v3.empty());
  EXPECT_EQ(v3[0], 1);
  EXPECT_EQ(v3[1], 2);
  EXPECT_EQ(v4.size(), 0);
  EXPECT_TRUE(v4.empty());

  s21::vector<int> v5 = {1, 2};
  s21::vector<int> v6;
  v5.swap(v6);
  EXPECT_EQ(v6.size(), 2);
  EXPECT_FALSE(v6.empty());
  EXPECT_EQ(v6[0], 1);
  EXPECT_EQ(v6[1], 2);
  EXPECT_EQ(v5.size(), 0);
  EXPECT_TRUE(v5.empty());

  s21::vector<int> v7;
  s21::vector<int> v8;
  v7.swap(v8);
  EXPECT_EQ(v7.size(), 0);
  EXPECT_TRUE(v7.empty());
  EXPECT_EQ(v8.size(), 0);
  EXPECT_TRUE(v8.empty());
}

TEST(VectorTest, InsertMany) {
  s21::vector<int> vec = {1, 2, 3, 7, 8};
  s21::vector<int>::const_iterator pos = vec.cbegin() + 3;
  vec.insert_many(pos, 4, 5, 6);
  EXPECT_EQ(vec.size(), 8);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 8);
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> vec = {1, 2, 3};
  vec.insert_many_back(4, 5, 6);
  EXPECT_EQ(vec.size(), 6);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
}
