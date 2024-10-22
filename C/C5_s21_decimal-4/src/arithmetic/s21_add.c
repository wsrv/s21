#include "../s21_decimal.h"
#include "../support/support_functions.h"
int s21_add(s21_decimal val1, s21_decimal val2, s21_decimal *res) {
  if (!res) return 1;

  if ((val1.bits[3] & SIMPLE_SIGN) >> 31 &&
      !((val2.bits[3] & SIMPLE_SIGN) >> 31)) {
    val1.bits[3] += SIMPLE_SIGN;
    return s21_sub(val2, val1, res);
  }
  if (!((val1.bits[3] & SIMPLE_SIGN) >> 31) &&
      ((val2.bits[3] & SIMPLE_SIGN) >> 31)) {
    val2.bits[3] += SIMPLE_SIGN;
    return s21_sub(val1, val2, res);
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

  for (int i = 0; i <= 5; i++) {
    result.bits[i] += value_1.bits[i] + value_2.bits[i];
    if (result.bits[i] >> 32 && i < 3 && i % 2 == 0)
      result.bits[i + 2] += result.bits[i] >> 32;
  }
  result.bits[n - 1] |= (value_1.bits[n - 1] & POW);
  result.bits[n - 1] |= (value_1.bits[n - 1] & SIGN);
  if (zero(result)) big_clean(&result);
  result_rounding(&result, 0);
  answer = error_function(&result, value_1, value_2, 0);
  clean_overflow(&result);
  convert_to_decimal(res, result);
  return answer;
}

int s21_big_add(s21_big_decimal val1, s21_big_decimal val2,
                s21_big_decimal *res) {
  s21_big_decimal value_1 = val1;
  s21_big_decimal value_2 = val2;
  s21_big_decimal *result = res;
  big_clean(result);

  for (int i = 0; i <= 5; i++) {
    result->bits[i] += value_1.bits[i] + value_2.bits[i];
    if (result->bits[i] >> 32 && i < 3 && i % 2 == 0) {
      result->bits[i + 2] += (result->bits[i] >> 32);
      result->bits[i] &= ~STECK_OVERFLOW;
    }
  }
  // output(value_1, value_2, *result);
  return 0;
}
