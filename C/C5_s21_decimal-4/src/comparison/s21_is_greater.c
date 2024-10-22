#include "../s21_decimal.h"
#include "../support/support_functions.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_2, value_1);
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2))
    return 1;
  return 0;
}