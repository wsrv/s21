#ifndef SUPPORT_FUNCTIONS_H_
#define SUPPORT_FUNCTIONS_H_
#define SIGN 0b0000000000000000000000000000000010000000000000000000000000000000
#define SIMPLE_SIGN 0b10000000000000000000000000000000
#define MIN 0b00000000000000000000000000000001
#define POW 0b0000000000000000000000000000000000000000111111110000000000000000
#define SIMPLE_POW \
  0b0000000000000000000000000000000000000000000000010000000000000000
#define STECK_OVERFLOW \
  0b1111111111111111111111111111111100000000000000000000000000000000
#define INF 0b0000000000000000000000000000000001111111100000000000000000000000
#define MAX_FLOAT 0b100000000000000000000000
#define S21_NULL ((void *)0)
#include "../s21_decimal.h"

typedef struct {
  uint64_t bits[8];
} s21_big_decimal;

typedef union {
  float f;
  struct {
    unsigned int mantisa : 23;
    unsigned int exponent : 8;
    unsigned int sign : 1;
  } parts;
} float_cast;

int big_clean(s21_big_decimal *value);
int clean(s21_decimal *value);
int clean_overflow(s21_big_decimal *value);
int get_bit(s21_decimal value, int index);

int result_rounding(s21_big_decimal *result, int round);
int nurlanization(s21_big_decimal *value_1, s21_big_decimal *value_2);
int s21_is_less_abs(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_mul_ten(s21_big_decimal *value);
int zero(s21_big_decimal result);
int left_shift(s21_big_decimal *value);

int error_function(s21_big_decimal* result, s21_big_decimal value_1,
                   s21_big_decimal value_2, int div);
int convert_to_decimal(s21_decimal *res, s21_big_decimal result);
int convert_to_big_decimal(s21_big_decimal *res, s21_decimal result);
int s21_big_add(s21_big_decimal val1, s21_big_decimal val2,
                s21_big_decimal *res);
int s21_div_ten(s21_big_decimal *value);
int get_big_bit(s21_big_decimal value, int index);
void s21_div_ten_u(s21_decimal dividend, s21_decimal *result);
void scale_sub_one(s21_decimal *a);
int s21_get_scale(s21_decimal value);
void set_bit(s21_decimal *dec, int index, int value);
int check (s21_decimal input);
int simple_sub(s21_decimal* val1, s21_decimal val2, s21_big_decimal* result);

// int output(s21_big_decimal value_1, s21_big_decimal value_2,
//            s21_big_decimal result);
// int print_dec_bit(s21_big_decimal dec);
// int right_shift_mini_dec(s21_decimal *value);
// int left_shift_mini_dec(s21_decimal *value);
// int right_shift(s21_big_decimal *value);
// void binarIntPrint(unsigned int n);
// void decimalPrint(s21_decimal n);
#endif