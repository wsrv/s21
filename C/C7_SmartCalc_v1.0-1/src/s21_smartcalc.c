#include "s21_smartcalc.h"
//  -lcheck_pic -pthread -lrt -lm -lsubunit

LexemsList* createList() {
  LexemsList* tmp = (LexemsList*)malloc(sizeof(LexemsList));
  tmp->size = 0;
  tmp->head = tmp->tail = NULL;
  return tmp;
}

void deleteList(LexemsList** list) {
  Node* tmp = (*list)->head;
  Node* next = NULL;
  while (tmp) {
    next = tmp->next;
    free(tmp);
    tmp = next;
  }
  free(*list);
  (*list) = NULL;
}

void pushBack(LexemsList* list, lexems_enum type, int priority, double value) {
  Node* tmp = (Node*)malloc(sizeof(Node));
  tmp->type = type;
  tmp->value = value;
  tmp->priority = priority;
  tmp->next = NULL;
  tmp->prev = list->tail;
  if (list->tail) list->tail->next = tmp;
  list->tail = tmp;
  if (list->head == NULL) list->head = tmp;
  list->size++;
  // if (tmp) free(tmp);
}

Node* getNth(LexemsList* list, size_t index) {
  Node* tmp = list->head;
  size_t i = 0;
  while (tmp && i < index) {
    tmp = tmp->next;
    i++;
  }
  return tmp;
}

// void deleteNth(LexemsList* list, size_t index) {
//   Node* elm = NULL;
//   // void *tmp = NULL;
//   elm = getNth(list, index);
//   if (elm->prev) elm->prev->next = elm->next;
//   if (elm->next) elm->next->prev = elm->prev;
//   if (!elm->prev) list->head = elm->next;
//   if (!elm->next) list->tail = elm->prev;
//   free(elm);
//   list->size--;
// }

void pushFront(LexemsList* list, lexems_enum type, int priority, double value) {
  Node* tmp = (Node*)malloc(sizeof(Node));
  tmp->type = type;
  tmp->value = value;
  tmp->priority = priority;
  tmp->next = list->head;
  tmp->prev = NULL;
  if (list->head) list->head->prev = tmp;
  list->head = tmp;
  if (list->tail == NULL) list->tail = tmp;
  list->size++;
}

void insert(LexemsList* list, size_t index, lexems_enum type, int priority,
            double value) {
  Node* elm = NULL;
  Node* ins = NULL;
  elm = getNth(list, index);
  ins = (Node*)malloc(sizeof(Node));
  ins->type = type;
  ins->value = value;
  ins->priority = priority;
  ins->prev = elm;
  ins->next = elm->next;
  if (elm->next) elm->next->prev = ins;
  elm->next = ins;
  if (!elm->prev) list->head = elm;
  if (!elm->next) list->tail = elm;
  list->size++;
}

void DelBack(LexemsList* list) {
  Node* next;
  next = list->tail;
  list->tail = list->tail->prev;
  if (list->tail) list->tail->next = NULL;
  if (next == list->head) list->head = NULL;
  free(next);
  list->size--;
}

int toOPZ(LexemsList* Llist, LexemsList* result) {
  int parenthesis = 0;
  int flag = 0;
  LexemsList* stek = createList();
  Node* tmp = Llist->head;
  while (tmp && flag != 1) {
    if (tmp->type == DIGIT || tmp->type == X_X)
      pushBack(result, tmp->type, tmp->priority, tmp->value);
    else if (tmp->type == COS || tmp->type == SIN || tmp->type == TAN ||
             tmp->type == ACOS || tmp->type == ASIN || tmp->type == ATAN ||
             tmp->type == SQRT || tmp->type == LN || tmp->type == LOG ||
             tmp->type == LEFT) {
      pushBack(stek, tmp->type, tmp->priority, tmp->value);
      if (tmp->type == LEFT) parenthesis++;
    } else if (tmp->type == ADD || tmp->type == SUB || tmp->type == MUL ||
               tmp->type == DIV || tmp->type == POW || tmp->type == MOD) {
      while (stek->size != 0 && stek->tail->priority > tmp->priority) {
        pushBack(result, stek->tail->type, stek->tail->priority,
                 stek->tail->value);
        if (stek->tail != NULL) DelBack(stek);
      }
      pushBack(stek, tmp->type, tmp->priority, tmp->value);
    } else if (tmp->type == RIGHT && parenthesis > 0) {
      parenthesis--;
      while (stek->tail->type != LEFT) {
        pushBack(result, stek->tail->type, stek->tail->priority,
                 stek->tail->value);
        if (stek->tail != NULL) DelBack(stek);
      }
      if (stek->tail != NULL) DelBack(stek);
      if (stek->tail != NULL &&
          (stek->tail->type == COS || stek->tail->type == SIN ||
           stek->tail->type == TAN || stek->tail->type == ACOS ||
           stek->tail->type == ASIN || stek->tail->type == ATAN ||
           stek->tail->type == SQRT || stek->tail->type == LN ||
           stek->tail->type == LOG)) {
        pushBack(result, stek->tail->type, stek->tail->priority,
                 stek->tail->value);
        if (stek->tail != NULL) DelBack(stek);
      }
      if (stek == NULL && parenthesis != 0) flag = 1;
    } else
      flag = 1;
    tmp = tmp->next;
  }
  while (flag != 1 && stek->size != 0) {
    if (stek->size != 0 &&
        (stek->tail->type == LEFT || stek->tail->type == RIGHT))
      flag = 1;
    else {
      pushBack(result, stek->tail->type, stek->tail->priority,
               stek->tail->value);
      if (stek->tail != NULL) DelBack(stek);
    }
  }
  // if (flag == 1 && result) deleteList(&result);
  if (stek) deleteList(&stek);
  return flag;
}

double getNum(char* str, int* i) {
  double val = 0.0;
  int po = 0;
  int len = strlen(str);
  while (*i < len && str[*i] >= '0' && str[*i] <= '9') {
    val = val * 10 + (str[*i] - '0');
    (*i)++;
  }
  if (str[*i] == '.') {
    (*i)++;
    while (*i < len && str[*i] >= '0' && str[*i] <= '9') {
      val = val + (str[*i] - '0') * pow(10, --po);
      (*i)++;
    }
  }
  return val;
}

LexemsList* parser(char* str) {
  int len = strlen(str);
  LexemsList* result = createList();
  for (int i = 0; i < len; i++) {
    if (str[i] == '(') {
      pushBack(result, LEFT, -1, 0.0);
    } else if (str[i] == ')') {
      pushBack(result, RIGHT, -1, 0.0);
    } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
      pushBack(result, COS, 4, 0.0);
      i = i + 2;
    } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
      pushBack(result, SIN, 4, 0.0);
      i = i + 2;
    } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
      pushBack(result, TAN, 4, 0.0);
      i = i + 2;
    } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
               str[i + 3] == 's') {
      pushBack(result, ACOS, 4, 0.0);
      i = i + 3;
    } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
               str[i + 3] == 'n') {
      pushBack(result, ASIN, 4, 0.0);
      i = i + 3;
    } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
               str[i + 3] == 'n') {
      pushBack(result, ATAN, 4, 0.0);
      i = i + 3;
    } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
      pushBack(result, MOD, 3, 0.0);
      i = i + 2;
    } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
               str[i + 3] == 't') {
      pushBack(result, SQRT, 4, 0.0);
      i = i + 3;
    } else if (str[i] == 'l' && str[i + 1] == 'n') {
      pushBack(result, LN, 4, 0.0);
      i = i + 1;
    } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
      pushBack(result, LOG, 4, 0.0);
      i = i + 2;
    } else if (str[i] == '+') {
      pushBack(result, ADD, 1, 0.0);
    } else if (str[i] == '-') {
      pushBack(result, SUB, 1, 0.0);
    } else if (str[i] == '*') {
      pushBack(result, MUL, 2, 0.0);
    } else if (str[i] == '/') {
      pushBack(result, DIV, 2, 0.0);
    } else if (str[i] == '^') {
      pushBack(result, POW, 3, 0.0);
    } else if (str[i] == 'x') {
      pushBack(result, X_X, 0, 0.0);
    } else {
      double digit = getNum(str, &i);
      i--;
      pushBack(result, DIGIT, 0, digit);
    }
  }
  return result;
}

int is_x(LexemsList* list) {
  int res = 0;
  Node* tmp = list->head;
  while (tmp != NULL) {
    if (tmp->type == X_X) res = 1;
    tmp = tmp->next;
  }
  return res;
}

void put_x(LexemsList* list, double x) {
  Node* tmp = list->head;
  while (tmp != NULL) {
    if (tmp->type == X_X) {
      tmp->type = DIGIT;
      tmp->value = x;
    }
    tmp = tmp->next;
  }
}

void UnaryMagic(LexemsList* list) {
  Node* tmp = list->head;
  if ((list->head->type == ADD || list->head->type == SUB) &&
      (list->head->next != NULL &&
       (list->head->next->type == DIGIT || list->head->next->type == LEFT ||
        list->head->next->type == COS || list->head->next->type == SIN ||
        list->head->next->type == TAN || list->head->next->type == ASIN ||
        list->head->next->type == ACOS || list->head->next->type == ATAN ||
        list->head->next->type == LN || list->head->next->type == LOG ||
        list->head->next->type == SQRT)))
    pushFront(list, DIGIT, 0, 0.0);
  for (int i = 0; i < list->size - 1; i++) {
    tmp = getNth(list, i + 1);
    if ((tmp->type == ADD || tmp->type == SUB) && (tmp->prev->type == LEFT))
      insert(list, i, DIGIT, 0, 0.0);
  }
}

// void Printer(LexemsList* list) {
//   printf("\n");
//   Node* tmp = (Node*)malloc(sizeof(Node));
//   tmp = list->head;
//   while (tmp != NULL) {
//     if (tmp->type == 1)
//       printf("%f ", tmp->value);
//     else if (tmp->type == 2)
//       printf("( ");
//     else if (tmp->type == 3)
//       printf(") ");
//     else if (tmp->type == 4)
//       printf("cos ");
//     else if (tmp->type == 5)
//       printf("sin ");
//     else if (tmp->type == 6)
//       printf("tan ");
//     else if (tmp->type == 7)
//       printf("asin ");
//     else if (tmp->type == 8)
//       printf("acos ");
//     else if (tmp->type == 9)
//       printf("atan ");
//     else if (tmp->type == 10)
//       printf("mod ");
//     else if (tmp->type == 11)
//       printf("sqrt ");
//     else if (tmp->type == 12)
//       printf("ln ");
//     else if (tmp->type == 13)
//       printf("log ");
//     else if (tmp->type == 14)
//       printf("+ ");
//     else if (tmp->type == 15)
//       printf("- ");
//     else if (tmp->type == 16)
//       printf("* ");
//     else if (tmp->type == 17)
//       printf("/ ");
//     else if (tmp->type == 18)
//       printf("^ ");
//     else if (tmp->type == 19)
//       printf("x ");
//     tmp = tmp->next;
//   }
//   printf("\n");
//   if (tmp != NULL) free(tmp);
// }

int calc(LexemsList* OPZ, LexemsList* result) {
  int flag = 0;
  double res = 0.0;
  Node* tmp = OPZ->head;
  // Node* tmp = (Node*)malloc(sizeof(Node));
  // tmp = OPZ->head;
  while (tmp != NULL && flag == 0) {
    if (tmp->type == DIGIT)
      pushBack(result, tmp->type, tmp->priority, tmp->value);
    else if (tmp->type == COS && result->tail != NULL)
      result->tail->value = cos(result->tail->value);
    else if (tmp->type == SIN && result->tail != NULL)
      result->tail->value = sin(result->tail->value);
    else if (tmp->type == TAN && result->tail != NULL)
      result->tail->value = tan(result->tail->value);
    else if (tmp->type == ACOS && result->tail != NULL)
      result->tail->value = acos(result->tail->value);
    else if (tmp->type == ASIN && result->tail != NULL)
      result->tail->value = asin(result->tail->value);
    else if (tmp->type == ATAN && result->tail != NULL)
      result->tail->value = atan(result->tail->value);
    else if (tmp->type == LN && result->tail != NULL)
      result->tail->value = log(result->tail->value);
    else if (tmp->type == LOG && result->tail != NULL)
      result->tail->value = log10(result->tail->value);
    else if (tmp->type == SQRT && result->tail != NULL)
      result->tail->value = sqrt(result->tail->value);
    else if (tmp->type == MOD && result->tail != NULL &&
             result->tail->prev != NULL) {
      res = fmod(result->tail->prev->value, result->tail->value);
      if (result->tail != NULL) DelBack(result);
      result->tail->value = res;
    } else if (tmp->type == ADD && result->tail != NULL &&
               result->tail->prev != NULL) {
      res = (result->tail->prev->value + result->tail->value);
      if (result->tail != NULL) DelBack(result);
      result->tail->value = res;
    } else if (tmp->type == SUB && result->tail != NULL &&
               result->tail->prev != NULL) {
      res = (result->tail->prev->value - result->tail->value);
      if (result->tail != NULL) DelBack(result);
      result->tail->value = res;
    } else if (tmp->type == DIV && result->tail != NULL &&
               result->tail->prev != NULL) {
      res = (result->tail->prev->value / result->tail->value);
      if (result->tail != NULL) DelBack(result);
      result->tail->value = res;
    } else if (tmp->type == MUL && result->tail != NULL &&
               result->tail->prev != NULL) {
      res = (result->tail->prev->value * result->tail->value);
      if (result->tail != NULL) DelBack(result);
      result->tail->value = res;
    } else if (tmp->type == POW && result->tail != NULL &&
               result->tail->prev != NULL) {
      res = pow(result->tail->prev->value, result->tail->value);
      if (result->tail != NULL) DelBack(result);
      result->tail->value = res;
    } else
      flag = 1;
    tmp = tmp->next;
  }
  // if (tmp != NULL) free(tmp);
  // if (OPZ->head != NULL) deleteList(&OPZ);
  return flag;
}

double s21_smart_calc(char* str, double x) {
  double itog = 0.0;
  LexemsList* Llist = parser(str);
  UnaryMagic(Llist);
  if (is_x(Llist)) put_x(Llist, x);
  LexemsList* OPZ = createList();
  int flag = toOPZ(Llist, OPZ);
  if (!flag) {
    LexemsList* res = createList();
    flag = calc(OPZ, res);
    // if (OPZ->head != NULL) deleteList(&OPZ);
    if (!flag && res->size == 1) {
      itog = res->head->value;
    } else
      itog = NAN;
    if (res) deleteList(&res);
  } else
    itog = NAN;
  deleteList(&Llist);
  deleteList(&OPZ);

  return itog;
}

double s21_credit_calc1(double months, double summ, double procents) {
  double resss;
  if (procents == 0) {
    resss = summ / months;
  } else {
    double r = procents / 1200;
    double tm = (1 + r);
    double temp = pow(tm, months);
    resss = summ * r * temp / (temp - 1);
  }
  resss = round(resss * 100) / 100;
  return resss;
}

LexemsList creditCalc2(double months, double summ, double procents) {
  LexemsList* res = createList();
  double b = summ / months;
  for (int i = 0; i < months; i++) {
    double sn = summ - (b * i);
    double p = sn * procents / 1200;
    double itog = b + p;
    itog = round(itog * 100) / 100;
    pushBack(res, DIGIT, 0, itog);
  }

  return *res;
}

// int main() {
//   char* str = "1*(1*(1*(1*(-1)))))";
//   int a = 1;
//   int b = isnan(s21_smart_calc(str, 0.0));
// }
