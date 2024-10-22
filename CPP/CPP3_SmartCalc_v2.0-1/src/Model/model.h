#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_
#include <cmath>
#include <iostream>
#include <list>
#include <stack>
// #include <string>

typedef enum {
  DIGIT = 1,
  LEFT = 2,
  RIGHT = 3,
  COS = 4,
  SIN = 5,
  TAN = 6,
  ASIN = 7,
  ACOS = 8,
  ATAN = 9,
  MOD = 10,
  SQRT = 11,
  LN = 12,
  LOG = 13,
  ADD = 14,
  SUB = 15,
  MUL = 16,
  DIV = 17,
  POW = 18,
  X_X = 19,
  ERR = 20
} lexems_enum;

namespace s21 {

typedef struct Node {
  lexems_enum type;
  int priority;
  double value;
} Node;

class Model {
 public:
  Model() {}
  ~Model() {}

  double s21_smart_calc(std::string& str, double x);
  double s21_credit_calc_monthly(double months, double summ, double procents);
  double s21_credit_calc_total_1(double monthly, double time);
  double s21_credit_calc_over_1(double total, double sum);
  std::list<double> s21_credit_calc2(double months, double summ,
                                     double procents);

 private:
  std::list<Node> ParseLexemes(std::string lexem);
  double getNum(std::string str, size_t* i);
  bool Valid(std::list<Node> list);
  // void Printer(std::list<Node> list);
  void UnaryMagic(std::list<Node>& list);
  bool isFunc(lexems_enum type);
  bool isOper(lexems_enum type);
  int toOPZ(std::list<Node> Llist, std::list<Node>& result);
  double calcOper(lexems_enum type, double val1, double val2);
  double calcFunc(lexems_enum type, double val);
  int calc(std::list<Node> OPZ, std::list<Node>& result);
  bool is_x(std::list<Node> list);
  void put_x(std::list<Node>& list, double x);
  std::list<double> creditCalc2(double months, double summ, double procents);
};

}  // namespace s21

#endif
