#include <math.h>

#include "../s21_decimal.h"
#include "../support/support_functions.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  *dst = 0.0;
  int scale = s21_get_scale(src);
  if (!dst || scale == -1) return 1;

  double tmp = 0.0;
  for (int i = 0; i < 96; i++) tmp += (get_bit(src, i) * pow(2, i));
  tmp = tmp * pow(10, -scale);
  if (get_bit(src, 127)) tmp = tmp * (-1);
  *dst = tmp;
  return 0;
}