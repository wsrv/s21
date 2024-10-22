#include <math.h>
#include <stdlib.h>

#include "../s21_decimal.h"
#include "../support/support_functions.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst || src == INFINITY) return 1;
  clean(dst);
  if (src == 0.0) return 0;
  if (0 < fabs(src) && fabs(src) < pow(10, -28)) return 1;

  int error = 0;
  float_cast float_num = {0};
  float_num.f = src;
  int exp = (float_num.parts.exponent - 127);
  int mant = float_num.parts.mantisa;

  mant += MAX_FLOAT;  // +1
  int k = 0;
  int j = 0;

  long double mantis = 1;
  for (int j = 1; j <= 23; j++) {
    if (mant >> (23 - j) & 1) mantis += powl(2, -j);
  }
  mantis *= powl(2, exp);
  int copy_mantis = mantis;
  for (k = 0; k < 7 && copy_mantis; k++) copy_mantis /= 10;

  for (j = 0; j < 7 - k + 1; j++) {
    mantis *= 10;
  }

  if ((int)mantis % 10 >= 5) mantis += 10;
  mantis /= 10;
  j--;
  while ((int)mantis % 10 == 0 && mantis) {
    mantis /= 10;
    j--;
  }
  if (mantis == 0.0) j = 0;

  mantis = (int)mantis;
  s21_from_int_to_decimal((int)mantis, dst);
  dst->bits[3] += j << 16;
  dst->bits[3] += float_num.parts.sign << 31;

  // s21_big_decimal big;
  // convert_to_big_decimal(&big, *dst);
  // output(big, big, big);
  return error;
}
