#include "../s21_decimal.h"
#include "../support/support_functions.h"
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  int n = 7;
  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;
  convert_to_big_decimal(&big_value_1, value_1);
  convert_to_big_decimal(&big_value_2, value_2);
  nurlanization(&big_value_1, &big_value_2);
  if (zero(big_value_1) && zero(big_value_2))
    res = 1;
  else
    for (int i = 0; i <= n; i++)
      if (big_value_1.bits[i] != big_value_2.bits[i]) {
        res = 0;
        break;
      }
  return res;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  if (!s21_is_equal(value_1, value_2)) return 1;
  return 0;
}