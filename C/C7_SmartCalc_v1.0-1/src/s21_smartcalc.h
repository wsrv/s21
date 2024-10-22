#ifndef S21_SMARTCALC_H
#define S21_SMARTCALC_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

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
  X_X = 19
} lexems_enum;

typedef struct Node {
  double value;
  int priority;
  lexems_enum type;
  struct Node* next;
  struct Node* prev;
} Node;

typedef struct LexemsList {
  int size;
  struct Node* head;
  struct Node* tail;
} LexemsList;

LexemsList* createList();
void deleteList(LexemsList** list);
void pushBack(LexemsList* list, lexems_enum type, int priority, double value);
Node* getNth(LexemsList* list, size_t index);
void deleteNth(LexemsList* list, size_t index);
void pushFront(LexemsList* list, lexems_enum type, int priority, double value);
void insert(LexemsList* list, size_t index, lexems_enum type, int priority,
            double value);
void DelBack(LexemsList* list);
int toOPZ(LexemsList* Llist, LexemsList* result);
double getNum(char* str, int* i);
LexemsList* parser(char* str);
int is_x(LexemsList* list);
void put_x(LexemsList* list, double x);
void UnaryMagic(LexemsList* list);
void Printer(LexemsList* list);
int calc(LexemsList* OPZ, LexemsList* result);
double s21_smart_calc(char* str, double x);
double s21_credit_calc1(double months, double summ, double procents);
LexemsList creditCalc2(double months, double summ, double procents);

#endif  // S21_SMARTCALC_H