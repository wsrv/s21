#include "../s21_decimal.h"
#include "../support/support_functions.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  if (check(value_1) || check(value_2)) return 1;
  int res = 0;
  int n = 7;

  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;
  convert_to_big_decimal(&big_value_1, value_1);
  convert_to_big_decimal(&big_value_2, value_2);
  nurlanization(&big_value_1, &big_value_2);
  if (zero(big_value_1) && zero(big_value_2)) return 0;
  if ((big_value_1.bits[n - 1] & SIGN) && !(big_value_2.bits[n - 1] & SIGN))
    res = 1;
  if ((big_value_1.bits[n - 1] & SIGN) == (big_value_2.bits[n - 1] & SIGN))
    res = s21_is_less_abs(big_value_1, big_value_2);
  if ((big_value_1.bits[n - 1] & SIGN) && big_value_2.bits[n - 1] & SIGN)
    res = !res;
  return res;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  if (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2)) return 1;
  return 0;
}

int s21_is_less_abs(s21_big_decimal value_1, s21_big_decimal value_2) {
  int res = 0;
  int n = 7;

  s21_decimal m_value_1;
  s21_decimal m_value_2;
  convert_to_decimal(&m_value_1, value_1);
  convert_to_decimal(&m_value_2, value_2);

  if (s21_is_equal(m_value_1, m_value_2)) return 0;
  if ((value_1.bits[n - 1] & POW) > (value_2.bits[n - 1] & POW)) return 1;
  if ((value_1.bits[n - 1] & POW) == (value_2.bits[n - 1] & POW)) {
    for (int i = n - 2; i >= 0; i--) {
      if (value_1.bits[i] > value_2.bits[i]) {
        i = -1;
        break;
      }
      if (value_1.bits[i] < value_2.bits[i]) {
        res = 1;
        i = -1;
        break;
      }
    }
  }
  return res;
}