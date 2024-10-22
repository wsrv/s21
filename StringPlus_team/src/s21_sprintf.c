// #include <stdarg.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "s21_string.h"

int s21_sprintf(char *buf, char *format, ...) {
  write_in_buf output = {0};
  va_start(output.argptr, format);
  buf[0] = '\0';
  int format_len = s21_strlen(format);
  for (output.format_index = 0;
       output.format_index < format_len && output.res != -1;
       output.format_index++) {
    output.flag_plus = 0;
    output.flag_space = 0;
    output.flag_minus = 0;
    output.flag_zero = 0;
    output.space = 0;
    output.flag_lattice = 0;
    output.str_long = 0;
    output.flag_add_space = 0;
    output.flag_h = 0;
    output.flag_l = 0;
    output.flag_L = 0;
    output.flag_g = 0;
    output.flag_e = 0;
    output.flag_E = 0;
    output.flag_x = 0;
    output.flag_o = 0;
    output.flag_u = 0;
    output.flag_dot = 0;
    output.flag_negative = 0;
    output.flag_positiv = 0;
    output.flag_accuracy = 0;
    output.accuracy = 6;
    if (format[output.format_index] == '%') {
      output.format_index++;
      sellect_flags(buf, &output, format);
      if (output.flag_minus) add_space(&output, buf);
    } else {
      buf[output.index_buf_mass++] = format[output.format_index];
      output.res++;
    }
    buf[output.index_buf_mass + 1] = '\0';
  }
  va_end(output.argptr);
  return output.res;
}

void sellect_flags(char *buf, write_in_buf *output, char *format) {
  switch (format[output->format_index]) {
    case '-':
      output->flag_minus = 1;
      output->format_index++;
      sellect_flags(buf, output, format);
      break;
    case '+':
      output->flag_plus = 1;
      output->format_index++;
      sellect_flags(buf, output, format);
      break;
    case ' ':
      output->flag_space = 1;
      output->format_index++;
      sellect_flags(buf, output, format);
      break;
    case '0':
      output->flag_zero = 1;
      output->format_index++;
      sellect_flags(buf, output, format);
      break;
    case '#':
      output->flag_lattice = 1;
      output->format_index++;
      sellect_flags(buf, output, format);
      break;
    default:
      sellect_width(buf, output, format);
      break;
  }
}
void sellect_width(char *buf, write_in_buf *output, char *format) {
  switch (format[output->format_index]) {
    case '0' ... '9':
      count_space(output, format);
      sellect_accuracy(buf, output, format);
      break;
    case '*':
      output->space = va_arg(output->argptr, int);
      if (output->space < 0) {
        output->flag_minus = 1;
        output->space *= -1;
      }
      output->format_index++;
      sellect_accuracy(buf, output, format);
      break;
    default:
      sellect_accuracy(buf, output, format);
      break;
  }
}
void sellect_accuracy(char *buf, write_in_buf *output, char *format) {
  int rub_flag = 0;
  if (format[output->format_index] == '.') {
    output->format_index++;
    output->flag_accuracy = 1;
    switch (format[output->format_index]) {
      case '*':
        output->accuracy = va_arg(output->argptr, int);
        if (output->accuracy == 0) output->flag_dot = 1;
        output->format_index++;
        sellect_modifier(buf, output, format);
        break;
      case '0' ... '9':
        rub_flag = output->space;
        count_space(output, format);
        output->accuracy = output->space;
        output->space = rub_flag;
        if (output->accuracy == 0) output->flag_dot = 1;
        sellect_modifier(buf, output, format);
        break;
      default:
        output->flag_dot = 1;
        sellect_modifier(buf, output, format);
        break;
    }
  } else
    sellect_modifier(buf, output, format);
}

void sellect_modifier(char *buf, write_in_buf *output, char *format) {
  switch (format[output->format_index]) {
    case 'h':
      output->format_index++;
      output->flag_h = 1;
      sellect_type(buf, output, format);
      break;
    case 'l':
      output->format_index++;
      output->flag_l = 1;
      sellect_type(buf, output, format);
      break;
    case 'L':
      output->format_index++;
      output->flag_L = 1;
      sellect_type(buf, output, format);
      break;
    default:
      sellect_type(buf, output, format);
      break;
  }
}

void sellect_type(char *buf, write_in_buf *output, char *format) {
  switch (format[output->format_index]) {
    case 'd':
      flag_d(buf, output);
      break;
    case 'c':
      flag_c(buf, output);
      break;
    case 's':
      flag_s(buf, output);
      break;
    case 'f':
      flag_f(buf, output);
      break;
    case 'u':
      output->flag_u = 1;
      flag_u(buf, output);
      break;
    case 'g':
      flag_g(buf, output);
      break;
    case 'G':
      flag_g(buf, output);
      break;
    case 'e':
      output->flag_e = 1;
      flag_e(buf, output);
      break;
    case 'E':
      output->flag_E = 1;
      flag_e(buf, output);
      break;
    case 'x':
      output->flag_x = 1;
      flag_x(buf, output);
      break;
    case 'X':
      flag_x(buf, output);
      break;
    case 'o':
      output->flag_o = 1;
      flag_x(buf, output);
      break;
    case 'p':
      flag_p(buf, output);
      break;
    case '%':
      buf[output->index_buf_mass++] = '%';
      buf[output->index_buf_mass + 1] = '\0';
      output->res++;
      break;
    default:
      // output->error++;
      break;
  }
}

void flag_d(char *buf, write_in_buf *output) {
  char str[256];
  long int input_data;
  if (output->flag_l)
    input_data = va_arg(output->argptr, long int);
  else
    input_data = va_arg(output->argptr, int);
  if (output->flag_h) input_data = (short int)input_data;
  itoa(output, input_data, str, 0);
  output->str_long = s21_strlen(str);
  add_sign(output, buf);
  if (!output->flag_minus) add_space(output, buf);
  buf = s21_strcat(buf, str);
  output->index_buf_mass += s21_strlen(str);
  output->res += s21_strlen(str);
}

void flag_c(char *buf, write_in_buf *output) {
  output->str_long = 1;
  if (output->flag_zero) output->flag_zero = 0;
  if (!output->flag_minus) add_space(output, buf);
  buf[output->index_buf_mass++] = va_arg(output->argptr, int);
  buf[output->index_buf_mass] = '\0';
  output->res++;
}

void flag_f(char *buf, write_in_buf *output) {
  int itsFloat = 1;
  char str[256];
  if (output->accuracy < 0) output->accuracy = 6;
  if (output->flag_dot) output->accuracy = 0;
  if (output->flag_dot && output->flag_lattice) output->flag_dot = 0;

  if (output->flag_L) {
    long double input_long_double = va_arg(output->argptr, long double);
    itoa(output, input_long_double, str, itsFloat);
  } else {
    double input_double = va_arg(output->argptr, double);
    itoa(output, input_double, str, itsFloat);
  }
  output->str_long = s21_strlen(str);
  add_sign(output, buf);
  if (!output->flag_minus) add_space(output, buf);

  buf = s21_strcat(buf, str);
  output->index_buf_mass += s21_strlen(str);
  output->res += s21_strlen(str);
}

void flag_s(char *buf, write_in_buf *output) {
  char strn[256];
  char *str2 = '\0';
  wchar_t *str_wchar;
  // str2 = str_wchar;
  if (output->flag_l)
    str_wchar = va_arg(output->argptr, wchar_t *);
  else
    str2 = va_arg(output->argptr, char *);

  strn[256] = '\0';
  if (!output->flag_accuracy) {
    strcpy(strn, str2);
  } else {
    if (output->accuracy < 0) output->accuracy = (int)s21_strlen(str2);
    s21_strncpy(strn, str2, output->accuracy);
    strn[output->accuracy] = '\0';
  }
  output->str_long = s21_strlen(strn);
  add_sign(output, buf);
  if (!output->flag_minus) add_space(output, buf);
  output->index_buf_mass += s21_strlen(strn);
  buf = s21_strcat(buf, strn);
  output->res += s21_strlen(strn);

  // if (output->flag_l) {
  //   buf[0] = '\0';
  //   output->res = -1;
  // }
  str_wchar = str_wchar;
}

void flag_u(char *buf, write_in_buf *output) {
  char str[256];
  unsigned int input_data;
  if (output->flag_l)
    input_data = va_arg(output->argptr, long int);
  else
    input_data = va_arg(output->argptr, unsigned int);
  if (output->flag_h) input_data = (unsigned short int)input_data;
  itoa(output, input_data, str, 0);
  output->str_long = s21_strlen(str);
  add_sign(output, buf);
  if (!output->flag_minus) add_space(output, buf);
  buf = s21_strcat(buf, str);
  output->index_buf_mass += s21_strlen(str);
  output->res += s21_strlen(str);
}

void flag_g(char *buf, write_in_buf *output) {
  char str[256];
  long double input_double;
  output->flag_g = 1;
  if (output->flag_dot) output->accuracy = 1;
  input_double = va_arg(output->argptr, double);

  scientific_notation(output, str, input_double);
  add_sign(output, buf);

  output->str_long = s21_strlen(str);
  if (!output->flag_minus) add_space(output, buf);
  buf = s21_strcat(buf, str);
  output->index_buf_mass += s21_strlen(str);
  output->res += s21_strlen(str);
}

void flag_e(char *buf, write_in_buf *output) {
  char str[256];
  long double input_double;
  input_double = va_arg(output->argptr, double);
  scientific_notation(output, str, input_double);
  add_sign(output, buf);
  output->str_long = s21_strlen(str);
  if (!output->flag_minus) add_space(output, buf);
  buf = s21_strcat(buf, str);
  output->index_buf_mass += s21_strlen(str);
  output->res += s21_strlen(str);
}

void flag_x(char *buf, write_in_buf *output) {
  char str[256];
  long int input_data;
  input_data = va_arg(output->argptr, int);
  hexadecimal(output, str, input_data);
  output->str_long = s21_strlen(str);
  if (!output->flag_minus) add_space(output, buf);
  buf = s21_strcat(buf, str);
  output->index_buf_mass += s21_strlen(str);
  output->res += s21_strlen(str);
}

void flag_p(char *buf, write_in_buf *output) {
  buf = buf;
  output->accuracy = output->accuracy;
  // char str[256];
  //  char* input_data;
  //  input_data = va_arg(output->argptr, void*);
  //  printf("%c\n", input_data[0]);
}
void itoa(write_in_buf *output, long double n, char s[], int itsFloat) {
  long int i = 0, j = 0, notWhole = -1;
  long double origin_n_doub = n;
  long int origin_n_int = n;
  char c;
  s[0] = '\0';
  if ((n) < 0) n *= -1;
  if (itsFloat) {
    for (notWhole = 0; notWhole < output->accuracy + 1; notWhole++) n *= 10;
    if ((long int)n % 10 >= 5) {
      n /= 10;
      n++;
    } else
      n /= 10;
    n = (long int)n;
    notWhole--;
  }

  do {
    if (notWhole == i && (output->accuracy != 0 || output->flag_lattice))
      s[i++] = '.';
    int n_positiv = (long int)n % 10;
    if (n_positiv < 0) n_positiv *= -1;
    s[i] = n_positiv + '0';
    n /= 10;
    i++;
  } while ((long int)n != 0);
  if (((origin_n_doub < 1 && origin_n_doub >= 0) ||
       (origin_n_doub > -1 && origin_n_doub <= 0)) &&
      output->accuracy != 0 && itsFloat) {
    s[i++] = '.';
    s[i++] = '0';
  }
  s[i] = '\0';
  while (output->flag_accuracy == 1 && !output->flag_g && !output->flag_dot &&
         (int)s21_strlen(s) < output->accuracy) {
    s[i++] = '0';
    s[i] = '\0';
  }
  // if(output->flag_dot && sign == 0) {
  //   sign = 1;
  //   i=0;
  //   }
  if (origin_n_doub >= 0 && output->flag_space && !output->flag_zero &&
      !output->flag_plus && !output->flag_u)
    s[i++] = ' ';
  if (origin_n_doub >= 0 && output->flag_space && output->flag_zero &&
      !output->flag_plus && !output->flag_u)
    output->flag_add_space = 1;
  if (origin_n_doub < 0 && !output->flag_u && !output->flag_zero) s[i++] = '-';
  if (origin_n_doub < 0 && output->flag_zero) output->flag_negative = 1;

  if (origin_n_doub >= 0 && output->flag_plus && !output->flag_u &&
      !output->flag_zero)
    s[i++] = '+';
  if (origin_n_doub >= 0 && output->flag_plus && output->flag_zero)
    output->flag_positiv = 1;

  s[i] = '\0';
  for (i = 0, j = s21_strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
    if (output->flag_g && !output->flag_lattice &&
        origin_n_doub == origin_n_int && s[i] == '.') {
      if (origin_n_doub == 0) {
        s[0] = '0';
        s[1] = '\0';
      } else
        s[i] = '\0';
      break;
    }
  }

  if (output->flag_dot && origin_n_int == 0 && !itsFloat) s[i] = '\0';

  if (origin_n_doub == 0.0 && itsFloat) {
    s[i++] = '.';
    for (int k = 0; (k < output->accuracy); k++) s[i++] = '0';
    s[i] = '\0';
  }
  // printf("[%d]\n", output->accuracy);
  //  if(output->accuracy == 0 && origin_n_int == 0 && itsFloat) { // ubuntu
  //  MACOS
  //    s[0] = origin_n_int +'0';
  //    s[1] = '\0';
  //  }
}

void count_space(write_in_buf *output, char *format) {
  output->space = 0;
  double rub = 0;
  int i = 0;
  for (i = 0; format[output->format_index] <= '9' &&
              format[output->format_index] >= '0';
       i++) {
    rub += (format[output->format_index] - '0') / simple_pow(10, i);
    output->format_index++;
  }
  rub *= simple_pow(10, i - 1);
  output->space = (int)rub;
}

double simple_pow(int base, int exp) {
  long int res = base;
  if (exp == 0) return 1;
  for (int i = 1; i < exp; i++) res *= base;
  return res;
}

void add_space(write_in_buf *output, char *buf) {
  // printf("(%s)\n", buf);
  int j = 0;

  for (j = 0; j < output->space - output->str_long; j++)
    if (output->flag_zero && !output->flag_minus)
      buf[output->index_buf_mass++] = '0';
    else
      buf[output->index_buf_mass++] = ' ';
  buf[output->index_buf_mass] = '\0';
  output->res += j;
  // printf("%s\n", buf);
  // output->res += j;
}

void add_sign(write_in_buf *output, char *buf) {
  if (output->flag_negative && output->flag_zero) {
    buf[output->index_buf_mass++] = '-';
    output->res++;
    output->space--;
  }
  if (output->flag_positiv && output->flag_zero) {
    buf[output->index_buf_mass++] = '+';
    output->res++;
    output->space--;
  }
  if (output->flag_add_space && output->flag_zero) {
    buf[output->index_buf_mass++] = ' ';
    output->res++;
    output->space--;
  }
}

void scientific_notation(write_in_buf *output, char s[], long double n) {
  long int whole_num = 0, not_whole_num = -1;
  long int copy_n_int = (long int)n;
  long double copy_n_doub = n;
  long double origin_n_save = n;
  int add_notation = 0, small = 0;
  int origin_save_accuracy = output->accuracy;

  for (whole_num = 0; copy_n_int /= 10; whole_num++)
    ;
  whole_num++;
  if (origin_n_save < 1 && origin_n_save > -1 && origin_n_save != 0) {
    do {
      copy_n_doub *= 10;
      not_whole_num++;
    } while ((int)((long int)copy_n_doub % 10) == 0);
    small = 1;
    not_whole_num++;
    n = copy_n_doub;
  } else {
    do {
      copy_n_doub *= 10;
      not_whole_num++;
    } while ((int)((long int)copy_n_doub % 10) != 0 &&
             not_whole_num - 1 <= output->accuracy - whole_num);
  }

  if (whole_num > output->accuracy ||
      (origin_n_save < 1 && origin_n_save > -1) || output->flag_e ||
      output->flag_E) {
    n /= simple_pow(10, whole_num - 1);
    add_notation = 1;
    output->accuracy = output->accuracy - 1;
  } else
    output->accuracy =
        output->accuracy - whole_num /*количество чисел после запятой*/;

  if (output->flag_e || output->flag_E) {
    output->accuracy = origin_save_accuracy;
  }

  itoa(output, n, s, 1);
  output->str_long = s21_strlen(s);
  if ((add_notation == 1 && !((origin_n_save <= 9 && origin_n_save >= 1) ||
                              (origin_n_save >= -9 && origin_n_save <= -1))) ||
      (output->flag_e || output->flag_E)) {
    if (small) whole_num = not_whole_num + 1;
    if (output->flag_e || output->flag_g)
      s[output->str_long++] = 'e';
    else
      s[output->str_long++] = 'E';
    if (origin_n_save < 1 && origin_n_save > -1 && origin_n_save != 0)
      s[output->str_long++] = '-';
    else
      s[output->str_long++] = '+';
    if ((whole_num - 1) < 9) {
      s[output->str_long++] = '0';
      s[output->str_long++] = (whole_num - 1) + '0';
    } else {
      s[output->str_long++] = (whole_num - 1) / 10 + '0';
      s[output->str_long++] = (whole_num - 1) % 10 + '0';
    }
  }

  s[output->str_long++] = '\0';
}

void hexadecimal(write_in_buf *output, char s[], long int n) {
  long int remainder = 0, origin_n = n;
  int digit = 16, k = 0;
  char c;
  if (output->flag_o) digit = 8;
  s[0] = '\0';
  if (n < 0) n = (4294967295 + 1 + n);
  do {
    remainder = n % digit;
    if (remainder > 9) {
      s[k] = 'A' + remainder - 10;
      if (output->flag_x) s[k] = 'a' + remainder - 10;
    } else
      s[k] = remainder + '0';
    s[k + 1] = '\0';
    k++;
  } while (n /= digit);

  for (int i = 0; output->flag_accuracy && i < output->accuracy - k - 2; i++)
    s[k++] = '0';

  if (output->flag_lattice && origin_n != 0) {
    s[k++] = 'x';
    s[k++] = '0';
  }

  for (int i = 0, j = k - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
