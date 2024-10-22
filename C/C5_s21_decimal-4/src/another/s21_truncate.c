#include "../s21_decimal.h"
#include "../support/support_functions.h"
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 1;
  if (result) {
    clean(result);
    int scale = s21_get_scale(value);
    if (!scale) {
      error = 0;
      for (int i = 0; i < 4; ++i) result->bits[i] = value.bits[i];
    } else if (scale != -1) {
      s21_decimal tmp1, tmp2;
      clean(&tmp1);
      clean(&tmp2);
      for (int i = 0; i < 4; ++i) tmp1.bits[i] = value.bits[i];
      error = 0;
      for (int s = 0; s < scale; s++) {
        s21_div_ten_u(tmp1, &tmp2);
        scale_sub_one(&tmp2);
        for (int i = 0; i < 4; ++i) tmp1.bits[i] = tmp2.bits[i];
      }
      for (int i = 0; i < 4; ++i) result->bits[i] = tmp1.bits[i];
    }
  }
  return error;
}
