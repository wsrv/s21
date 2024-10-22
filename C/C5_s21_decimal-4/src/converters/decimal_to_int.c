#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"
#include "../support/support_functions.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  int scale = s21_get_scale(src);
  if (src.bits[1] || src.bits[2] || scale == -1 || src.bits[0] >> 31) {
    error = 1;
  } else {
    *dst = src.bits[0];
    if (scale > 0 && scale <= 28) {
      *dst = *dst / pow(10, scale);
    }
  }
  if (get_bit(src, 127)) *dst = *dst * (-1);
  return error;
}