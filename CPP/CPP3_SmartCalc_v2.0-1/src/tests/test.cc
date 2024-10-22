#include <gtest/gtest.h>
#include <math.h>

#include <iostream>

#include "../Controller/controller.h"
using namespace std;

TEST(test, credit_test) {
  s21::Controller controller;

  double monthly = controller.cred_monthly(36, 100000, 5);
  EXPECT_TRUE(2997.09 == monthly);

  double total = controller.cred_total_1(monthly, 36);
  EXPECT_TRUE(107895.24 == total);

  double over = controller.cred_over_1(total, 100000);
  EXPECT_TRUE(7895.24 == round(over * 100) / 100);
}

TEST(test, Operations) {
  s21::Controller controller;

  std::string str = "8-7";
  double result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(1.0 == result);

  str = "-7";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(-7.0 == result);

  str = "5+5";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(10.0 == result);

  str = "4*5*2*2*2+2";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(162.0 == result);

  str = "150/10+5*2/2";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(20.0 == result);

  str = "5+5-2*3/6";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(9.0 == result);

  str = "123+0.456";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(123.456 == result);

  str = "-(-1)";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(1.0 == result);

  str = "10-20*(-10)";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(210.0 == result);

  str = "5+5-2*3/6";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(9.0 == result);

  str = "(2.0)^(2)";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(4.0 == result);
}

TEST(test, OperationsNAN) {
  s21::Controller controller;

  std::string str = "-";
  double result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(isnan(result));

  str = "-8-";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(isnan(result));

  str = "1*(1*(1*(1*(-1)))))";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(isnan(result));

  str = "1*(1*(1*(1*(/-1))))";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(isnan(result));
}

TEST(test, Functions) {
  s21::Controller controller;

  std::string str = "cos(10mod2.2)";
  double result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(result == cos(fmod(10, 2.2)));

  str = "sqrt(ln(10))";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(result == sqrt(log(10)));

  str = "atan(10)+sin(10)";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(result == atan(10) + sin(10));
}

TEST(test, FunctionsNAN) {
  s21::Controller controller;

  std::string str = "cos()";
  double result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(isnan(result));

  str = ")(sin(x)";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(isnan(result));
}

TEST(test, OperationsWith_x) {
  s21::Controller controller;

  std::string str = "x-7";
  double result = controller.Calculation(str, 8.0);
  EXPECT_TRUE(1.0 == result);

  str = "x";
  result = controller.Calculation(str, -7.0);
  EXPECT_TRUE(-7.0 == result);

  str = "x+x";
  result = controller.Calculation(str, 5.0);
  EXPECT_TRUE(10.0 == result);

  str = "4*5*x*x*x+x";
  result = controller.Calculation(str, 2.0);
  EXPECT_TRUE(162.0 == result);

  str = "150/x+5*2/2";
  result = controller.Calculation(str, 10.0);
  EXPECT_TRUE(20.0 == result);

  str = "5+5-2*x/6";
  result = controller.Calculation(str, 3.0);
  EXPECT_TRUE(9.0 == result);

  str = "123+x";
  result = controller.Calculation(str, 0.456);
  EXPECT_TRUE(123.456 == result);

  str = "-(-x)";
  result = controller.Calculation(str, 1.0);
  EXPECT_TRUE(1.0 == result);

  str = "x-20*(-x)";
  result = controller.Calculation(str, 10.0);
  EXPECT_TRUE(210.0 == result);

  str = "5+x-2*3/6";
  result = controller.Calculation(str, 5.0);
  EXPECT_TRUE(9.0 == result);

  str = "(2.0)^(x)";
  result = controller.Calculation(str, 2.0);
  EXPECT_TRUE(4.0 == result);
}

TEST(test, OperationsWithX_NAN) {
  s21::Controller controller;

  std::string str = "-x-";
  double result = controller.Calculation(str, 8.0);
  EXPECT_TRUE(isnan(result));

  str = "x*(x*(x*(1*(-x)))))";
  result = controller.Calculation(str, 1.0);
  EXPECT_TRUE(isnan(result));

  str = "1*(1*(x*(1*(/-1))))";
  result = controller.Calculation(str, 1.0);
  EXPECT_TRUE(isnan(result));
}

TEST(test, FunctionsWithX) {
  s21::Controller controller;

  std::string str = "cos(xmod2.2)";
  double result = controller.Calculation(str, 10.0);
  EXPECT_TRUE(result == cos(fmod(10, 2.2)));

  str = "sqrt(ln(x))";
  result = controller.Calculation(str, 10.0);
  EXPECT_TRUE(result == sqrt(log(10)));

  str = "atan(x)+sin(10)";
  result = controller.Calculation(str, 10.0);
  EXPECT_TRUE(result == atan(10) + sin(10));
}

TEST(test, FunctionsWithX_NAN) {
  s21::Controller controller;

  std::string str = "cos()x";
  double result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(isnan(result));

  str = ")(sin(x)";
  result = controller.Calculation(str, 0.0);
  EXPECT_TRUE(isnan(result));
}
