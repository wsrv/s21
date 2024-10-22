#include "../s21_decimal.h"
#include "../support/support_functions.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result && s21_get_scale(value) != -1) {
    clean(result);
    for (int i = 0; i < 4; i++) result->bits[i] = value.bits[i];
    if (get_bit(value, 127) == 0)  // if positiv with zero in the end
      set_bit(result, 127, 1);
    else
      set_bit(result, 127, 0);
  } else
    error = 1;
  return error;
}