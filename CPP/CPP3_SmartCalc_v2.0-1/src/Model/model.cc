#include "model.h"

namespace s21 {

std::list<Node> Model::ParseLexemes(std::string str) {
  std::list<Node> result;
  size_t len = str.length();
  for (size_t i = 0; i < len;) {
    if (str[i] == 'x') {
      result.push_back({X_X, 0, 0.0});
      (i)++;
    } else if (str[i] == '+') {
      result.push_back({ADD, 1, 0.0});
      (i)++;
    } else if (str[i] == '-') {
      result.push_back({SUB, 1, 0.0});
      (i)++;
    } else if (str[i] == '/') {
      result.push_back({DIV, 3, 0.0});
      (i)++;
    } else if (str[i] == '*') {
      result.push_back({MUL, 3, 0.0});
      (i)++;
    } else if (str[i] == '^') {
      result.push_back({POW, 4, 0.0});
      (i)++;
    } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
      result.push_back({MOD, 4, 0.0});
      (i) += 3;
    } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
      result.push_back({SIN, 4, 0.0});
      (i) += 3;
    } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
      result.push_back({COS, 5, 0.0});
      (i) += 3;
    } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
      result.push_back({TAN, 5, 0.0});
      (i) += 3;
    } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
      result.push_back({LOG, 5, 0.0});
      (i) += 3;
    } else if (str[i] == 'l' && str[i + 1] == 'n') {
      result.push_back({LN, 5, 0.0});
      (i) += 2;
    } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
               str[i + 3] == 'n') {
      result.push_back({ASIN, 5, 0.0});
      (i) += 4;
    } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
               str[i + 3] == 's') {
      result.push_back({ACOS, 5, 0.0});
      (i) += 4;
    } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
               str[i + 3] == 'n') {
      result.push_back({ATAN, 5, 0.0});
      (i) += 4;
    } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
               str[i + 3] == 't') {
      result.push_back({SQRT, 5, 0.0});
      (i) += 4;
    } else if (str[i] == '(') {
      result.push_back({LEFT, -1, 0.0});
      (i)++;
    } else if (str[i] == ')') {
      result.push_back({RIGHT, -1, 0.0});
      (i)++;
    } else if (isdigit(str[i])) {
      double digit = getNum(str, &i);  // std::stod
      result.push_back({DIGIT, 0, digit});
    } else {
      result.push_back({ERR, 0, 0});
      i = len;
    }
  }
  return result;
}

double Model::getNum(std::string str, size_t* i) {
  double val = 0.0;
  bool point = false;
  size_t len = str.length();
  std::string digit;
  while (*i < len &&
         (isdigit(str[*i]) || (str[*i] == '.' && !point) || str[*i] == 'e' ||
          (str[*i - 1] == 'e' && (str[*i] == '+' || str[*i] == '-')))) {
    if (str[*i] == '.') point = true;
    digit += str[*i];
    (*i)++;
  }
  val = std::stod(digit);
  return val;
}

bool Model::Valid(std::list<Node> list) {
  bool res = true;
  if (isFunc(list.back().type) || isOper(list.back().type) ||
      list.back().type == LEFT || list.back().type == ERR)
    res = false;
  else {
    std::list<Node>::iterator it = list.begin();
    std::list<Node>::iterator it2 = it++;
    while (it2 != list.end() && res == true) {
      if ((*it).type == RIGHT && (*it2).type == LEFT) res = false;
      it++;
      it2++;
    }
  }
  return res;
}

/*void Model::Printer(std::list<Node> list) {
  printf("\n");
  std::list<Node>::iterator it = list.begin();
  while (it != list.end()) {
    if ((*it).type == 1)
      printf("%f ", (*it).value);
    else if ((*it).type == 2)
      printf("( ");
    else if ((*it).type == 3)
      printf(") ");
    else if ((*it).type == 4)
      printf("cos ");
    else if ((*it).type == 5)
      printf("sin ");
    else if ((*it).type == 6)
      printf("tan ");
    else if ((*it).type == 7)
      printf("asin ");
    else if ((*it).type == 8)
      printf("acos ");
    else if ((*it).type == 9)
      printf("atan ");
    else if ((*it).type == 10)
      printf("mod ");
    else if ((*it).type == 11)
      printf("sqrt ");
    else if ((*it).type == 12)
      printf("ln ");
    else if ((*it).type == 13)
      printf("log ");
    else if ((*it).type == 14)
      printf("+ ");
    else if ((*it).type == 15)
      printf("- ");
    else if ((*it).type == 16)
      printf("* ");
    else if ((*it).type == 17)
      printf("/ ");
    else if ((*it).type == 18)
      printf("^ ");
    else if ((*it).type == 19)
      printf("x ");
    ++it;
  }
  printf("\n");
}*/

void Model::UnaryMagic(std::list<Node>& list) {
  std::list<Node>::iterator it = list.begin();
  std::list<Node>::iterator it2 = list.begin();
  ++it2;
  if (((*it).type == ADD || (*it).type == SUB) &&
      (it2 != list.end() &&
       ((*it2).type == DIGIT || (*it2).type == LEFT || isFunc((*it2).type))))
    list.push_front({DIGIT, 0, 0.0});
  for (; it2 != list.end(); ++it, ++it2) {
    if (((*it2).type == ADD || (*it2).type == SUB) && ((*it).type == LEFT))
      it = list.insert(it2, {DIGIT, 0, 0.0});
  }
}

bool Model::isFunc(lexems_enum type) {
  if (type == COS || type == SIN || type == TAN || type == ACOS ||
      type == ASIN || type == ATAN || type == SQRT || type == LN || type == LOG)
    return true;
  else
    return false;
}

bool Model::isOper(lexems_enum type) {
  if (type == ADD || type == SUB || type == MUL || type == DIV || type == POW ||
      type == MOD)
    return true;
  else
    return false;
}

int Model::toOPZ(std::list<Node> Llist, std::list<Node>& result) {
  int parenthesis = 0;
  int flag = 0;
  std::stack<Node> stek;
  std::list<Node>::iterator it = Llist.begin();
  while (it != Llist.end() && flag != 1) {
    if ((*it).type == DIGIT || (*it).type == X_X)
      result.push_back({(*it).type, (*it).priority, (*it).value});
    else if (isFunc((*it).type) || (*it).type == LEFT) {
      stek.push({(*it).type, (*it).priority, (*it).value});
      if ((*it).type == LEFT) parenthesis++;
    } else if (isOper((*it).type)) {
      while (!(stek.empty()) && ((stek.top().priority >= (*it).priority &&
                                  stek.top().type != POW) ||
                                 (stek.top().priority > (*it).priority))) {
        result.push_back(
            {stek.top().type, stek.top().priority, stek.top().value});
        if (!(stek.empty())) stek.pop();
      }
      stek.push({(*it).type, (*it).priority, (*it).value});
    } else if ((*it).type == RIGHT && parenthesis > 0) {
      parenthesis--;
      while (stek.top().type != LEFT) {
        result.push_back(
            {stek.top().type, stek.top().priority, stek.top().value});
        if (!(stek.empty())) stek.pop();
      }
      if (!(stek.empty())) stek.pop();
      if ((!(stek.empty())) && (isFunc(stek.top().type))) {
        stek.push({stek.top().type, stek.top().priority, stek.top().value});
        if (!(stek.empty())) stek.pop();
      }
      if ((stek.empty()) && parenthesis != 0) flag = 1;
    } else
      flag = 1;
    ++it;
  }
  while (flag != 1 && !(stek.empty())) {
    if (!(stek.empty()) &&
        (stek.top().type == LEFT || stek.top().type == RIGHT))
      flag = 1;
    else {
      result.push_back(
          {stek.top().type, stek.top().priority, stek.top().value});
      if (!(stek.empty())) stek.pop();
    }
  }
  return flag;
}

double Model::calcOper(lexems_enum type, double val1, double val2) {
  double res = 0.0;
  if (type == MOD)
    res = fmod(val1, val2);
  else if (type == ADD)
    res = (val1 + val2);
  else if (type == SUB)
    res = (val1 - val2);
  else if (type == DIV)
    res = (val1 / val2);
  else if (type == MUL)
    res = (val1 * val2);
  else if (type == POW)
    res = pow(val1, val2);
  return res;
}

double Model::calcFunc(lexems_enum type, double val) {
  double res = 0.0;
  if (type == COS)
    res = cos(val);
  else if (type == SIN)
    res = sin(val);
  else if (type == TAN)
    res = tan(val);
  else if (type == ACOS)
    res = acos(val);
  else if (type == ASIN)
    res = asin(val);
  else if (type == ATAN)
    res = atan(val);
  else if (type == LN)
    res = log(val);
  else if (type == LOG)
    res = log10(val);
  else if (type == SQRT)
    res = sqrt(val);
  return res;
}

int Model::calc(std::list<Node> OPZ, std::list<Node>& result) {
  int flag = 0;
  double res = 0.0;
  std::list<Node>::iterator it = OPZ.begin();
  while (it != OPZ.end() && flag == 0) {
    if ((*it).type == DIGIT)
      result.push_front({(*it).type, (*it).priority, (*it).value});
    else if (isFunc((*it).type) && !(result.empty()))
      result.front().value = calcFunc((*it).type, result.front().value);
    else if (isOper((*it).type) && result.size() > 1) {
      std::list<Node>::iterator it2 = result.begin();
      ++it2;
      res = calcOper((*it).type, (*it2).value, result.front().value);
      if (!(result.empty())) result.pop_front();
      result.front().value = res;
    } else
      flag = 1;
    ++it;
  }
  return flag;
}

double Model::s21_smart_calc(std::string& str, double x) {
  double itog = NAN;
  std::list<Node> Llist = ParseLexemes(str);
  if (Valid(Llist)) {
    UnaryMagic(Llist);
    std::list<Node> OPZ;
    int flag = toOPZ(Llist, OPZ);
    if (is_x(OPZ)) put_x(OPZ, x);
    if (!flag) {
      std::list<Node> res;
      flag = calc(OPZ, res);
      if (!flag && res.size() == 1) {
        itog = res.front().value;
      }
    }
  }
  return itog;
}

bool Model::is_x(std::list<Node> list) {
  std::list<Node>::iterator it = list.begin();
  bool res = false;
  while (it != list.end() && !res) {
    if ((*it).type == X_X) res = true;
    ++it;
  }
  return res;
}

void Model::put_x(std::list<Node>& list, double x) {
  std::list<Node>::iterator it = list.begin();
  while (it != list.end()) {
    if ((*it).type == X_X) {
      (*it).priority = 0;
      (*it).type = DIGIT;
      (*it).value = x;
    }
    ++it;
  }
}

double Model::s21_credit_calc_monthly(double months, double summ,
                                      double procents) {
  double monthly;
  if (procents == 0) {
    monthly = summ / months;
  } else {
    double r = procents / 1200;
    double tm = (1 + r);
    double temp = pow(tm, months);
    monthly = summ * r * temp / (temp - 1);
  }
  monthly = round(monthly * 100) / 100;
  return monthly;
}

double Model::s21_credit_calc_total_1(double monthly, double time) {
  return monthly * time;
}

double Model::s21_credit_calc_over_1(double total, double sum) {
  return total - sum;
}

std::list<double> Model::s21_credit_calc2(double months, double summ,
                                          double procents) {
  std::list<double> res;
  double total = 0.0;
  double b = summ / months;
  for (int i = 0; i < months; i++) {
    double sn = summ - (b * i);
    double p = sn * procents / 1200;
    double itog = b + p;
    itog = round(itog * 100) / 100;
    total = total + itog;
    res.push_back(itog);
  }
  res.push_front(total);
  res.push_front(total - summ);
  return res;
}

}  // namespace s21
