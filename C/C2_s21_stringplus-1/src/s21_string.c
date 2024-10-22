#include "s21_string.h"

// 1 Выполняет поиск первого вхождения указанного символа в массиве
void *s21_memchr(const void *str, int c, s21_size_t n) {
  int end = 1;
  char *ptr = (char *)str, *result = S21_NULL;
  for (s21_size_t i = 0; i < n && end == 1; i++) {
    int symbol;
    symbol = *(ptr + i);
    if (symbol == c) {
      end = 0;
      result = ptr + i;
    }
  }
  return result;
}
// 2 Сравнивает первые n байтов двух массивов
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  unsigned char *string1 = (unsigned char *)str1;
  unsigned char *string2 = (unsigned char *)str2;
  for (s21_size_t i = 0; i < n; i++) {
    if (*string1 == *string2) {
      string1++;
      string2++;
    } else {
      result = *string1 - *string2;
      n = 0;
    }
  }
  return result;
}
// 3 Копирует n символов из src в dest
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *d = dest;
  const char *s = src;
  while (n--) {
    *d++ = *s++;
  }
  return dest;
}
// 4 Заполнение массива указанными символами
void *s21_memset(void *str, int c, s21_size_t n) {
  char *s = str;
  while (n > 0) {
    *s++ = c;
    n--;
  }
  return str;
}
// 5 Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *begin = dest + s21_strlen(dest);
  char *end = dest + s21_strlen(dest) + n - 1;
  while (*src != '\0' && begin <= end) {
    *begin++ = *src++;
  }
  *begin = '\0';
  return dest;
}
// 6 Поиск первого вхождения символа в строку
char *s21_strchr(const char *str, int c) {
  s21_size_t i = 0;
  char *a;
  a = (char *)str;
  while (str[i] != '\0') {
    if (str[i] == c) return (a + i);
    i++;
  }
  if (c == 0) {
    return a + i;
  }
  return S21_NULL;
}
// 7 Сравнение строк с ограничением количества сравниваемых символов
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      result = (str1[i] < str2[i]) ? -1 : 1;
    }
  }
  return result;
}
// 8 Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  if (i < n) {
    dest[i] = '\0';
  }
  return dest;
}
// 9 Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int result = s21_strlen(str1);
  if (s21_strpbrk(str1, str2) != S21_NULL) {
    result = s21_strpbrk(str1, str2) - str1;
  }
  return result;
}
// 10 Выполняет поиск во внутреннем массиве номера ошибки errnum и
// возвращает указатель на строку с сообщением об ошибке.
// Нужно объявить макросы, содержащие массивы сообщений об ошибке
// для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке.
// Проверка текущей ОС осуществляется с помощью директив.
#ifdef __linux__
char *s21_strerror(int errnum) {
#define MAX_NUM_ERR 134
  static const char *Error_[MAX_NUM_ERR] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",  //
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error"};
  static char result[256];
  if (errnum < 0 || errnum >= MAX_NUM_ERR) {
    s21_sprintf(result, "Unknown error %d", errnum);
  } else
    s21_sprintf(result, "%s", Error_[errnum]);
  return result;
}
#else
char *s21_strerror(int errnum) {
#define MAX_NUM_ERR 107
  static const char *Error_[MAX_NUM_ERR] = {
      "Undefined error: 0",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "Device not configured",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource deadlock avoided",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Resource busy",
      "File exists",
      "Cross-device link",
      "Operation not supported by device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Result too large",
      "Resource temporarily unavailable",
      "Operation now in progress",
      "Operation already in progress",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol family",
      "Address already in use",
      "Can't assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Socket is already connected",
      "Socket is not connected",
      "Can't send after socket shutdown",
      "Too many references: can't splice",
      "Operation timed out",
      "Connection refused",
      "Too many levels of symbolic links",
      "File name too long",
      "Host is down",
      "No route to host",
      "Directory not empty",
      "Too many processes",
      "Too many users",
      "Disc quota exceeded",
      "Stale NFS file handle",
      "Too many levels of remote in path",
      "RPC struct is bad",
      "RPC version wrong",
      "RPC prog. not avail",
      "Program version wrong",
      "Bad procedure for program",
      "No locks available",
      "Function not implemented",
      "Inappropriate file type or format",
      "Authentication error",
      "Need authenticator",
      "Device power is off",
      "Device error",
      "Value too large to be stored in data type",
      "Bad executable (or shared library)",
      "Bad CPU type in executable",
      "Shared library version mismatch",
      "Malformed Mach-o file",
      "Operation canceled",
      "Identifier removed",
      "No message of desired type",
      "Illegal byte sequence",
      "Attribute not found",
      "Bad message",
      "EMULTIHOP (Reserved)",
      "No message available on STREAM",
      "ENOLINK (Reserved)",
      "No STREAM resources",
      "Not a STREAM",
      "Protocol error",
      "STREAM ioctl timeout",
      "Operation not supported on socket",
      "Policy not found",
      "State not recoverable",
      "Previous owner died",
      "Interface output queue is full"};
  static char result[256];
  if (errnum < 0 || errnum >= MAX_NUM_ERR) {
    s21_sprintf(result, "Unknown error: %d", errnum);
  } else
    s21_sprintf(result, "%s", Error_[errnum]);
  return result;
}
#endif

// 10 Для работы strerror
//    Добавляет строку, на которую указывает src, в конец строки, на которую
//    указывает dest
char *s21_strcat(char *dest, const char *src) {
  char *destmem = dest;
  while (*dest != 0) dest++;
  while (*src != 0) {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = *src;
  return destmem;
}

// 11 Вычисляет длину строки str, не включая завершающий нулевой символ
s21_size_t s21_strlen(const char *str) {
  int i;
  for (i = 0; str[i] != '\0'; i++)
    ;
  return i;
}
// 12 Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  char *ret = S21_NULL;
  for (; *str1 != 0 && !ret; str1++) {
    for (char *p = (char *)str2; *p != 0; p++) {
      if (*str1 == *p) {
        ret = (char *)str1;
        break;
      }
    }
  }
  return ret;
}
// 13 Поиск последнего вхождения символа в строку
char *s21_strrchr(const char *str, int c) {
  char *p_char = S21_NULL;
  for (; *str != '\0'; ++str) {
    if (*str == (char)c) {
      p_char = (char *)str;
    }
  }
  if (p_char == S21_NULL) {
    p_char = (char *)str;
  }
  return *p_char == c ? (char *)p_char : S21_NULL;
}
// 14 Находит первое вхождение всей строки needle (не включая завершающий
// нулевой символ) которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t s1 = s21_strlen(haystack);
  s21_size_t s2 = s21_strlen(needle);
  char *result = S21_NULL;
  int error = 0;
  if (s1 < s2) {
    if (haystack[0] == '\0' && needle[0] == '\0') {
      result = (char *)haystack;
    } else {
      result = S21_NULL;
    }
    error = 1;
  }
  if (needle[0] == '\0') {
    result = (char *)haystack;
    error = 1;
  }
  s21_size_t i = 0;
  while ((i <= s1 - s2) && error == 0) {
    if (s21_strncmp(haystack + i, needle, s2) == 0) {
      result = (char *)haystack + i;
      break;
    }
    ++i;
  }

  return result;
}

// 15 Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim) {
  static char *last = S21_NULL;
  if (str != S21_NULL) {
    last = str;
  }
  char *result = last;
  char *separator;
  for (; *last != '\0'; last++) {
    separator = (char *)delim;
    for (; *separator != '\0'; separator++) {
      if (*last == *separator) {
        *last = '\0';
        last++;
        if (result[0] != '\0') {
          return result;
        } else {
          result = last;
          break;
        }
      }
    }
  }
  return (result[0] == '\0') ? S21_NULL : result;
}
// Специальные функции обработки строк (вдохновленные классом String в языке C#)
//
//  1 Возвращает копию строки (str), преобразованной в верхний регистр
void *s21_to_upper(const char *str) {
  char *result;
  if (str != S21_NULL) {
    int len = 0;
    for (; str[len] != '\0'; len++)
      ;
    len += 1;
    result = (char *)malloc(len * sizeof(char));
    for (int i = 0; i < len; i++) {
      if ((str[i] > 96) && (str[i] < 123))
        result[i] = str[i] - 32;
      else
        result[i] = str[i];
    }
  } else
    result = S21_NULL;
  return result;
}
// 2 Возвращает копию строки (str), преобразованной в нижний регистр
void *s21_to_lower(const char *str) {
  char *result;
  if (str != S21_NULL) {
    int len = 0;
    for (; str[len] != '\0'; len++)
      ;
    len += 1;
    result = (char *)malloc(len * sizeof(char));
    for (int i = 0; i < len; i++) {
      if ((str[i] > 64) && (str[i] < 91))
        result[i] = str[i] + 32;
      else
        result[i] = str[i];
    }
  } else
    result = S21_NULL;
  return result;
}

// 3 Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию
//   start_index) в данной строке (src)
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *rezult;
  if (src != S21_NULL && str != S21_NULL && start_index < s21_strlen(src)) {
    rezult =
        (char *)malloc((s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char));
    s21_strncpy(rezult, src, start_index);
    s21_strncpy(rezult + start_index, str, s21_strlen(str));
    s21_strncpy(rezult + start_index + s21_strlen(str), src + start_index,
                s21_strlen(src) - start_index + 1);
  } else if (src != S21_NULL && str != S21_NULL && start_index == 0 &&
             s21_strlen(src) == 0 && s21_strlen(str) == 0) {
    rezult = malloc(sizeof(char));
    rezult[0] = '\0';
  } else
    rezult = S21_NULL;

  return (char *)rezult;
}
// 4.0 Нужно для работы s21_trim
void s21_delete(char *trim_deleted, int p) {
  int len = s21_strlen(trim_deleted);
  for (int i = 0, j = 0; i < len; j++, i++) {
    if (i == p) i++;
    trim_deleted[j] = trim_deleted[i];
  }
  trim_deleted[s21_strlen(trim_deleted) - 1] = '\0';
}
// 4 Возвращает новую строку, в которой удаляются все начальные и
//   конечные вхождения набора заданных символов (trim_chars) из данной строки
//   (src).
void *s21_trim(const char *src, const char *trim_chars) {
  char *rezult;
  if (src == S21_NULL)
    rezult = S21_NULL;
  else {
    int len = s21_strlen(src);
    int trim_len = 0;
    if (trim_chars != S21_NULL) trim_len = s21_strlen(trim_chars);
    int start = 0, end = len - 1;
    if (trim_chars == S21_NULL) {
      int start = 0, end = len - 1;
      while (src[start] == ' ' || src[start] == '\t' || src[start] == '\n' ||
             src[start] == '\r')
        start++;
      while (src[end] == ' ' || src[end] == '\t' || src[end] == '\n' ||
             src[end] == '\r')
        end--;
      rezult = (char *)malloc(sizeof(char) * (end - start + 1));
      for (int i = start, j = 0; i <= end; j++, i++) {
        rezult[j] = src[i];
        rezult[j + 1] = '\0';
      }
    } else if (len == 0) {
      rezult = malloc(sizeof(char));
      rezult[0] = '\0';
    } else if (trim_len == 0) {
      rezult = malloc(sizeof(src));
      s21_strncpy(rezult, src, len);
      rezult[len] = '\0';
    } else {
      char *trim_deleted = malloc(sizeof(trim_chars));
      s21_strncpy(trim_deleted, trim_chars, trim_len);
      for (int i = 0; i < trim_len; i++) {
        if (src[start] == trim_deleted[i]) {
          while (src[start] == trim_deleted[i]) start++;
          s21_delete(trim_deleted, i);
          i = -1;
          trim_len = trim_len - 1;
        }
      }
      trim_len = s21_strlen(trim_chars);
      s21_strncpy(trim_deleted, trim_chars, trim_len);
      for (int i = 0; i < trim_len; i++) {
        if (src[end] == trim_deleted[i]) {
          while (src[end] == trim_deleted[i]) end--;
          s21_delete(trim_deleted, i);
          i = -1;
          trim_len = trim_len - 1;
        }
      }
      if (end <= start) {
        rezult = malloc(sizeof(char));
        rezult[0] = '\0';
      } else {
        rezult = malloc(sizeof(char) * (end - start + 1));
        int res_len = end - start + 1;
        for (int j = 0, i = start; i <= end && j < res_len; j++, i++) {
          rezult[j] = src[i];
        }
      }
    }
  }
  return (char *)rezult;
}
