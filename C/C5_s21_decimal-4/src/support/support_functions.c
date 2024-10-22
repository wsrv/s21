#include "support_functions.h"

#include <math.h>

int nurlanization(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  int n = 7;
  long unsigned factor1 = ((value_1->bits[n - 1] & POW) >> 16);
  long unsigned factor2 = ((value_2->bits[n - 1] & POW) >> 16);
  if (factor1 > factor2)
    for (unsigned i = 0; i < factor1 - factor2; i++) {
      s21_mul_ten(value_2);
      value_2->bits[n - 1] += SIMPLE_POW;
    }

  if (factor1 < factor2)
    for (unsigned i = 0; i < factor2 - factor1; i++) {
      s21_mul_ten(value_1);
      value_1->bits[n - 1] += SIMPLE_POW;
    }
  return 0;
}

int s21_mul_ten(s21_big_decimal *value) {
  int n = 7;
  for (int i = 0; i < n - 2; i += 2) {
    value->bits[i] *= 10;
    value->bits[i + 1] *= 10;
  }

  for (int i = 0; i < n - 2; i++) {
    if (i < 3) {
      value->bits[i + 2] += (value->bits[i] >> 32);
      value->bits[i] &= ~STECK_OVERFLOW;
    }
    if (value->bits[i] >> 32) {
      value->bits[i + 1] += value->bits[i] >> 32;
      value->bits[i] &= ~STECK_OVERFLOW;
    }
  }
  return 0;
}

int s21_div_ten(s21_big_decimal *value) {
  int ost = value->bits[0] % 10;
  for (int i = 5; i >= 0; i--) {
    if (i > 0 && i < 5) {
      value->bits[i - 2] &= ~STECK_OVERFLOW;
      value->bits[i - 2] += (value->bits[i] % 10) << 32;
    }
    if (i == 5) {
      value->bits[i - 1] += value->bits[i] % 10 << 32;
    }
    value->bits[i] /= 10;
  }
  return ost;
}

int clean_overflow(s21_big_decimal *value) {
  int n = 7;
  for (int i = 0; i < n; i++) {
    if (i % 2 != 0) value->bits[i] = 0;
    if (i % 2 == 0) value->bits[i] &= ~STECK_OVERFLOW;
  }

  return 0;
}

int get_bit(s21_decimal value, int index) {
  int big = (index / 32);
  int small = 31 - index % 32;
  int res = ((value.bits[big] << small) >> 31);
  return res != 0 ? 1 : 0;
}
int get_big_bit(s21_big_decimal value, int index) {
  int big = (index / 64);
  int small = 63 - index % 64;
  int res = ((value.bits[big] << small) >> 63);
  return res * -1;
}

int big_clean(s21_big_decimal *value) {
  int n = 7;
  for (int i = 0; i <= n; i++) value->bits[i] = 0;
  return 0;
}

int clean(s21_decimal *value) {
  int n = 3;
  for (int i = 0; i <= n; i++) value->bits[i] = 0;
  return 0;
}

int result_rounding(s21_big_decimal *result, int ost) {
  int n = 7;
  int fail = 0;
  if (result->bits[n - 2] && (result->bits[n - 1] & POW)) {
    if (ost != 0) {
      fail = 1;
    }
    ost = s21_div_ten(result);
    result->bits[n - 1] -= SIMPLE_POW;
    result_rounding(result, ost);
  } else if (zero(*result))
    big_clean(result);

  if (ost == 5 && !fail)
    if (get_big_bit(*result, 0)) result->bits[0]++;
  return 0;
}

int convert_to_decimal(s21_decimal *res, s21_big_decimal result) {
  clean(res);
  for (int i = 0; i <= 3; i++) res->bits[i] = result.bits[2 * i];
  return 0;
}
int convert_to_big_decimal(s21_big_decimal *res, s21_decimal result) {
  big_clean(res);
  for (int i = 0; i <= 3; i++) res->bits[2 * i] = result.bits[i];
  return 0;
}

int zero(s21_big_decimal result) {
  int res = 1;
  int n = 7;
  for (int i = n - 2; i >= 0; i--)
    if (result.bits[i]) {
      res = 0;
      break;
    }
  return res;
}

int check(s21_decimal input) {
  if (((input.bits[3] & (~SIGN)) >> 16) > 28) return 1;
  return 0;
}
int error_function(s21_big_decimal *result, s21_big_decimal value_1,
                   s21_big_decimal value_2, int div) {
  int n = 7;
  if (div && zero(value_2)) {
    big_clean(result);
    return 3;
  }
  if (!(result->bits[n - 1] & POW) &&
      (result->bits[n - 3] >> 32 || result->bits[n - 2])) {
    big_clean(result);
    return 1;
  }
  if (((result->bits[n - 1] & ~SIGN) >> 16) > 28 ||
      ((value_1.bits[n - 1] & ~SIGN) >> 16) > 28 ||
      ((value_2.bits[n - 1] & ~SIGN) >> 16) > 28) {
    big_clean(result);
    return 2;
  }
  return 0;
}

int left_shift(s21_big_decimal *value) {
  for (int i = 0; i <= 4; i += 2) value->bits[i] <<= 1;

  value->bits[5] <<= 1;

  for (int i = 0; i <= 2; i += 2) {
    value->bits[i + 2] += ((value->bits[i] & (STECK_OVERFLOW)) >> 32);
    value->bits[i] &= ~STECK_OVERFLOW;
  }
  value->bits[5] += (value->bits[4] & STECK_OVERFLOW) >> 32;
  value->bits[4] &= ~STECK_OVERFLOW;
  return 0;
}

void s21_div_ten_u(s21_decimal dividend, s21_decimal *result) {
  s21_big_decimal value_1;
  convert_to_big_decimal(&value_1, dividend);
  s21_div_ten(&value_1);
  convert_to_decimal(result, value_1);
}

void scale_sub_one(s21_decimal *a) {
  int scale = s21_get_scale(*a);
  if (scale > 0) {
    a->bits[3] = ((a->bits[3] >> 16) - 1) << 16;
  }
}

int s21_get_scale(s21_decimal value) {
  int res = value.bits[3];
  res = res << 1;
  res = res >> 17;
  if (res < 0 || res > 28) res = -1;
  return res;
}

void set_bit(s21_decimal *dec, int index, int value) {
  int big = (index / 32);
  int small = 31 - index % 32;
  int mask = 0b11111111111111111111111111111111;
  mask = (((mask << small) >> 31) << (31 - small)) * (-1);
  if (value == 0) {
    mask = ~(mask);
    dec->bits[big] = dec->bits[big] & mask;
  } else
    dec->bits[big] = dec->bits[big] | mask;
}

// int output(s21_big_decimal value_1, s21_big_decimal value_2,
//            s21_big_decimal result) {
//   print_dec_bit(value_1);
//   printf("+\n");
//   print_dec_bit(value_2);
//   printf("=\n");
//   print_dec_bit(result);
//   printf(
//       "------------------------------------------------------------------------"
//       "----------------------------------------\n");
//   return 0;
// }
// int print_dec_bit(s21_big_decimal dec) {
//   for (int i = 1; i <= 7; i += 2) {
//     for (int j = 63; j >= 0; j--) printf("%ld", (dec.bits[i] >> j) & 1);
//     for (int j = 63; j >= 0; j--) printf("%ld", (dec.bits[i - 1] >> j) & 1);
//     printf("\n");
//   }
//   return 0;
// }

// void binarIntPrint(unsigned int n) {
//   printf("0b");
//   for (int j = 31; j >= 0; j--) printf("%d", (n >> j) & 1);
//   printf("|%d\n", n);
// }

// void decimalPrint(s21_decimal n) {
//   for (int i = 0; i < 4; i++) binarIntPrint(n.bits[i]);
// }

// int right_shift(s21_big_decimal *value) {
//   for (int i = 4; i >= 2; i -= 2) value->bits[i - 2] += (value->bits[i] <<
//   32); for (int i = 0; i <= 4; i++) value->bits[i] >>= 1;
//   clean_overflow(value);
//   return 0;
// }

// int left_shift_mini_dec(s21_decimal *value) {
//   for (int i = 0; i <= 2; i++) {
//     value->bits[i + 1] += (value->bits[i] >> 31);
//   }

//   for (int i = 0; i <= 2; i++) value->bits[i] <<= 1;

//   return 0;
// }