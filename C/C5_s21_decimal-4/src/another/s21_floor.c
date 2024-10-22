#include "../s21_decimal.h"
#include "../support/support_functions.h"
int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 1;
  if (!result) return 1;
  clean(result);

  int scale = s21_get_scale(value);
  if (scale == 0) {
    error = 0;
    for (int i = 0; i < 4; ++i) result->bits[i] = value.bits[i];
  } else if (scale != -1) {
    error = 0;
    s21_decimal tmp1, tmp2;
    clean(&tmp1);
    clean(&tmp2);
    if (get_bit(value, 127) == 0) {
      s21_truncate(value, &tmp1);
      for (int i = 0; i < 4; ++i) result->bits[i] = tmp1.bits[i];
    } else {
      s21_truncate(value, &tmp1);
      if (s21_is_equal(tmp1, value) == 0) {
        s21_decimal one;
        one.bits[0] = 0b00000000000000000000000000000001;
        one.bits[1] = 0b00000000000000000000000000000000;
        one.bits[2] = 0b00000000000000000000000000000000;
        one.bits[3] = 0b00000000000000000000000000000000;
        error = s21_sub(tmp1, one, &tmp2);
        for (int i = 0; i < 4; ++i) tmp1.bits[i] = tmp2.bits[i];
      }
      for (int i = 0; i < 4; ++i) result->bits[i] = tmp1.bits[i];
    }
  }
  return error;
}