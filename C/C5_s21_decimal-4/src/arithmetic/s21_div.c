#include "../s21_decimal.h"
#include "../support/support_functions.h"
int s21_div(s21_decimal val1, s21_decimal val2, s21_decimal* res) {
  if (!res) return 1;
  clean(res);

  int answer = 0;
  s21_big_decimal value_1;
  s21_big_decimal copy_value_1;
  s21_big_decimal value_2;
  s21_big_decimal copy_value_2;
  s21_big_decimal result;
  s21_big_decimal div;
  s21_decimal five = {{0b00000000000000000000000000000101, 0, 0, 0}};

  big_clean(&result);

  int pow = 0;

  convert_to_big_decimal(&value_1, val1);
  convert_to_big_decimal(&value_2, val2);
  convert_to_big_decimal(&copy_value_1, val1);
  convert_to_big_decimal(&copy_value_2, val2);
  convert_to_big_decimal(&div, val2);

  nurlanization(&value_1, &value_2);

  for (int i = 0; !zero(value_1) && i < 96; i++) {
    convert_to_decimal(&val1, value_1);
    convert_to_decimal(&val2, value_2);

    if (s21_is_less_or_equal(val1, val2)) {
      convert_to_big_decimal(&value_1, val1);
      left_shift(&value_1);
      convert_to_decimal(&val1, value_1);
      result.bits[6] += SIMPLE_POW;
      pow++;
    }
    if (s21_is_less_or_equal(val2, val1)) {
      simple_sub(&val1, val2, &result);
    }
    convert_to_big_decimal(&value_1, val1);
  }
  convert_to_decimal(res, result);

  for (int j = 0; j < pow; j++) {
    convert_to_decimal(res, result);
    s21_mul(*res, five, res);
    convert_to_big_decimal(&result, *res);
  }

  while ((result.bits[6] & POW) && !(result.bits[0] % 10)) {
    s21_div_ten(&result);
    result.bits[6] -= SIMPLE_POW;
  }
  if ((val1.bits[3] & SIGN) || (val2.bits[3] & SIGN)) result.bits[6] += SIGN;
  if (zero(copy_value_1)) big_clean(&result);
  convert_to_decimal(res, result);

  return answer;
}

int simple_sub(s21_decimal* val1, s21_decimal val2, s21_big_decimal* result) {
  int long1 = 0;
  int long2 = 0;
  // int n =7;
  s21_decimal copy_val2 = val2;
  s21_big_decimal value_1;
  // s21_big_decimal copy_value_1;
  s21_big_decimal value_2;
  s21_big_decimal copy_value_2;
  s21_big_decimal div;
  convert_to_big_decimal(&value_1, *val1);
  convert_to_big_decimal(&value_2, val2);
  convert_to_big_decimal(&copy_value_2, val2);
  convert_to_big_decimal(&div, val2);

  for (long1 = 92; long1 >= 0; long1--)
    if (get_bit(*val1, long1)) break;
  for (long2 = 92; long2 >= 0; long2--)
    if (get_bit(val2, long2)) break;

  for (int k = 0; k < long1 - long2; k++) left_shift(&value_2);
  convert_to_decimal(&val2, value_2);

  while (s21_is_greater_or_equal(*val1, copy_val2)) {
    if (s21_is_less_or_equal(val2, *val1)) {
      s21_sub(*val1, val2, val1);
      result->bits[0]++;
    }
    if (val2.bits[0] != copy_value_2.bits[0])
      val2.bits[0] >>= 1;  // right shift
    else
      break;
    left_shift(result);
    convert_to_big_decimal(&value_1, *val1);
  }
  // output(value_1, value_2, *result);
  return 0;
}