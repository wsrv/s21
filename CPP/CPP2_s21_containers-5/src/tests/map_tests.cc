#include <gtest/gtest.h>

#include <list>
#include <map>

#include "../s21_containers.h"

//________________________________________________Member_functions__________________________________________________

TEST(TestMapGroup, Initializer_list) {
  s21::map<int, char> a = {{1, 'N'}, {2, 'u'}, {3, 'r'},
                           {4, 'l'}, {4, 'a'}, {4, 'n'}};
  std::map<int, char> b = {{1, 'N'}, {2, 'u'}, {3, 'r'},
                           {4, 'l'}, {4, 'a'}, {4, 'n'}};
  auto it1 = a.begin();
  auto it2 = b.begin();
  for (; it1 != a.end(); it1++, it2++) {
    EXPECT_EQ(it1->first, it2->first);
    EXPECT_EQ(it1->second, it2->second);
  }
  EXPECT_EQ(a.size(), b.size());
}

TEST(TestMapGroup, ConstructorCopy) {
  s21::map<int, int> a = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> b = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> a_copy = a;
  std::map<int, int> b_copy = b;

  EXPECT_EQ(a_copy.size(), b_copy.size());
  auto it1 = a_copy.begin();
  auto it2 = b_copy.begin();
  for (; it1 != a_copy.end(); ++it1, ++it2) {
    EXPECT_TRUE((*it1).first == (*it2).first);
    EXPECT_TRUE((*it1).second == (*it2).second);
  }
  // a.SimpleprintTree(a.root);
}

TEST(map, ConstructorMoveMap) {
  s21::map<int, int> a = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> b = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> a_copy = std::move(a);
  std::map<int, int> b_copy = std::move(b);
  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a_copy.size(), b_copy.size());
  auto it1 = a_copy.begin();
  auto it2 = b_copy.begin();
  for (; it1 != a_copy.end(); ++it1, ++it2) {
    EXPECT_TRUE(it1->first == it2->first);
    EXPECT_TRUE(it1->second == it2->second);
  }
}

//________________________________________________Iterators__________________________________________________

TEST(TestMapGroup, Begin) {
  s21::map<int, char> a;
  std::map<int, char> b;
  a[99] = 'N';
  b[99] = 'N';

  ASSERT_EQ(a.begin()->first, b.begin()->first);
  for (int i = 0; i < 10; i++) ASSERT_EQ(a[i], b[i]);
  ASSERT_EQ(a.begin()->first, b.begin()->first);
}

TEST(TestMapGroup, End) {
  s21::map<int, char> a;
  std::map<int, char> b;
  s21::map<int, char>::iterator it1;
  std::map<int, char>::iterator it2;

  for (int i = 1; i < 50; i++) {  // leaks
    std::pair<int, int> x = {rand() % 100, rand() % 100};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }
  for (it1 = a.begin(), it2 = b.begin(); it2 != b.end(); it1++, it2++)
    ASSERT_EQ(a[it1->first], b[it2->first]);

  it1 = a.begin();
  it2 = b.begin();
  it1++;
  it2++;
  ASSERT_EQ(a[it1->first], b[it2->first]);
  it1++;
  it2++;
  ASSERT_EQ(a[it1->first], b[it2->first]);
  it1++;
  it2++;
  ASSERT_EQ(a[it1->first], b[it2->first]);
  --it1;
  --it2;
  ASSERT_EQ(a[it1->first], b[it2->first]);
  --it1;
  --it2;
  ASSERT_EQ(a[it1->first], b[it2->first]);
  --it1;
  --it2;
  ASSERT_EQ(a[it1->first], b[it2->first]);
  it1++;
  it2++;
  ASSERT_EQ(a[it1->first], b[it2->first]);
  ASSERT_EQ(a[(++it1)->first], b[(++it2)->first]);
  ASSERT_EQ(a[(++it1)->first], b[(++it2)->first]);
  ASSERT_EQ(a[(it1--)->first], b[(it2--)->first]);

  ASSERT_EQ(a.end()->first, b.end()->second);
  // a.printTree(a.root);
}

//________________________________________________Capacity__________________________________________________
TEST(TestMapGroup, Capacity) {
  s21::map<int, std::string> a;
  std::map<int, std::string> b;
  ASSERT_EQ(a.empty(), b.empty());
  a[99] = "Nurlan";
  b[99] = "The Best";
  ASSERT_EQ(a.empty(), b.empty());
  s21::map<int, std::string>::iterator it1 = a.begin();
  std::map<int, std::string>::iterator it2 = b.begin();
  a.erase(it1);
  b.erase(it2);
  ASSERT_EQ(a.empty(), b.empty());
  // a.printTree(a.root);
}

TEST(TestMapGroup, Size) {
  s21::map<int, std::string> a;
  std::map<int, std::string> b;
  ASSERT_EQ(a.size(), b.size());
  for (int i = 0; i < 6; i++) {
    a[99] = "Nurlan";
    b[99] = "The Best";
  }
  ASSERT_EQ(a.size(), b.size());
}
//________________________________________________Element_access____________________________________________
TEST(TestMapGroup, operator) {
  s21::map<int, std::string> a;
  std::map<int, std::string> b;
  for (int i = 0; i < 50; i++) {
    a[99] = "Nurlan";
    b[99] = "Nurlan";
  }
  for (int i = 0; i < 100; i++) ASSERT_EQ(a[i], b[i]);
}

TEST(TestMapGroup, at1) {
  s21::map<char, std::string> a = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  EXPECT_THROW(a.at('g'), std::out_of_range);
  ASSERT_EQ(a.at('a'), "Alina");
}

TEST(TestMapGroup, at2) {
  s21::map<int, std::string> a;
  std::map<int, std::string> b;
  s21::map<int, std::string>::iterator it1;
  std::map<int, std::string>::iterator it2;
  for (int i = 0; i < 50; i++) {
    a[i] = "Nurlan";
    b[i] = "Nurlan";
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end() || it2 != b.end();
       it1++, it2++) {
    ASSERT_EQ(a.at(it1->first), b.at(it2->first));
  }

  for (int i = 50; i < 100; i++) {
    EXPECT_THROW(a.at(i), std::out_of_range);
    EXPECT_THROW(b.at(i), std::out_of_range);
  }
  ASSERT_EQ(a.size(), b.size());
}

//________________________________________________Modifiers_________________________________________________

TEST(TestMapGroup, Clear) {
  s21::map<int, int> a;
  std::map<int, int> b;
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
  a.insert(std::make_pair(1, 1));
  b.insert(std::make_pair(1, 1));
  EXPECT_EQ(a.empty(), b.empty());
  a.clear();
  b.clear();
  EXPECT_EQ(a.empty(), b.empty());
}

TEST(TestMapGroup, Insert_int_int) {
  s21::map<int, int> a;
  std::map<int, int> b;
  std::pair<int, int> a1 = {19, 0};
  std::pair<int, int> b1 = {19, 0};
  s21::map<int, int>::iterator it1;
  std::map<int, int>::iterator it2;

  for (int i = 1; i < 50; i++) {
    std::pair<int, int> x = {rand() % 10, rand() % 100};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }
  ASSERT_EQ(a.insert(a1).second, true);
  ASSERT_EQ(a.insert(a1).second, false);
  ASSERT_EQ(b.insert(b1).second, true);
  a[77] = 3;
  b[77] = 3;

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(it1->first, it2->first);

  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}
TEST(TestMapGroup, Insert_int_char) {
  s21::map<int, char> a;
  std::map<int, char> b;
  s21::map<int, char>::iterator it1;
  std::map<int, char>::iterator it2;

  for (int i = 0; i < 50; i++) {
    std::pair<int, char> x = {i, 'N' + i};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }
  a[77] = 'O';
  b[77] = 'O';
  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++) {
    ASSERT_EQ(it1->first, it2->first);
  }
  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TEST(TestMapGroup, Insert_int_string) {
  s21::map<int, std::string> a;
  std::map<int, std::string> b;
  s21::map<int, std::string>::iterator it1;
  std::map<int, std::string>::iterator it2;

  for (int i = 0; i < 50; i++) {
    std::pair<int, std::string> x = {i, std::to_string(i)};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }
  a[90] = "Nurlan";
  b[90] = "Nurlan";

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++) {
    ASSERT_EQ(it1->first, it2->first);
  }
  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TEST(TestMapGroup, Insert_string_int) {
  s21::map<std::string, int> a;
  std::map<std::string, int> b;
  s21::map<std::string, int>::iterator it1;
  std::map<std::string, int>::iterator it2;

  for (int i = 0; i < 50; i++) {
    std::pair<std::string, int> x = {std::to_string(rand() % 100),
                                     rand() % 100};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }
  a["Nurlan"] = 333;
  b["Nurlan"] = 333;

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++) {
    ASSERT_EQ(it1->first, it2->first);
  }
  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TEST(TestMapGroup, Insert_string_char) {
  s21::map<std::string, char> a;
  std::map<std::string, char> b;
  s21::map<std::string, char>::iterator it1;
  std::map<std::string, char>::iterator it2;

  for (int i = 0; i < 50; i++) {
    std::pair<std::string, char> x = {std::to_string(rand() % 100),
                                      rand() % 100};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }
  a["Nurlan"] = 'O';
  b["Nurlan"] = 'O';

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(it1->first, it2->first);

  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TEST(TestMapGroup, Insert_string_string) {
  s21::map<std::string, std::string> a;
  std::map<std::string, std::string> b;
  s21::map<std::string, std::string>::iterator it1;
  std::map<std::string, std::string>::iterator it2;

  for (int i = 0; i < 50; i++) {
    std::pair<std::string, std::string> x = {std::to_string(rand() % 100),
                                             std::to_string(rand() % 100)};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }
  a["Nurlan"] = "The Best";
  b["Nurlan"] = "The Best";

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++) {
    ASSERT_EQ(it1->first, it2->first);
  }
  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TEST(TestMapGroup, Insert_or_assign_int_string) {
  s21::map<int, std::string> a;
  std::map<int, std::string> b;
  s21::map<int, std::string>::iterator it1;
  std::map<int, std::string>::iterator it2;

  for (int i = 0, j = 49; i < 50; i++, j--) {
    std::pair<int, std::string> a1 = {i, std::to_string(rand() % 100)};
    std::pair<int, std::string> b1 = {j, std::to_string(rand() % 100)};
    ASSERT_EQ(a.insert(a1).second, b.insert(b1).second);
  }
  a[99] = "The Best";
  b[99] = "The Best";

  for (int i = 49; i >= 0; i--) a.insert_or_assign(i, std::to_string(i));

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(it1->first, it2->first);

  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TEST(TestMapGroup, Insert_pair) {
  s21::map<std::pair<int, int>, std::pair<int, int>> a;
  std::map<std::pair<int, int>, std::pair<int, int>> b;
  s21::map<std::pair<int, int>, std::pair<int, int>>::iterator it1;
  std::map<std::pair<int, int>, std::pair<int, int>>::iterator it2;

  for (int i = 0, j = 49; i < 50; i++, j--) {
    std::pair<std::pair<int, int>, std::pair<int, int>> x = {{i, j}, {j, i}};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++) {
    ASSERT_EQ(it1->first.first, it2->first.first);
    ASSERT_EQ(it1->first.second, it2->first.second);
    ASSERT_EQ(it1->second.first, it2->second.first);
    ASSERT_EQ(it1->second.second, it2->second.second);
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

TEST(TestMapGroup, Insert_my_class) {
  s21::map<s21::my_class, s21::my_class> a;
  s21::map<s21::my_class, s21::my_class>::iterator it1;

  for (int i = 0, j = 49; i < 50; i++, j--) {
    s21::my_class a1(i, j);
    s21::my_class a2(j, i);
    std::pair<s21::my_class, s21::my_class> x = {a1, a2};
    ASSERT_EQ(a.insert(x).second, true);
  }

  for (it1 = a.begin(); it1 != a.end(); it1++) {
    ASSERT_EQ(it1->first.val.first, it1->second.val.second);
    ASSERT_EQ(it1->first.val.second, it1->second.val.first);
  }
  ASSERT_EQ(a.size(), 50);
}

TEST(TestMapGroup, Insert_many) {
  s21::map<int, int> a;
  std::map<int, int> b;
  std::pair<int, int> x1 = {1, 2};
  std::pair<int, int> x2 = {2, 3};
  std::pair<int, int> x3 = {3, 4};
  // cout << "\033[94m" << a.insert(x1).second << endl;

  std::vector<std::pair<s21::map<int, int>::iterator, bool>> v1;
  v1 = a.insert_many(x1, x2, x3);

  std::vector<std::pair<std::map<int, int>::iterator, bool>> v2;
  v2.push_back(b.insert(x1));
  v2.push_back(b.insert(x2));
  v2.push_back(b.insert(x3));

  for (int i = 0; i < int(v1.size()); i++) {
    ASSERT_EQ(v1[i].first->first, v2[i].first->first);
    ASSERT_EQ(v1[i].first->second, v2[i].first->second);
    ASSERT_EQ(v1[i].second, v2[i].second);
  }
}

TEST(TestMapGroup, Erase_1) {
  s21::map<int, std::string> a;
  std::map<int, std::string> b;
  s21::map<int, std::string>::iterator it1;
  std::map<int, std::string>::iterator it2;
  s21::map<int, std::string>::iterator save_it1;
  std::map<int, std::string>::iterator save_it2;

  for (int i = 0; i < 50; i++) {
    std::pair<int, std::string> x = {rand() % 100, std::to_string(i)};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }
  a[101] = "The Best";
  b[101] = "The Best";

  int i = 0;
  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); i++) {
    it1 = a.erase(it1);
    it2 = b.erase(it2);
    ASSERT_EQ(a.size(), b.size());
    save_it1 = it1;
    save_it2 = it2;
    for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++) {
      ASSERT_EQ(it1->first, it2->first);
    }
    it1 = save_it1;
    it2 = save_it2;
  }
  // a.printTree(a.root);
}
TEST(TestMapGroup, Erase_2) {
  s21::map<int, std::string> a;
  std::map<int, std::string> b;
  s21::map<int, std::string>::iterator it1;
  std::map<int, std::string>::iterator it2;

  for (int i = 0; i < 50; i++) {
    std::pair<int, std::string> x = {i, std::to_string(rand() % 100)};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(it1->first, it2->first);

  int i = 0;
  for (it1 = a.begin(), it2 = b.begin(); i < 10; i++, it1++, it2++)
    ;

  for (int j = 0; j < 10; j++) {
    it1 = a.erase(it1);
    it2 = b.erase(it2);
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(it1->first, it2->first);
  // a.printTree(a.root);
  // a.SimpleprintTree(a.root);
}

TEST(TestMapGroup, Swap) {
  s21::map<int, double> a1;
  s21::map<int, double> a2;
  std::map<int, double> b1;
  std::map<int, double> b2;
  s21::map<int, double>::iterator it1;
  std::map<int, double>::iterator it2;

  for (int i = 0, j = 49; i < 50; i++, j--) {
    std::pair<int, double> x = {i, j / 10.};
    ASSERT_EQ(a1.insert(x).second, b1.insert(x).second);
  }
  for (int i = 0, j = 49; i < 50; i++, j--) {
    std::pair<int, double> x = {i, j << 1};
    ASSERT_EQ(a2.insert(x).second, b2.insert(x).second);
  }

  for (it1 = a1.begin(), it2 = b1.begin(); it1 != a1.end(); it1++, it2++)
    ASSERT_EQ(it1->first, it2->first);

  a1.swap(a2);
  b1.swap(b2);

  for (it1 = a1.begin(), it2 = b1.begin(); it1 != a1.end(); it1++, it2++)
    ASSERT_EQ(it1->first, it2->first);
  for (it1 = a2.begin(), it2 = b2.begin(); it1 != a2.end(); it1++, it2++)
    ASSERT_EQ(it1->first, it2->first);

  ASSERT_EQ(a1.size(), b1.size());
  ASSERT_EQ(a2.size(), b2.size());
  // a1.printTree(a1.root);
}

TEST(TestMapGroup, Merge) {
  s21::map<int, double> a1;
  s21::map<int, double> a2;
  s21::map<int, double>::iterator it1;
  for (int i = 0; i <= 10; i++) {
    std::pair<int, double> x = {i, 1 / 10.};
    a1.insert(x).second;
  }
  for (int i = 5; i <= 15; i++) {
    std::pair<int, double> x = {i, 10.};
    a2.insert(x).second;
  }

  a1.merge(a2);
  for (int i = 0; i <= 10; i++) ASSERT_EQ(a1[i], 1 / 10.);
  for (int i = 11; i <= 15; i++) ASSERT_EQ(a1[i], 10.);
  for (int i = 5; i <= 10; i++) ASSERT_EQ(a2[i], 10.);
  ASSERT_EQ(a2.size(), 6);

  // a2.printTree(a2.root);
}
//________________________________________________Lookup____________________________________________________
TEST(TestMapGroup, Contains) {
  s21::map<int, std::string> a;
  std::map<int, std::string> b;
  s21::map<int, std::string>::iterator it1;

  for (int i = 0; i < 50; i++) {
    std::pair<int, std::string> x = {i, std::to_string(i)};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }

  for (int i = 0; i < 50; i++) ASSERT_EQ(a.contains(i), true);
  for (int i = 50; i < 100; i++) ASSERT_EQ(a.contains(i), false);
}

//________________________________________________Iterators_________________________________________________
TEST(TestMapGroup, operator_plus) {
  s21::map<int, char> a;
  std::map<int, char> b;
  s21::map<int, char>::iterator it1;
  std::map<int, char>::iterator it2;

  for (int i = 0; i < 50; i++) {
    std::pair<int, char> x = {i, i};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++)
    ASSERT_EQ(it1->first, it2->first);

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); ++it1, ++it2)
    ASSERT_EQ(it1->first, it2->first);
}

TEST(TestMapGroup, operator_sub) {
  s21::map<int, int> a;
  std::map<int, int> b;
  s21::map<int, int>::iterator it1;
  std::map<int, int>::iterator it2;

  for (int i = 0; i < 10; i++) {
    std::pair<int, int> x = {i, i};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }

  it1 = a.end();
  it2 = b.end();
  do {
    it1--;
    it2--;
    ASSERT_EQ(it1->first, it2->first);

  } while (it1 != a.begin() && it2 != b.begin());

  it1 = a.end();
  it2 = b.end();
  do {
    --it1;
    --it2;
    ASSERT_EQ(it1->first, it2->first);

  } while (it1 != a.begin() || it2 != b.begin());
  ASSERT_EQ(a.size(), b.size());
  // a.printTree(a.root);
}

TEST(TestMapGroup, operator_equal) {
  s21::map<std::string, std::string> a;
  std::map<std::string, std::string> b;
  a["Nurlan"] = "The Best";
  b["Nurlan"] = "The Best";
  s21::map<std::string, std::string>::iterator it11 = a.begin();
  s21::map<std::string, std::string>::iterator it12 = a.begin();
  std::map<std::string, std::string>::iterator it21 = b.end();
  std::map<std::string, std::string>::iterator it22 = b.end();
  ASSERT_EQ(it11 != it11, it21 != it21);
  ASSERT_EQ(it11 == it11, it21 == it21);
  ASSERT_EQ(it11 != it12, it21 != it22);
  ASSERT_EQ(it11 == it12, it21 == it22);
}

TEST(TestMapGroup, operator_Arrow) {
  s21::map<char, char> a;
  std::map<char, char> b;
  s21::map<char, char>::iterator it1;
  std::map<char, char>::iterator it2;
  EXPECT_THROW(it1->first, std::exception);

  for (int i = 0; i < 26; i++) {
    std::pair<char, char> x = {'a' + i, 'a' + i};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); ++it1, ++it2)
    ASSERT_EQ(it1->first, it2->first);
  // a.printTree(a.root);
}

TEST(TestMapGroup, Dereferencing_operator) {
  // GTEST_SKIP()<<"\033[33m Dereferencing operator is not supported";
  s21::map<char, char> a;
  std::map<char, char> b;
  s21::map<char, char>::iterator it1;
  std::map<char, char>::iterator it2;
  for (int i = 0; i < 26; i++) {
    std::pair<char, char> x = {'a' + i, 'a' + i};
    ASSERT_EQ(a.insert(x).second, b.insert(x).second);
  }

  for (it1 = a.begin(), it2 = b.begin(); it1 != a.end(); ++it1, ++it2)
    ASSERT_EQ((*it1).first, (*it2).first);

  // a.printTree(a.root);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
