#include "../s21_decimal.h"
#include "../support/support_functions.h"
int s21_mul(s21_decimal val1, s21_decimal val2, s21_decimal *res) {
  if (!res) return 1;
  int answer = 0;
  int n = 7;
  s21_decimal value_2d = val2;
  s21_big_decimal value_1;
  s21_big_decimal value_2;
  s21_big_decimal result;
  big_clean(&result);
  convert_to_big_decimal(&value_1, val1);
  convert_to_big_decimal(&value_2, val2);
  int last = 0;
  for (int i = 95; i >= 0; i--)
    if (get_bit(value_2d, i)) {
      last = i;
      break;
    }

  for (int i = 0; i <= last; i++) {
    if (get_bit(value_2d, i)) s21_big_add(value_1, result, &result);
    left_shift(&value_1);
  }
  if (!zero(result)) {
    result.bits[n - 1] +=
        ((value_1.bits[n - 1] & POW) + (value_2.bits[n - 1] & POW)) & POW;
    result.bits[n - 1] +=
        ((value_1.bits[n - 1] & SIGN) + (value_2.bits[n - 1] & SIGN)) & SIGN;
  } else
    big_clean(&result);
  result_rounding(&result, 0);
  answer = error_function(&result, value_1, value_2, 0);
  clean_overflow(&result);
  convert_to_decimal(res, result);
  // output(value_1, value_2, result);
  return answer;
}