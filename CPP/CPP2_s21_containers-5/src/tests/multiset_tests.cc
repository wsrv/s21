#include <gtest/gtest.h>

#include <set>

#include "../s21_containersplus.h"

template <typename T>
struct TestMultisetGroup : public testing::Test {
  using MultisetType = T;
};

using MultisetType = ::testing::Types<int, float, double, char>;
TYPED_TEST_CASE(TestMultisetGroup, MultisetType);
//________________________________________________Member_functions__________________________________________________

TYPED_TEST(TestMultisetGroup, Initializer_list) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a = {
      1, 2, 3, 4, 5, 6, 6, 6, 6, 5};
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b = {
      1, 2, 3, 4, 5, 6, 6, 6, 6, 5};
  auto it1 = a.begin() = a.begin();
  auto it2 = b.begin();
  for (; it1 != a.end(); it1++, it2++) EXPECT_EQ(*it1, *it2);
  // a.SimpleprintTree(a.root);
  EXPECT_EQ(a.size(), b.size());
}

TYPED_TEST(TestMultisetGroup, ConstructorCopy) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a = {1, 1,
                                                                          1, 2};
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b = {1, 1,
                                                                          1, 2};
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a_copy(a);
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b_copy(b);
  EXPECT_EQ(a_copy.size(), b_copy.size());
  auto it1 = a.begin() = a_copy.begin();
  auto it2 = b_copy.begin();
  for (; it1 != a_copy.end(); ++it1, ++it2) EXPECT_TRUE((*it1) == (*it2));

  // a.SimpleprintTree(a.root);
}

TYPED_TEST(TestMultisetGroup, ConstructorMovemultiset) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a = {
      1, 2, 1, 4, 1, 6};
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b = {
      1, 2, 1, 4, 1, 6};
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a_copy =
      std::move(a);
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b_copy =
      std::move(b);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a_copy.size(), b_copy.size());
  auto it1 = a.begin() = a_copy.begin();
  auto it2 = b_copy.begin();
  for (; it1 != a_copy.end(); ++it1, ++it2) EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(a.size(), b.size());
  // a_copy.printTree(a_copy.root);
}

//________________________________________________Iterators__________________________________________________

TYPED_TEST(TestMultisetGroup, Begin) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a = {
      'N', 'U', 'N', 'U', 'U', 'N'};
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b = {
      'N', 'U', 'N', 'U', 'U', 'N'};
  auto it1 = a.begin();
  auto it2 = b.begin();
  ASSERT_EQ(*it1, *it2);
  for (; it1 != a.end(); it1++, it2++) ASSERT_EQ(*it1, *it2);
  ASSERT_EQ(a.size(), b.size());
}

TYPED_TEST(TestMultisetGroup, End) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a;
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b;
  auto it1 = a.begin();
  auto it2 = b.begin();

  for (int i = 1; i < 50; i++) ASSERT_EQ(*a.insert(1), *b.insert(1));

  for (it1 = a.begin(), it2 = b.begin(); it2 != b.end(); it1++, it2++)
    ASSERT_EQ(*a.find(*it1), *b.find(*it2));

  it1 = a.begin();
  it2 = b.begin();

  it1++;
  it2++;
  ASSERT_EQ(*it1, *it2);
  it1++;
  it2++;
  ASSERT_EQ(*it1, *it2);
  it1++;
  it2++;
  ASSERT_EQ(*it1, *it2);
  --it1;
  --it2;
  ASSERT_EQ(*it1, *it2);
  --it1;
  --it2;
  ASSERT_EQ(*it1, *it2);
  --it1;
  --it2;
  ASSERT_EQ(*it1, *it2);
  it1++;
  it2++;
  ASSERT_EQ(*it1, *it2);
  ASSERT_EQ(*(++it1), *(++it2));
  ASSERT_EQ(*(++it1), *(++it2));
  ASSERT_EQ(*(it1--), *(it2--));

  // a.SimpleprintTree(a.root);
}

//________________________________________________Capacity__________________________________________________
TYPED_TEST(TestMultisetGroup, Empty) {
  s21::multiset<std::string> a;
  std::multiset<std::string> b;
  ASSERT_EQ(a.empty(), b.empty());
  a.insert("Nurlan");
  b.insert("Nurlan");
  ASSERT_EQ(a.empty(), b.empty());
  s21::multiset<std::string>::iterator it1 = a.begin();
  std::multiset<std::string>::iterator it2 = b.begin();
  a.erase(it1);
  b.erase(it2);
  ASSERT_EQ(a.empty(), b.empty());
  // a.printTree(a.root);
}

TYPED_TEST(TestMultisetGroup, Size) {
  s21::multiset<std::string> a;
  std::multiset<std::string> b;
  ASSERT_EQ(a.size(), b.size());
  for (int i = 0; i < 6; i++) {
    a.insert("Nurlan");
    b.insert("The Best");
  }
  ASSERT_EQ(a.size(), b.size());
}

//________________________________________________Modifiers_________________________________________________

TYPED_TEST(TestMultisetGroup, Clear) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a;
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b;
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
  a.insert(1);
  b.insert(1);
  EXPECT_EQ(a.empty(), b.empty());
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
}

TYPED_TEST(TestMultisetGroup, Insert_int) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a;
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b;
  auto it1 = a.begin();
  auto it2 = b.begin();

  for (int i = 1; i < 50; i++) {
    int x = rand() % 100;
    ASSERT_EQ(*a.insert(x), *b.insert(x));
  }
  ASSERT_EQ(*a.insert(99), *b.insert(99));

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);

  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TYPED_TEST(TestMultisetGroup, Insert_char) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a;
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b;
  auto it1 = a.begin();
  auto it2 = b.begin();

  for (int i = 0; i < 50; i++) ASSERT_EQ(*a.insert('N'), *b.insert('N'));

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);

  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TYPED_TEST(TestMultisetGroup, Insert_string) {
  s21::multiset<std::string> a;
  std::multiset<std::string> b;
  s21::multiset<std::string>::iterator it1;
  std::multiset<std::string>::iterator it2;

  for (int i = 0; i < 50; i++) ASSERT_EQ(*a.insert("OK"), *b.insert("OK"));

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);

  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TYPED_TEST(TestMultisetGroup, Insert_pair) {
  s21::multiset<std::pair<int, int>> a;
  std::multiset<std::pair<int, int>> b;
  s21::multiset<std::pair<int, int>>::iterator it1;
  std::multiset<std::pair<int, int>>::iterator it2;

  for (int i = 0; i < 50; i++)
    ASSERT_EQ(*a.insert(std::pair<int, int>{1, 2}),
              *b.insert(std::pair<int, int>{1, 2}));

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++) {
    ASSERT_EQ((*it1).first, (*it2).first);
    ASSERT_EQ((*it1), (*it2));
  }
  ASSERT_EQ(a.size(), b.size());
}

namespace s21 {
class my_class {
  using value_type = std::pair<int, int>;

 public:
  value_type val;

  my_class() {
    val.first = 0;
    val.second = 0;
  }
  my_class(int x, int y) {
    val.first = x;
    val.second = y;
  }

  bool operator>(const my_class& it) { return val.first > it.val.first; };
  bool operator<(const my_class& it) { return val.first < it.val.first; };
  bool operator==(const my_class& it) { return val.first == it.val.first; };
};
}  // namespace s21

TYPED_TEST(TestMultisetGroup, Insert_my_class) {
  s21::multiset<s21::my_class> a;
  s21::multiset<s21::my_class>::iterator it1;

  for (int i = 0; i < 50; i++) {
    s21::my_class a1(10, 11);
    s21::my_class x = a1;
    *a.insert(x);
  }
  for (it1 = a.begin(); it1 != a.end(); it1++) {
    ASSERT_EQ((*it1).val.first, 10);
    ASSERT_EQ((*it1).val.second, 11);
  }
  ASSERT_EQ(a.size(), 50);
}

TEST(TestMultisetGroup, Insert_many) {
  s21::multiset<int> a;
  std::multiset<int> b;
  int x1 = 1;
  int x2 = 2;
  int x3 = 3;

  std::vector<std::pair<s21::multiset<int>::iterator, bool>> v1;
  v1 = a.insert_many(x1, x2, x3);

  std::vector<std::pair<std::multiset<int>::iterator, bool>> v2;
  v2.push_back(
      std::pair<std::multiset<int>::iterator, bool>{b.insert(x1), true});
  v2.push_back(
      std::pair<std::multiset<int>::iterator, bool>{b.insert(x2), true});
  v2.push_back(
      std::pair<std::multiset<int>::iterator, bool>{b.insert(x3), true});

  for (int i = 0; i < int(v1.size()); i++) {
    ASSERT_EQ(*v1[i].first, *v2[i].first);
    ASSERT_EQ(v1[i].second, v2[i].second);
  }
}

TYPED_TEST(TestMultisetGroup, Erase_1) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a;
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b;
  auto it1 = a.begin();
  auto it2 = b.begin();
  auto save_it1(it1);
  auto save_it2(it2);

  for (int i = 0; i < 50; i++) {
    int x = rand() % 100;
    ASSERT_EQ(*a.insert(x), *b.insert(x));
  }

  int i = 0;
  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); i++) {
    it1 = a.erase(it1);
    it2 = b.erase(it2);
    ASSERT_EQ(a.size(), b.size());
    save_it1 = it1;
    save_it2 = it2;
    for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
      ASSERT_EQ(*it1, *it2);

    it1 = save_it1;
    it2 = save_it2;
  }
  // a.printTree(a.root);
}

TYPED_TEST(TestMultisetGroup, Erase_2) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a;
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b;
  auto it1 = a.begin();
  auto it2 = b.begin();

  for (int i = 0; i < 50; i++) {
    ASSERT_EQ(*a.insert(11), *b.insert(11));
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);

  int i = 0;
  for (it1 = a.begin(), it2 = b.begin(); i < 10; i++, it1++, it2++)
    ;

  for (int j = 0; j < 10; j++) {
    it1 = a.erase(it1);
    it2 = b.erase(it2);
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
  // a.printTree(a.root);
  // a.SimpleprintTree(a.root);
}

TYPED_TEST(TestMultisetGroup, Swap) {
  s21::multiset<double> a1;
  s21::multiset<double> a2;
  std::multiset<double> b1;
  std::multiset<double> b2;
  s21::multiset<double>::iterator it1;
  std::multiset<double>::iterator it2;

  for (int i = 0, j = 49; i < 50; i++, j--) {
    double x = j / 10.;
    ASSERT_EQ(*a1.insert(x), *b1.insert(x));
  }
  for (int i = 0, j = 49; i < 50; i++, j--) {
    double x = j << 1;
    ASSERT_EQ(*a2.insert(x), *b2.insert(x));
  }

  for (it1 = a1.begin(), it2 = b1.begin(); it1 != a1.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);

  a1.swap(a2);
  b1.swap(b2);

  for (it1 = a1.begin(), it2 = b1.begin(); it1 != a1.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);
  for (it1 = a2.begin(), it2 = b2.begin(); it1 != a2.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);

  ASSERT_EQ(a1.size(), b1.size());
  ASSERT_EQ(a2.size(), b2.size());
  // a1.printTree(a1.root);
}

TYPED_TEST(TestMultisetGroup, Merge) {
  s21::multiset<double> a1;
  s21::multiset<double> a2;
  s21::multiset<double>::iterator it1;
  for (int i = 0; i <= 10; i++) a1.insert(i);

  for (int i = 5; i <= 15; i++) a2.insert(i);

  a1.merge(a2);
  int i = 0;
  for (it1 = a1.begin(); i < 5; i++, it1++) ASSERT_EQ(*it1, i);
  i = 5;
  for (int i = 5; i <= 10; it1++, i++) {
    ASSERT_EQ(*it1++, i);
    ASSERT_EQ(*it1, i);
  }
  for (i = 11; i <= 15; i++, it1++) ASSERT_EQ(*it1, i);
  ASSERT_EQ(a1.size(), 22);
  ASSERT_EQ(a2.size(), 0);

  // a1.SimpleprintTree(a1.root);
  // a2.printTree(a2.root);
}

//________________________________________________Lookup____________________________________________________
TYPED_TEST(TestMultisetGroup, Contains) {
  s21::multiset<std::string> a;
  std::multiset<std::string> b;
  s21::multiset<std::string>::iterator it1;
  EXPECT_THROW(*it1, std::exception);

  for (int i = 0; i < 50; i++) {
    std::string x = std::to_string(i);
    ASSERT_EQ(*a.insert(x), *b.insert(x));
  }

  for (int i = 0; i < 50; i++) ASSERT_EQ(a.contains(std::to_string(i)), true);
  for (int i = 50; i < 100; i++)
    ASSERT_EQ(a.contains(std::to_string(i)), false);
}

TYPED_TEST(TestMultisetGroup, Find) {
  s21::multiset<std::string> a;
  std::multiset<std::string> b;
  s21::multiset<std::string>::iterator it1;
  EXPECT_THROW(*it1, std::exception);

  for (int i = 0; i < 50; i++) {
    std::string x = std::to_string(i);
    ASSERT_EQ(*a.insert(x), *b.insert(x));
  }

  for (int i = 0; i < 50; i++)
    ASSERT_EQ(*a.find(std::to_string(i)), *b.find(std::to_string(i)));
}

//________________________________________________Iterators_________________________________________________
TYPED_TEST(TestMultisetGroup, operator_plus) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a;
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b;
  auto it1 = a.begin();
  auto it2 = b.begin();

  for (int i = 0; i < 50; i++) {
    char x = 'N';
    ASSERT_EQ(*a.insert(x), *b.insert(x));
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(*it1, *it2);

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); ++it1, ++it2)
    ASSERT_EQ(*it1, *it2);
}

TYPED_TEST(TestMultisetGroup, operator_sub) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a;
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b;
  auto it1 = a.begin();
  auto it2 = b.begin();

  for (int i = 0; i < 10; i++) {
    int x = 4;
    ASSERT_EQ(*a.insert(x), *b.insert(x));
  }

  it1 = a.end();
  it2 = b.end();
  do {
    it1--;
    it2--;
    ASSERT_EQ(*it1, *it2);

  } while (it1 != a.begin() && it2 != b.begin());

  it1 = a.end();
  it2 = b.end();
  do {
    --it1;
    --it2;
    ASSERT_EQ(*it1, *it2);

  } while (it1 != a.begin() || it2 != b.begin());
  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TYPED_TEST(TestMultisetGroup, operator_equal) {
  s21::multiset<std::string> a;
  std::multiset<std::string> b;
  a.insert("Nurlan");
  b.insert("Nurlan");
  s21::multiset<std::string>::iterator it11 = a.begin();
  s21::multiset<std::string>::iterator it12 = a.begin();
  std::multiset<std::string>::iterator it21 = b.end();
  std::multiset<std::string>::iterator it22 = b.end();
  ASSERT_EQ(it11 != it11, it21 != it21);
  ASSERT_EQ(it11 == it11, it21 == it21);
  ASSERT_EQ(it11 != it12, it21 != it22);
  ASSERT_EQ(it11 == it12, it21 == it22);
}

TYPED_TEST(TestMultisetGroup, operator_Arrow) {
  s21::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> a;
  std::multiset<typename TestMultisetGroup<TypeParam>::MultisetType> b;
  auto it1 = a.begin();
  auto it2 = b.begin();
  for (int i = 0; i < 26; i++) {
    char x = 'a';
    ASSERT_EQ(*a.insert(x), *b.insert(x));
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); ++it1, ++it2)
    ASSERT_EQ(*it1, *it2);
  // a.printTree(a.root);
}
