#include "../s21_decimal.h"
#include "../support/support_functions.h"

int s21_sub(s21_decimal val1, s21_decimal val2, s21_decimal *res) {
  if (!res) return 1;

  if ((val1.bits[3] & SIMPLE_SIGN) != (val2.bits[3] & SIMPLE_SIGN)) {
    val2.bits[3] += SIMPLE_SIGN;
    return s21_add(val1, val2, res);
  }

  int answer = 0;
  int n = 7;
  s21_big_decimal value_1;
  s21_big_decimal value_2;
  s21_big_decimal result;
  big_clean(&result);
  clean(res);

  convert_to_big_decimal(&value_1, val1);
  convert_to_big_decimal(&value_2, val2);
  nurlanization(&value_1, &value_2);

  if (s21_is_less_abs(value_2, value_1)) {
    for (int i = 0; i <= n - 2; i++) {
      if (value_1.bits[i] < value_2.bits[i] && i < 3) {
        result.bits[i] += SIGN << 1;
        result.bits[i + 2]--;
      }
      result.bits[i] += value_1.bits[i] - value_2.bits[i];
    }
    result.bits[n - 1] |= (value_1.bits[n - 1] & SIGN);
    result.bits[n - 1] |= (value_1.bits[n - 1] & POW);
  }

  if (s21_is_less_abs(value_1, value_2)) {
    value_2.bits[n - 1] += SIGN;
    for (int i = 0; i < n - 1; i++) {
      if (value_1.bits[i] > value_2.bits[i] && i < 5) {
        if (i <= 3) result.bits[i + 2]--;
        if (i > 3) result.bits[i + 1]--;
        result.bits[i] +=
            0b0000000000000000000000000000000100000000000000000000000000000000;
      }
      result.bits[i] += value_2.bits[i] - value_1.bits[i];
    }
    result.bits[n - 1] |= (value_2.bits[n - 1] & SIGN);
    result.bits[n - 1] |= (value_1.bits[n - 1] & POW);
  }
  if (zero(result)) big_clean(&result);
  result_rounding(&result, 0);
  answer = error_function(&result, value_1, value_2, 0);
  clean_overflow(&result);
  convert_to_decimal(res, result);
  // output(value_1, value_2, result);
  return answer;
}