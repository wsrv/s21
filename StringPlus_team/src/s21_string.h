#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#define S21_NULL ((void *)0)

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long s21_size_t;

typedef struct {
  char mas_format[100];
  int mas_format_len;
  int type;
} base_mass;

typedef struct {
  int index_buf_mass;
  int format_index;
  int str_long;
  int space;
  int flag_plus;
  int flag_minus;
  int flag_space;
  int flag_zero;
  int flag_add_space;
  int accuracy;
  int flag_h;
  int flag_l;
  int flag_L;
  int flag_g;
  int flag_e;
  int flag_E;
  int flag_x;
  int flag_o;
  int flag_u;
  int flag_lattice;
  int flag_negative;
  int flag_positiv;
  int flag_dot;
  char e_exp[256];
  int flag_accuracy;
  int accuracy_g;
  int res;

  va_list argptr;

} write_in_buf;

// macygabr
int s21_sprintf(char *buf, char *format, ...);
void itoa(write_in_buf *output, long double n, char s[], int itsFloat);
void count_space(write_in_buf *output, char *format);
double simple_pow(int base, int exp);
void add_space(write_in_buf *output, char *buf);
void add_sign(write_in_buf *output, char *buf);
void sellect_flags(char *buf, write_in_buf *output, char *format);
void sellect_width(char *buf, write_in_buf *output, char *format);
void sellect_accuracy(char *buf, write_in_buf *output, char *format);
void sellect_modifier(char *buf, write_in_buf *output, char *format);
void sellect_type(char *buf, write_in_buf *output, char *format);
void scientific_notation(write_in_buf *output, char s[], long double n);
void hexadecimal(write_in_buf *output, char s[], long int n);
void flag_d(char *buf, write_in_buf *output);
void flag_c(char *buf, write_in_buf *output);
void flag_s(char *buf, write_in_buf *output);
void flag_f(char *buf, write_in_buf *output);
void flag_u(char *buf, write_in_buf *output);
void flag_g(char *buf, write_in_buf *output);
void flag_e(char *buf, write_in_buf *output);
void flag_x(char *buf, write_in_buf *output);
void flag_p(char *buf, write_in_buf *output);

// marshaga
void *s21_memchr(const void *str, int c, s21_size_t n);

/**
 * Array comparison
 * @param str1 a pointer to the arrays to be compared
 * @param str2 a pointer to the arrays to be compared
 * @param n the size of the compared part of the array in bytes
 *
 * @return 0 - if the compared parts of the arrays are identical
 */
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

/**
 * Copies count characters from the object pointed to by src to the object
 * pointed to by dest. Both objects are interpreted as arrays of unsigned char.
 * @param dest pointer to the object to copy to
 * @param src 	pointer to the object to copy from
 * @param n number of bytes to copy
 * @return Returns a copy of dest
 * @return Returns zero on success and non-zero value on error. Also on error,
 * if dest is not a null pointer and destsz is valid, writes destsz zero bytes
 * in to the destination array.
 *
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n);

/**
 * Copies the character c (an unsigned char) to the first n characters of the
 * string pointed to, by the argument str.
 * @param str This is a pointer to the block of memory to fill.
 * @param c This is the value to be set. The value is passed as an int, but the
 * function fills the block of memory using the unsigned char conversion of this
 * value.
 * @param n This is the number of bytes to be set to the value.
 * @return This function returns a pointer to the memory area str.
 */
void *s21_memset(void *str, int c, s21_size_t n);

/**
 * The C library function appends the string pointed to by src to the end of the
 * string pointed to by dest up to n characters long.
 * @param dest This is pointer to the destination array, which should contain a
 * C string, and should be large enough to contain the concatenated resulting
 * string which includes the additional null-character.
 * @param src This is the string to be appended.
 * @param  n This is the maximum number of characters to be appended.
 * @return This function returns a pointer to the resulting string dest.
 */
char *s21_strncat(char *dest, const char *src, s21_size_t n);

/**
 * Find the first occurrence of a character in a string
 * @param str pointer to the string to be searched
 * @param c the code of the desired character
 *
 * @return Pointer to the character to search for, if found in str, NULL
 * otherwise.
 */
char *s21_strchr(const char *str, int c);

/**
 * String comparison with a limit on the number of compared characters.
 * @param str1 This is the first string to be compared.
 * @param str2 This is the second string to be compared.
 * @param n The maximum number of characters to be compared.
 * @return If Return value < 0 then it indicates str1 is less than str2.
 * @return If Return value > 0 then it indicates str2 is less than str1.
 * @return If Return value = 0 then it indicates str1 is equal to str2.
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

/**
 *  Copies up to n characters from the string pointed to, by src to dest. In a
 * case where the length of src is less than that of n, the remainder of dest
 * will be padded with null bytes.
 * @param dest This is the pointer to the destination array where the content is
 * to be copied.
 * @param src This is the string to be copied.
 * @param n The number of characters to be copied from source.
 * @return This function returns the pointer to the copied string.
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n);

/**
 * String comparison with a limit on the number of compared characters.
 * @param str1 This is the main C string to be scanned.
 * @param str2 This is the string containing a list of characters to match in
 * str1.
 * @return This function returns the number of characters in the initial segment
 * of string str1 which are not in the string str2.
 *
 */
s21_size_t s21_strcspn(const char *str1, const char *str2);

char *s21_strcat(char *dest, const char *src);

/// @brief Computes the length of the string str up to, but not including the
/// terminating null character.
/// @param str  This is the string whose length is to be found.
/// @return This function returns the length of string.
s21_size_t s21_strlen(const char *str);

/// @brief Finds the first character in the string str1 that matches any
/// character specified in str2.
/// @param str1  This is the C string to be scanned.
/// @param str2 This is the C string containing the characters to match.
/// @return This function returns a pointer to the character in str1 that
/// matches one of the characters in str2, or NULL if no such character is
/// found.
char *s21_strpbrk(const char *str1, const char *str2);

/// @brief Searches for the last occurrence of the character c (an unsigned
/// char) in the string pointed to, by the argument str.
/// @param str This is the C string.
/// @param c This is the character to be located. It is passed as its int
/// promotion, but it is internally converted back to char.
/// @return This function returns a pointer to the last occurrence of character
/// in str. If the value is not found, the function returns a null pointer.
char *s21_strrchr(const char *str, int c);

/// @brief Function finds the first occurrence of the substring needle in the
/// string haystack. The terminating '\0' characters are not compared.
/// @param haystack This is the main C string to be scanned.
/// @param needle This is the small string to be searched with-in haystack
/// string.
/// @return This function returns a pointer to the first occurrence in haystack
/// of any of the entire sequence of characters specified in needle, or a null
/// pointer if the sequence is not present in haystack.
char *s21_strstr(const char *haystack, const char *needle);

/// @brief Breaks string str into a series of tokens using the delimiter delim.
/// @param str The contents of this string are modified and broken into smaller
/// strings (tokens).
/// @param delim This is the C string containing the delimiters. These may vary
/// from one call to another.
/// @return This function returns a pointer to the first token found in the
/// string. A null pointer is returned if there are no tokens left to retrieve.
char *s21_strtok(char *str, const char *delim);

// void print_arg(va_list argptr, base_mass str);

// roddstat ^^
char *s21_strerror(int errnum);
void s21_delete(char *trim_deleted, int p);
char *s21_strcat(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
#endif