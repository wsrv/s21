#include <math.h>

#include "../s21_decimal.h"
#include "../support/support_functions.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) return 1;

  clean(dst);
  int error = 0;
  if (src < 0) {
    set_bit(dst, 127, 1);
    src = (-1) * src;
  }
  if (src > INT_MAX)
    error = 1;
  else
    dst->bits[0] = src;
  return error;
}