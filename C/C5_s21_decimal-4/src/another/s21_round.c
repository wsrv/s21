#include "../s21_decimal.h"
#include "../support/support_functions.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 1;
  if (result) {
    clean(result);
    int scale = s21_get_scale(value);
    if ((scale == 0) ||
        (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0)) {
      error = 0;
      for (int i = 0; i < 4; ++i) result->bits[i] = value.bits[i];
    } else if (scale != -1) {
      error = 0;
      s21_decimal tmp1;
      clean(&tmp1);
      s21_decimal tmp2;
      clean(&tmp2);
      s21_decimal zero_five = {{0b00000000000000000000000000000101,
                                0b00000000000000000000000000000000,
                                0b00000000000000000000000000000000,
                                0b00000000000000010000000000000000}};
      s21_decimal one = {{0b00000000000000000000000000000001,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000,
                          0b00000000000000000000000000000000}};
      s21_truncate(value, &tmp1);
      s21_sub(value, tmp1, &tmp2);
      set_bit(&tmp2, 127, 0);
      *result = tmp1;
      if (s21_is_greater_or_equal(tmp2, zero_five))
        error = s21_add(tmp1, one, result);
    }
  }
  if (error != 0 && error != 1) error = 1;
  return error;
}
