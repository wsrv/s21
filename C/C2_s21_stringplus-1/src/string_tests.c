#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

#include "s21_string.h"

START_TEST(test_d) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *flags[100];
  int str3[100];
  int str4[100];
  flags[0] = "N%d";
  flags[1] = "Nu% d";
  flags[2] = "Nur%-d";
  flags[3] = "Nurl%+d";
  flags[4] = "Nurla%#d";
  flags[5] = "Nurlan%0d";
  flags[6] = "Nurlan %6d";
  flags[7] = "Nurlan %.4d ";
  flags[8] = "Nurlan %hd T";
  flags[9] = "Nurlan %ld Tu";
  flags[10] = "Nurlan %.*d Tur";
  flags[11] = "Nurlan %*d Turs";

  str3[0] = 1;
  str3[1] = 123;
  str3[2] = 1234567;
  str3[3] = -1234567;
  str3[4] = 0;

  str4[0] = 12;
  str4[1] = -12;
  str4[2] = 0;
  str4[3] = 1;
  str4[4] = -1;

  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 4; j++) {
      ck_assert_int_eq(sprintf(str1, flags[i], str3[j]),
                       s21_sprintf(str2, flags[i], str3[j]));
      ck_assert_pstr_eq(str1, str2);
    }
  }
  for (int i = 10; i <= 11; i++)
    for (int j = 0; j <= 4; j++)
      for (int k = 0; k <= 4; k++) {
        ck_assert_int_eq(sprintf(str1, flags[i], str4[k], str3[j]),
                         s21_sprintf(str2, flags[i], str4[k], str3[j]));
        ck_assert_pstr_eq(str1, str2);
      }
}
END_TEST

START_TEST(test_c) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *flags[100];
  char str3[100];
  int str4[100];
  flags[0] = "N%c";
  flags[1] = "Nu% c";
  flags[2] = "Nur%-c";
  flags[3] = "Nurl%+c";
  flags[4] = "Nurla%#c";
  flags[5] = "Nurlan%0c";
  flags[6] = "Nurlan %6c";
  flags[7] = "Nurlan %.4c ";
  flags[8] = "Nurlan %hc T";
  flags[9] = "Nurlan %lc Tu";
  flags[10] = "Nurlan %.*c Tur";
  flags[11] = "Nurlan %*c Turs";

  str3[0] = 'b';
  str3[1] = 'b';
  str3[2] = 'b';
  str3[3] = 'b';
  str3[4] = 'b';

  str4[0] = 12;
  str4[1] = -12;
  str4[2] = 0;
  str4[3] = 1;
  str4[4] = -1;

  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 4; j++) {
      ck_assert_int_eq(sprintf(str1, flags[i], str3[j]),
                       s21_sprintf(str2, flags[i], str3[j]));
      ck_assert_pstr_eq(str1, str2);
    }
  }
  for (int i = 10; i <= 11; i++)
    for (int j = 0; j <= 4; j++)
      for (int k = 0; k <= 4; k++) {
        ck_assert_int_eq(sprintf(str1, flags[i], str4[k], str3[j]),
                         s21_sprintf(str2, flags[i], str4[k], str3[j]));
        ck_assert_pstr_eq(str1, str2);
      }
}
END_TEST

START_TEST(test_f) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *flags[100];
  double str3[100];
  int str4[100];
  flags[0] = "N%f";
  flags[1] = "Nu% f";
  flags[2] = "Nur%-f";
  flags[3] = "Nurl%+f";
  flags[4] = "Nurla%#f";
  flags[5] = "Nurlan%0f";
  flags[6] = "Nurlan %6f";
  flags[7] = "Nurlan %.4f ";
  flags[8] = "Nurlan %hf T";
  flags[9] = "Nurlan %lf Tu";

  flags[10] = "Nurlan %.*f Tur";
  flags[11] = "Nurlan %*f Turs";
  flags[12] = "Nurlan %Lf Turs";

  str3[0] = 1.0;
  str3[1] = 123.4567;
  str3[2] = 0.1234567;
  str3[3] = -123.4567;
  str3[4] = -0.1234567;

  str4[0] = 12;
  str4[1] = -12;
  str4[2] = 0;
  str4[3] = 1;
  str4[4] = -1;
  long double long_double = 0.1234567;

  for (int i = 0; i <= 9; i++)
    for (int j = 0; j <= 4; j++) {
      ck_assert_int_eq(sprintf(str1, flags[i], str3[j]),
                       s21_sprintf(str2, flags[i], str3[j]));
      ck_assert_pstr_eq(str1, str2);
    }

  for (int i = 10; i <= 11; i++)
    for (int j = 0; j <= 4; j++)
      for (int k = 0; k <= 4; k++) {
        ck_assert_int_eq(sprintf(str1, flags[i], str4[k], str3[j]),
                         s21_sprintf(str2, flags[i], str4[k], str3[j]));
        ck_assert_pstr_eq(str1, str2);
      }

  ck_assert_int_eq(sprintf(str1, flags[12], long_double),
                   s21_sprintf(str2, flags[12], long_double));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(test_s) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *flags[100];
  char *str3[100];
  int str4[100];
  flags[0] = "N%s";
  flags[1] = "Nu% s";
  flags[2] = "Nur%-s";
  flags[3] = "Nurl%+s";
  flags[4] = "Nurla%#s";
  flags[5] = "Nurlan%0s";
  flags[6] = "Nurlan %6s";
  flags[7] = "Nurlan %.4s ";
  flags[8] = "Nurlan %s T";
  flags[9] = "Nurlan %s Tu";

  flags[10] = "Nurlan %.*s Tur";
  flags[11] = "Nurlan %*s Turs";

  str3[0] = "be";
  str3[1] = "bes";
  str3[2] = "best";
  str3[3] = "TrEyEqO";
  str3[4] = "14356Ty";

  str4[0] = 12;
  str4[1] = -12;
  str4[2] = 0;
  str4[3] = 1;
  str4[4] = -1;

  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 2; j++) {
      ck_assert_int_eq(sprintf(str1, flags[i], str3[j]),
                       s21_sprintf(str2, flags[i], str3[j]));
      ck_assert_pstr_eq(str1, str2);
    }
  }
  for (int i = 10; i <= 10; i++)
    for (int j = 0; j <= 0; j++)
      for (int k = 0; k <= 1; k++) {
        ck_assert_int_eq(sprintf(str1, flags[i], str4[k], str3[j]),
                         s21_sprintf(str2, flags[i], str4[k], str3[j]));
        ck_assert_pstr_eq(str1, str2);
      }
}
END_TEST

START_TEST(test_u) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *flags[100];
  int str3[100];
  int str4[100];
  flags[0] = "N%u";
  flags[1] = "Nu% u";
  flags[2] = "Nur%-u";
  flags[3] = "Nurl%+u";
  flags[4] = "Nurla%#u";
  flags[5] = "Nurlan%0u";
  flags[6] = "Nurlan %6u";
  flags[7] = "Nurlan %.4u ";
  flags[8] = "Nurlan %hu T";
  flags[9] = "Nurlan %lu Tu";
  flags[10] = "Nurlan %.*u Tur";
  flags[11] = "Nurlan %*u Turs";

  str3[0] = 1;
  str3[1] = 123.4567;
  str3[2] = 1234567;
  str3[3] = -1234567;
  str3[4] = 0;

  str4[0] = 12;
  str4[1] = -12;
  str4[2] = 0;
  str4[3] = 1;
  str4[4] = -1;

  for (int i = 0; i <= 9; i++)
    for (int j = 0; j <= 4; j++) {
      ck_assert_int_eq(sprintf(str1, flags[i], str3[j]),
                       s21_sprintf(str2, flags[i], str3[j]));
      ck_assert_pstr_eq(str1, str2);
    }

  for (int i = 10; i <= 11; i++)
    for (int j = 0; j <= 4; j++)
      for (int k = 0; k <= 4; k++) {
        ck_assert_int_eq(sprintf(str1, flags[i], str4[k], str3[j]),
                         s21_sprintf(str2, flags[i], str4[k], str3[j]));
        ck_assert_pstr_eq(str1, str2);
      }
}
END_TEST

// START_TEST(test_g) {
//   char str1[1024] = "";
//   char str2[1024] = "";
//   char *flags[100];
//   double str3[100];
//   int str4[100];
//   flags[0] = "N%g";
//   flags[1] = "Nu% g";
//   flags[2] = "Nur%-g";
//   flags[3] = "Nurl%+g";
//   flags[4] = "Nurla%#g";
//   flags[5] = "Nurlan%0g";
//   flags[6] = "Nurlan %6g";
//   flags[7] = "Nurlan %.4g ";
//   flags[8] = "Nurlan %hg T";
//   flags[9] = "Nurlan %lg Tu";
//   flags[10] = "Nurlan %.*g Tur";
//   flags[11] = "Nurlan %*g Turs";

//   str3[0] = 1.123;
//   str3[1] = 123.4567;
//   str3[2] = 7654321;
//   str3[3] = -1234567;
//   // str3[4] = 0;

//   str4[0] = 12;
//   str4[1] = -12;
//   str4[2] = 0;
//   str4[3] = 1;
//   str4[4] = -1;

//   for (int i = 0; i <= 0; i++)
//     for (int j = 2; j <= 3; j++) {
//       // sprintf(str1, flags[i], str3[j]);
//       // s21_sprintf(str2, flags[i], str3[j]);
//       // printf("[%s] =[%s], %s, %f\n",str1,str2, flags[i], str3[j]);

//       // ck_assert_int_eq(sprintf(str1, flags[i], str3[j]),
//       //                  s21_sprintf(str2, flags[i], str3[j]));
//       // ck_assert_pstr_eq(str1, str2);
//     }

//   for (int i = 10; i <= 11; i++)
//     for (int j = 0; j <= 3; j++)
//       for (int k = 0; k <= 4; k++) {
//         //              sprintf(str1, flags[i], str4[k], str3[j]);
//         // s21_sprintf(str2, flags[i], str4[k], str3[j]);
//         // printf("[%s] =[%s], %s, %f, %d\n",str1,str2, flags[i], str4[k],
//         // str3[j]);

//         // ck_assert_int_eq(sprintf(str1, flags[i], str4[k], str3[j]),
//         //                  s21_sprintf(str2, flags[i], str4[k], str3[j]));
//         // ck_assert_pstr_eq(str1, str2);
//       }
// }
// END_TEST

// START_TEST(test_x) {
//   char str1[1024] = "";
//   char str2[1024] = "";
//   char *flags[100];
//   int str3[100];
//   int str4[100];
//   flags[0] = "N%x";
//   flags[1] = "Nu% x";
//   flags[2] = "Nur%-x";
//   flags[3] = "Nurl%+x";
//   flags[4] = "Nurla%#x";
//   flags[5] = "Nurlan%0x";
//   flags[6] = "Nurlan %6x";
//   flags[7] = "Nurlan %.4x ";
//   flags[8] = "Nurlan %hx T";
//   flags[9] = "Nurlan %lx Tu";
//   flags[10] = "Nurlan %.*x Tur";
//   flags[11] = "Nurlan %*x Turs";

//   str3[0] = 633546;
//   str3[1] = 123;
//   str3[2] = 7654321;
//   str3[3] = -1234567;
//   str3[4] = 0;

//   str4[0] = 12;
//   str4[1] = -12;
//   str4[2] = 0;
//   str4[3] = 1;
//   str4[4] = -1;

//   for (int i = 0; i <= 9; i++)
//     for (int j = 0; j <= 4; j++) {
//     ck_assert_int_eq(sprintf(str1, flags[i], str3[j]),
//                        s21_sprintf(str2, flags[i], str3[j]));
//       ck_assert_pstr_eq(str1, str2);
//     }

//   for (int i = 10; i <= 11; i++)
//     for (int j = 0; j <= 3; j++)
//       for (int k = 0; k <= 4; k++) {
//         ck_assert_int_eq(sprintf(str1, flags[i], str4[k], str3[j]),
//                          s21_sprintf(str2, flags[i], str4[k], str3[j]));
//         ck_assert_pstr_eq(str1, str2);
//       }
// }
// END_TEST

START_TEST(test_e) {
  char str1[1024] = "";
  char str2[1024] = "";
  char *flags[100];
  double str3[100];
  int str4[100];
  flags[0] = "N%e";
  flags[1] = "N%E";
  flags[2] = "Nu% e";
  flags[3] = "Nur%-e";
  flags[4] = "Nurl%+e";
  flags[5] = "Nurla%#e";
  flags[6] = "Nurlan%0e";
  flags[7] = "Nurlan %6e";
  flags[8] = "Nurlan %.4e ";
  flags[9] = "Nurlan %he T";
  flags[10] = "Nurlan %le Tu";
  flags[11] = "Nurlan %.*e Tur";
  flags[12] = "Nurlan %*e Turs";

  str3[0] = 1.123;
  str3[1] = 123.4567;
  str3[2] = 7654321;
  str3[3] = -1234567;
  str3[4] = 0.0;

  str4[0] = 12;
  str4[1] = -12;
  str4[2] = 0;
  str4[3] = 1;
  str4[4] = -1;

  for (int i = 0; i <= 10; i++)
    for (int j = 0; j <= 3; j++) {
      // sprintf(str1, flags[i], str3[j]);
      // s21_sprintf(str2, flags[i], str3[j]);
      // printf("[%s] =[%s], %s, %f\n",str1,str2, flags[i], str3[j]);
      ck_assert_int_eq(sprintf(str1, flags[i], str3[j]),
                       s21_sprintf(str2, flags[i], str3[j]));
      ck_assert_pstr_eq(str1, str2);
    }

  for (int i = 11; i <= 12; i++)
    for (int j = 0; j <= 0; j++)
      for (int k = 0; k <= 0; k++) {
        //  sprintf(str1, flags[i], str4[k], str3[j]);
        // s21_sprintf(str2, flags[i], str4[k], str3[j]);
        // printf("[%s] =[%s], %s, %f\n",str1,str2, flags[i], str3[j]);
        ck_assert_int_eq(sprintf(str1, flags[i], str4[k], str3[j]),
                         s21_sprintf(str2, flags[i], str4[k], str3[j]));
        ck_assert_pstr_eq(str1, str2);
      }
}
END_TEST

START_TEST(sprintf_1_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 9;
  int b = 10;
  int c = 17;
  int d = 66;
  int e = 124;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = -6;
  int b = -10;
  int c = -17;
  int d = -66;
  int e = -124;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 60;
  int b = 50;
  int c = 1744;
  int d = 386;
  int e = 257;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  int a = 60;
  int b = 50;
  int c = 1744;
  int d = 386;
  int e = 257;
  ck_assert_int_eq(sprintf(str1, str3, a, b, c, d, e),
                   s21_sprintf(str2, str3, a, b, c, d, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  char a = 0;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                   s21_sprintf(str2, str3, a, a, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// START_TEST(sprintf_6_c) {
//   char str1[100];
//   char str2[100];
//   char *str3 = "%05c Test % 5c Test %lc Test";
//   int a = 70;
//   unsigned long int b = 70;
//   // sprintf(str1, str3, a, a, b);
//   //                  s21_sprintf(str2, str3, a, a, b);
//   //         printf("[%s] == [%s]\n", str1, str2);
//   ck_assert_int_eq(sprintf(str1, str3, a, a, b),
//                    s21_sprintf(str2, str3, a, a, b));
//   ck_assert_pstr_eq(str1, str2);
// }
// END_TEST

START_TEST(sprintf_7_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%-010c Test % -10c Test %-lc";
  int a = 74;
  unsigned long int b = 74;
  ck_assert_int_eq(sprintf(str1, str3, a, a, b),
                   s21_sprintf(str2, str3, a, a, b));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// START_TEST(sprintf_8_c) {
//   char str1[100];
//   char str2[100];
//   char *str3 = "%+010.5c Test % +10.5c Test %-10lc Test %-10lc Test %+10lc";
//   char a = 92;
//   unsigned long int b = 92;
//   unsigned long int c = 92;
//   ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
//                    s21_sprintf(str2, str3, a, a, b, c, c));
//   ck_assert_pstr_eq(str1, str2);
// }
// END_TEST

START_TEST(sprintf_9_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%6.4c Test %-6.4c Test %4.10lc Test %-4.10lc Test %-0lc";
  int a = 10;
  unsigned long int b = 10;
  unsigned long int c = 10;
  ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                   s21_sprintf(str2, str3, a, a, b, c, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_10_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%6.4c Test %-6.4c Test %4.10lc Test %-4.10lc Test %-0lc";
  int a = -10;
  unsigned long int b = 10;
  unsigned long int c = 10;

  sprintf(str1, str3, a, a, b, c, c);
  // s21_sprintf(str2, str3, a, a, b, c, c);
  // printf("%s\n%s\n\n", str1,str2);

  ck_assert_int_eq(sprintf(str1, str3, a, a, b, c, c),
                   s21_sprintf(str2, str3, a, a, b, c, c));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%#c Test %#c Test %#c Test %#c Test %#c";
  ck_assert_int_eq(sprintf(str1, str3, ' ', 'n', '5', '%', '\\'),
                   s21_sprintf(str2, str3, ' ', 'n', '5', '%', '\\'));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  ck_assert_int_eq(sprintf(str1, str3, '\n', '\0', '\0', '\0', 'c'),
                   s21_sprintf(str2, str3, '\n', '\0', '\0', '\0', 'c'));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_13_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  ck_assert_int_eq(sprintf(str1, str3, 'b', '4', '#', '@', '\0'),
                   s21_sprintf(str2, str3, 'b', '4', '#', '@', '\0'));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_c) {
  char str1[100];
  char str2[100];
  char *str3 = "%c Test %c Test %c Test %c Test %c";
  ck_assert_int_eq(sprintf(str1, str3, 'Y', 'G', 123, '\0', 'J'),
                   s21_sprintf(str2, str3, 'Y', 'G', 123, '\0', 'J'));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// START_TEST(sprintf_15_c) {
//   char str1[400];
//   char str2[400];
//   char *str3 = "%.7c Test %-7c Test %-50c Test % 54c Test %0188c";
//   int a = 112;
//   ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
//                    s21_sprintf(str2, str3, a, a, a, a, a));
//   ck_assert_pstr_eq(str1, str2);
// }
// END_TEST

START_TEST(sprintf_16_c) {
  char str1[400];
  char str2[400];
  char *str3 = "%.7c Test % -.7c Test %- 050c Test %- 54c Test %-0188c";
  int a = 45;
  ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
                   s21_sprintf(str2, str3, a, a, a, a, a));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// START_TEST(sprintf_17_c) {
//   char str1[400];
//   char str2[400];
//   char *str3 = "%70c Test %-90c Test %080c Test %-065c Test %- 60c";
//   int a = 255;
//   ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
//                    s21_sprintf(str2, str3, a, a, a, a, a));
//   ck_assert_pstr_eq(str1, str2);
// }
// END_TEST

// START_TEST(sprintf_18_c) {
//   char str1[400];
//   char str2[400];
//   char *str3 = "%70c Test %-90c Test %080c Test %-065c Test %- 60c";
//   int a = 255;
//   ck_assert_int_eq(sprintf(str1, str3, a, a, a, a, a),
//                    s21_sprintf(str2, str3, a, a, a, a, a));
//   ck_assert_pstr_eq(str1, str2);
// }
// END_TEST

START_TEST(sprintf_19_c) {
  char str1[100];
  char str2[100];  //%lc Test %llc Test %hc Test %hhc
  char *str3 = "%c Test %lc Test %hc";
  int a = 3;
  unsigned long int b = 103;
  unsigned short e = 255;
  ck_assert_int_eq(sprintf(str1, str3, a, b, e),
                   s21_sprintf(str2, str3, a, b, e));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_signed) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %d Test";
  int val = -12;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three signed parameters
START_TEST(sprintf_2_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%d Test %d Test %d";
  int val = 012;
  int val2 = -017;
  int val3 = 07464;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Three decimal parameters
START_TEST(sprintf_3_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%d Test %d Test %d";
  int val = 3015;
  int val2 = 712;
  int val3 = 99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different sizes
START_TEST(sprintf_4_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%ld Test %ld Test %hd GOD %hd";
  long int val = 3088675747373646;
  long val2 = 33030030303;
  short int val3 = 22600;
  short val4 = -120;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different width
START_TEST(sprintf_5_signed) {
  char str1[100];
  char str2[100];
  char *str3 = "%3d Test %5d Test %10d";
  int val = -3015;
  int val2 = -11234;
  int val3 = -99;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3),
                   s21_sprintf(str2, str3, val, val2, val3));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Different precision and width
START_TEST(sprintf_6_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%6.5d Test %.23d Test %3.d TEST %.d %.6d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -38;
  int val5 = -100;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Minus flag
START_TEST(sprintf_7_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%-10.5d Test %-.8d Test %-7d TEST %-.d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zeroes
START_TEST(sprintf_8_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%0d Test %0.d Test %0.0d TEST %0d GOD %.d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -2939;
  int val5 = -0123;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Pluses
START_TEST(sprintf_9_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%+d Test %+3.d Test %+5.7d TEST %+10d";
  int val = -3015;
  int val2 = -712;
  int val3 = -99;
  int val4 = -2939;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Zero vals
START_TEST(sprintf_10_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "(%d) Test (%3.d) Test (%5.7d) TEST %10d %#d %-d %+d %.d % .d";
  int val = 0;

  //  sprintf(str1, str3, val, val, val, val, val, val, val, val, val);
  //       s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val,
  //                   val);
  //   printf("[%s]\n[%s]\n\n", str1, str2);

  ck_assert_int_eq(
      sprintf(str1, str3, val, val, val, val, val, val, val, val, val),
      s21_sprintf(str2, str3, val, val, val, val, val, val, val, val, val,
                  val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Spaces
START_TEST(sprintf_11_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "% d Test % 3.d Test % 5.7d TEST % 10d GOD %.d";
  int val = -32;
  int val2 = -8899;
  int val3 = -91918;
  int val4 = -32311;
  int val5 = -23;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Plus
START_TEST(sprintf_12_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%+d Test %+3.d Test %+5.7d TEST %+10d GOD %+.d";
  int val = -32;
  int val2 = -8899;
  int val3 = 91918;
  int val4 = -32311;
  int val5 = 3261;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Hash
START_TEST(sprintf_13_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%#d Test %#3d Test %#5.7d TEST %#.7d Oof %#.d";
  int val = -32;
  int val2 = 8899;
  int val3 = -91918;
  int val4 = 32311;
  int val5 = -8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// ZERO flag
START_TEST(sprintf_14_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%0d Test %06d Test %05.7d TEST %0.7d Oof %0.d";
  int val = -32;
  int val2 = 8899;
  int val3 = -91918;
  int val4 = -32311;
  int val5 = -8894;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Asterisk
START_TEST(sprintf_15_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%*d Test %-*d Test %*.*d TEST %.*d";
  int val = 32;
  int val2 = 8899;
  int val3 = -919;
  int val4 = 32311;
  int ast = 2;
  int ast2 = 5;
  int ast3 = 4;
  int ast4 = 10;
  int ast5 = 7;
  ck_assert_int_eq(
      sprintf(str1, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5, val4),
      s21_sprintf(str2, str3, ast, val, ast2, val2, ast3, ast4, val3, ast5,
                  val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// Simple extra test
START_TEST(sprintf_16_signed) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "%d";
  int val = 12;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST
START_TEST(sprintf_17_signed) {
  char str1[1024] = "";
  char str2[1024] = "";
  int val = -75;
  sprintf(str1, "Hello %d %023d", val, val);  // нет нулей перед числом(бонус)
  s21_sprintf(str2, "Hello %d %023d", val, val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_18_signed) {
  char str1[300];
  char str2[300];
  char *str3 = "%ld Test %ld Test %hd GOD %hd tt %d tt %d";
  long int val = LONG_MAX;
  long val2 = LONG_MIN;
  short int val3 = SHRT_MAX;
  short val4 = SHRT_MIN;
  int val5 = INT_MAX;
  int val6 = INT_MIN;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4, val5, val6),
                   s21_sprintf(str2, str3, val, val2, val3, val4, val5, val6));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_19_signed) {
  char str1[200];
  char str2[200];
  char *str3 = "%- d Test %- 15d sdasda %- 15d sdsad %- d";
  int val = -3231;
  int val2 = -3231;
  int val3 = 3231;
  int val4 = 3231;
  ck_assert_int_eq(sprintf(str1, str3, val, val2, val3, val4),
                   s21_sprintf(str2, str3, val, val2, val3, val4));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_f) {
  char str1[200];
  char str2[200];
  char *str3 = "%f TEST %.f TEST %4f TEST %4.f TEST %5.10f!";
  double num = 76.756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_f) {
  char str1[200];
  char str2[200];
  char *str3 = "%f TEST %.f TEST %3f TEST %4.f TEST %5.10f!";
  double num = -76.756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_f) {
  char str1[400];
  char str2[400];
  char *str3 = "%Lf\n%.Lf!";
  long double num_long = -76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num_long, num_long),
                   s21_sprintf(str2, str3, num_long, num_long));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_f) {
  char str1[400];
  char str2[400];
  char *str3 = "%20.10f\n%20.15f\n%-20.5f!";
  double num = -76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_f) {
  char str1[400];
  char str2[400];
  char *str3 = "1)%Lf 2)%.Lf 3)%+-#Lf 4)%+#.Lf 5)%-#.Lf!";
  long double num = 76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %5f\ntest: %6.1f\ntest: %8.2f!";
  double num = 76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %10.5f\ntest: %12.4f!";
  double num = 76.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15.1f\ntest: %16.2f\ntest: %18.3f!";
  double num = -7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %10.4f\ntest: %25.5f!";
  double num = -7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_10_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+15.f\ntest: %+#16.f\ntest: %+#18.0f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 18.0f\ntest: %+10.f\ntest: %+25.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-26.1f\ntest: %-18.0f\ntest: %#-10.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_13_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-#15.f\ntest: %-+25.f!";
  double num = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_14_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-15.4f!\ntest: %-26.1f!\ntest: %-18.0f!";
  double num = -365289.3462865487;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_15_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %#-10.9f! test: %-+25.12f!";
  double num = -365289.3462865487;

  //   sprintf(str1, str3, num, num);
  // s21_sprintf(str2, str3, num, num);
  //  printf("[%s]\n[%s]\n",str1, str2);
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_16_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15.12f!\ntest: %26.12f!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_17_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %18.7f!\ntest: %10.12f!\ntest: %25.12f!";
  double num = -365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_18_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15.11f!\ntest: %26.12f!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_19_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %18.7f!\ntest: %10.12f!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_20_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %- 23.10f!\ntest: %+ 25.12f!";
  double num = 365289.34628654873789362746834;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_21_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 15f!\ntest: % -26f!\ntest: %- 18f!";
  double num = -365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_22_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+- 14f!\ntest: %+ 10f!\ntest: % +25f!";
  double num = -365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_23_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 14f!\ntest: % -27f!\ntest: %- 19f!";
  double num = 365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_24_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+- 16f!\ntest: %+ 44f!\ntest: % +35f!";
  double num = 365789.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_25_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %26Lf! test: %18Lf! test: %60Lf!";
  long double num = -37527658396.34;
  // sprintf(str1, str3, num, num, num);
  //                  s21_sprintf(str2, str3, num, num, num);
  //     printf("[%s]\n[%s]\n\n", str1, str2);
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_26_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %15Lf!test: %100Lf!";
  long double num = -37527658396.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_27_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %- 26Lf!\ntest: %+- 18Lf!\ntest: %60Lf!";
  long double num = 37527658396.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_28_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % +15Lf!test: %100Lf!";
  long double num = 37527658396.34;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_30_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %020f! test: %-020f! test: %+025f!";
  double num = 837564.4753366;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_31_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-+ 025.5f! test: %- 020.4f test: %+ 016.6f!";
  double num = 837564.47533;
  //   sprintf(str1, str3, num, num, num);
  //              s21_sprintf(str2, str3, num, num, num);
  // printf("[%s]\n[%s]\n\n", str1, str2);
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_32_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %015f!\ntest: %-026f!\ntest: %+018f!";
  double num = -947.6785643;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_33_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+- 010.2f!\ntest: %- 025.7f\ntest: %+- 18.4f!";
  double num = -947.6785643;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_34_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 15.1Lf!\ntest: % -26.15Lf!\ntest: %- 30.15Lf!";
  long double num = 278.723786;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_35_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 50.15Lf!\ntest: % +40.15Lf!";
  long double num = 278.723786;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_36_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: % 15.1Lf!\ntest: % -26.13Lf!\ntest: %- 30.8Lf!";
  long double num = -2358.367776967;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_37_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %+ 50.14Lf!\ntest: % +40.14Lf!";
  long double num = -2358.367776967;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_38_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.1Lf!\ntest: %.2Lf!\ntest: %.3Lf!";
  long double num = -9999.99999;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_39_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.10Lf!\ntest: %.6Lf!\ntest: %.Lf!";
  long double num = -9999.99999;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_40_f) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %.1Lf! test: %.2Lf! test: %.3Lf!";
  long double num = 000000000000000.00000000000;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.1g TEST %4g TEST %4.g TEST %6.10g!";
  double num = 76.756589367;
  // sprintf(str1, str3, num, num, num);
  // s21_sprintf(str2, str3, num, num, num);
  // printf("[%s]\n[%s]\n\n", str1, str2);
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_2_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%G TEST %.g TEST %4g TEST %4.g TEST %5.10g!";
  double num = -76.756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_3_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%25.18g TEST\n%.6g TEST\n";
  double num = 838.65400000;
  double num1 = 640.783289182;
  ck_assert_int_eq(sprintf(str1, str3, num, num1),
                   s21_sprintf(str2, str3, num, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_4_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%.2g TEST\n%.3g TEST\n";
  double num = 838.65400000;
  double num1 = 640.783289182;
  ck_assert_int_eq(sprintf(str1, str3, num, num1),
                   s21_sprintf(str2, str3, num, num1));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_5_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %#5.10g!";
  double num = 0.0000756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_6_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %#5.10g!";
  double num = -0.0000756589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_7_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.g TEST %4g TEST %4.g TEST %5.10g!";
  double num = 573429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_8_g) {
  char str1[200];
  char str2[200];
  char *str3 = "%g TEST %.0g TEST %4.2g TEST %4.g TEST %5.10g!";
  double num = -57251397732103429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num, num, num),
                   s21_sprintf(str2, str3, num, num, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_9_g) {
  char str1[200];
  char str2[200];
  char *str3 = "test: %15.1g\ntest: %16.2g\ntest: %18.3g!";
  double num = -57251397732103429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_10_g) {
  char str1[200];
  char str2[200];
  char *str3 = "test: %10.4g\ntest: %25.5g!";
  double num = -57251397732103429.56589367;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_11_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %-#15.g test: %-26.1g test: %-18.0g!";
  double num = -7648938790.756589;

  //   sprintf(str1, str3, num, num, num);
  // s21_sprintf(str2, str3, num, num, num);
  // printf("[%s]\n[%s]\n\n", str1, str2);
  ck_assert_int_eq(sprintf(str1, str3, num, num, num),
                   s21_sprintf(str2, str3, num, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_12_g) {
  char str1[400];
  char str2[400];
  char *str3 = "test: %#-10.g\ntest: %-+25.g!";
  double num = -7648938790.756589;
  ck_assert_int_eq(sprintf(str1, str3, num, num),
                   s21_sprintf(str2, str3, num, num));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_hex) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %x Test";
  int val = 0x32;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_HEX) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %X Test";
  int val = 0X32;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_signed_i) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %d Test";
  int val = -12;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_octal) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "Test %o Test";
  int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_1_percent) {
  char str1[100] = "";
  char str2[100] = "";
  char *str3 = "%%Test %o Test";
  int val = 012;
  ck_assert_int_eq(sprintf(str1, str3, val), s21_sprintf(str2, str3, val));
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

// roddstat________________________________________________________________

START_TEST(toUp_1) {
  char str1[] = "abcDEFGHIJklmnopqrstuvwxyz";
  char *str2 = malloc(sizeof(str1));
  str2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *res = s21_to_upper(str1);
  ck_assert_pstr_eq(res, str2);
  free(res);
}
END_TEST

START_TEST(toUp_2) {
  char str1[] = "\t123(&@#)";
  char *str2 = malloc(sizeof(str1));
  str2 = "\t123(&@#)";
  char *res = s21_to_upper(str1);
  ck_assert_pstr_eq(res, str2);
  free(res);
}
END_TEST

START_TEST(toUp_3) {
  char *str1 = NULL;
  char *str2 = NULL;
  char *res = s21_to_upper(str1);
  ck_assert_pstr_eq(res, str2);
}
END_TEST
//-------------------------------------

START_TEST(toLow_1) {
  char str1[] = "abcDEFGHIJklmnopqrstuvwxyz";
  char *str2 = malloc(sizeof(str1));
  str2 = "abcdefghijklmnopqrstuvwxyz";
  char *res = s21_to_lower(str1);
  ck_assert_pstr_eq(res, str2);
  free(res);
}
END_TEST

START_TEST(toLow_2) {
  char str1[] = "\t123(&@#)";
  char *str2 = malloc(sizeof(str1));
  str2 = "\t123(&@#)";
  char *res = s21_to_lower(str1);
  ck_assert_pstr_eq(res, str2);
  free(res);
}
END_TEST

START_TEST(toLow_3) {
  char *str1 = NULL;
  char *str2 = NULL;
  char *res = s21_to_lower(str1);
  ck_assert_pstr_eq(res, str2);
}
END_TEST
//-------------------------------------

START_TEST(trim_1) {
  char s1[30] = "";
  char s3[] = "";
  char *s4 = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(trim_2) {
  char *s1 = S21_NULL;
  char s3[] = "";
  char *s4 = S21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(trim_3) {
  char s1[30] = "s21_Hello, world!";
  char s3[] = "s21_Hello, world!";
  char s4[] = "";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(trim_4) {
  char *s1 = S21_NULL;
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(trim_5) {
  char s1[] = " s21_Hello, world! ";
  char *s3 = S21_NULL;
  char *s4 = "s21_Hello, world!";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(trim_6) {
  char s1[] = " s21_Hello, world! ";
  char *s3 = "";
  char *s4 = " s21_Hello, world! ";
  char *s2 = s21_trim(s1, s3);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST
//-------------------------------------
START_TEST(insert_1) {
  char s1[50] = "s21_Hello, world!";
  char s3[] = "s21_test.";
  char s4[] = "s21_Hello, s21_test.world!";
  s21_size_t num = 11;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(insert_2) {
  char s1[50] = "";
  char s3[] = "";
  char *s4 = S21_NULL;
  s21_size_t num = 5;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(insert_3) {
  char *s1 = "";
  char s3[] = "";
  char *s4 = S21_NULL;
  s21_size_t num = 1;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(insert_4) {
  char s1[50] = "";
  char s3[] = "";
  char s4[] = "";
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(insert_5) {
  char s1[50] = "s21_Hello, world!";
  char s3[] = "s21_test.";
  char s4[] = "s21_test.s21_Hello, world!";
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(insert_6) {
  char s1[50] = "s21_Hello, world!";
  char s3[] = "s21_test.";
  char *s4 = S21_NULL;
  s21_size_t num = -1;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(insert_7) {
  char *s1 = S21_NULL;
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(insert_8) {
  char s1[] = "s21_Hello, world!";
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s4, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(insert_9) {
  char s1[] = "";
  char *s3 = S21_NULL;
  char *s4 = S21_NULL;
  s21_size_t num = 0;
  char *s2 = s21_insert(s1, s3, num);
  ck_assert_pstr_eq(s2, s4);
  if (s2) free(s2);
}
END_TEST

// marshaga
// utherydg________________________________________________________________

// 1
START_TEST(tests_memchr) {
  static char str1[28] = "Lorem ipsum dolor sit amet.";
  static char str2[6] = "12345";
  int sym1 = 115;
  int sym2 = 120;
  int sym3 = 'd';
  int sym5 = ' ';
  int sym6 = '4';
  int sym7 = '9';
  s21_size_t len1 = strlen(str1);
  s21_size_t len2 = strlen(str2);
  s21_size_t len5 = 5;
  ck_assert_ptr_eq(
      memchr(str1, sym1, len1),
      s21_memchr(str1, sym1, len1));  // поиск символа в полной строке
  ck_assert_ptr_eq(memchr(str2, sym6, len2), s21_memchr(str2, sym6, len2));
  ck_assert_ptr_eq(
      memchr(str1, sym2, len1),
      s21_memchr(str1, sym2, len1));  // поиск несуществующего символа в строке
  ck_assert_ptr_eq(memchr(str2, sym7, len2), s21_memchr(str2, sym7, len2));
  ck_assert_ptr_eq(
      memchr(str1, sym1, len5),
      s21_memchr(str1, sym1, len5));  // поиск существующего символ, но он
                                      // находится за пределами сравнения
  ck_assert_ptr_eq(
      memchr(str1, sym3, len1),
      s21_memchr(str1, sym3, len1));  // поиск char символа, входящего в строку
  ck_assert_ptr_eq(memchr(str2, sym3, len2), s21_memchr(str2, sym3, len2));
  ck_assert_ptr_eq(
      memchr(str1, sym3, len1),
      s21_memchr(str1, sym3, len1));  // проверка на символ, который несколько
                                      // раз встречается в строке
  ck_assert_ptr_eq(
      memchr(str1, sym5, len1),
      s21_memchr(str1, sym5, len1));  // проверка на символ "пробел"
}
END_TEST
// 2
int reduction(char *arr1, char *arr2, int length) {
  int res1 = memcmp(arr1, arr2, length);
  res1 = res1 > 0 ? 1 : res1 == 0 ? 0 : -1;
  return res1;
}
START_TEST(tests_memcmp) {
  s21_size_t len0 = 0;
  s21_size_t len1 = 1;
  s21_size_t len2 = 2;
  s21_size_t len6 = 6;
  s21_size_t len11 = 11;
  s21_size_t len13 = 13;
  s21_size_t len53 = 53;
  // Сравнение массива из символов
  char arr1[] = "Hola, amigo!";
  char arr2[] = "Hola, amigo!";
  ck_assert_int_eq(reduction(arr1, arr2, len13), s21_memcmp(arr1, arr2, len13));
  ck_assert_int_eq(reduction(arr1, arr2, len6), s21_memcmp(arr1, arr2, len6));
  ck_assert_int_eq(reduction(arr1, arr2, len0), s21_memcmp(arr1, arr2, len0));
  // Сравнение массива из чисел
  char arr3[] = "4815162342";
  char arr4[] = "4815162342";
  ck_assert_int_eq(reduction(arr3, arr4, len11), s21_memcmp(arr3, arr4, len11));
  ck_assert_int_eq(reduction(arr3, arr4, len6), s21_memcmp(arr3, arr4, len6));
  ck_assert_int_eq(reduction(arr3, arr4, len0), s21_memcmp(arr3, arr4, len0));
  // Сравнение массива из фразы
  char arr5[] = "The sign of the result is the sign of the difference";
  char arr6[] = "The sign of the result is the sign of the difference";
  ck_assert_int_eq(reduction(arr5, arr6, len53), s21_memcmp(arr5, arr6, len53));
  ck_assert_int_eq(reduction(arr5, arr6, len13), s21_memcmp(arr5, arr6, len13));
  ck_assert_int_eq(reduction(arr5, arr6, len0), s21_memcmp(arr5, arr6, len0));
  // Сравнение пустой строки с пробелом
  char arr7[] = " ";
  char arr8[] = " ";
  ck_assert_int_eq(reduction(arr7, arr8, len2), s21_memcmp(arr7, arr8, len2));
  // Сравнение пустой строки
  char arr9[] = "";
  char arr10[] = "";
  ck_assert_int_eq(reduction(arr9, arr10, len1), s21_memcmp(arr9, arr10, len1));
}
END_TEST
// 3
START_TEST(tests_memcpy) {
  char src1[] = "hard";
  // char src4[] = "hard";
  s21_size_t len0 = 0;
  s21_size_t len1 = 1;
  // s21_size_t len2 = 2;
  s21_size_t len4 = 4;
  s21_size_t len10 = 10;
  // выше записы часто использующие переменные
  char dest1[] = "No pain, no gain!";
  char dest11[] = "No pain, no gain!";
  ck_assert_str_eq(memcpy(dest1, src1, len4), s21_memcpy(dest11, src1, len4));
  // копирование полного слова в непустой массив
  char dest2[] = "No pain, no gain!";
  char dest22[] = "No pain, no gain!";
  ck_assert_str_eq(memcpy(dest2, src1, len0), s21_memcpy(dest22, src1, len0));
  // копирование 0 символов
  char src3[] = "\0";
  char dest3[] = "No pain, no gain!";
  char dest33[] = "No pain, no gain!";
  ck_assert_str_eq(memcpy(dest3, src3, len1), s21_memcpy(dest33, src3, len1));
  // копирование символа конца строки.
  char dest4[] = "No pain, no gain!";
  char dest44[] = "No pain, no gain!";
  ck_assert_str_eq(memcpy(dest4, src1, len10), s21_memcpy(dest44, src1, len10));
  // копирование большего числа битов чем в копируемой строке
  char src5[] = "";
  char dest5[] = "No pain, no gain!";
  char dest55[] = "No pain, no gain!";
  ck_assert_str_eq(memcpy(dest5, src5, len10), s21_memcpy(dest55, src5, len10));
  // копирование пустой строки
  char dest6[10] = "";
  char dest66[10] = "";
  // копирование в пустую строку полную строку
  ck_assert_str_eq(memcpy(dest6, src1, len4), s21_memcpy(dest66, src1, len4));
  char dest7[10] = "";
  char dest77[10] = "";
  ck_assert_str_eq(memcpy(dest7, src1, len1), s21_memcpy(dest77, src1, len1));
  // копирование в пустую строку неполную строку
}
END_TEST
// 4
START_TEST(tests_memset) {
  s21_size_t len0 = 0;
  s21_size_t len5 = 5;
  int add_end = '\0';
  // int add_digit = 80;
  int add_space = ' ';
  char string1[5] = "";
  char string2[5] = "";
  ck_assert_str_eq(memset(string1, add_end, len0),
                   s21_memset(string2, add_end, len0));
  // char string11[5] = "Hello";
  // char string22[5] = "Hello";
  // ck_assert_str_eq(memset(string11, add_digit, len5), s21_memset(string22,
  // add_digit, len5));
  char string3[] = "Danke schon";
  char string4[] = "Danke schon";
  ck_assert_str_eq(memset(string3, add_end, len5),
                   s21_memset(string4, add_end, len5));
  char string5[] = "123456789";
  char string6[] = "123456789";
  // s21_size_t length = strlen(string5);
  ck_assert_str_eq(memset(string5, add_space, len5),
                   s21_memset(string6, add_space, len5));
  char string7[] = "First things first";
  char string8[] = "First things first";
  ck_assert_str_eq(memset(string7, add_space, len0),
                   s21_memset(string8, add_space, len0));
  char string9[] = "Oh my God!";
  char string10[] = "Oh my God!";
  ck_assert_str_eq(memset(string9, add_space, len5),
                   s21_memset(string10, add_space, len5));
}
END_TEST
// 5
START_TEST(tests_strncat) {
  char src1[] = "";
  // char src2[] = " ";
  char src3[] = "\0";
  char src4[] = "world";
  char src5[] = "a";
  int len0 = 0;
  int len1 = 1;
  int len2 = 2;
  int len5 = 5;
  int len10 = 10;
  // часто используемые переменные
  char str1[20] = "Hello";
  char str11[20] = "Hello";
  ck_assert_pstr_eq(strncat(str1, src4, len5), s21_strncat(str11, src4, len5));
  // добавить слово целиком
  char str2[20] = "Hello";
  char str22[20] = "Hello";
  ck_assert_pstr_eq(strncat(str2, src4, len2), s21_strncat(str22, src4, len2));
  // добавить слово НЕ целиком
  char str3[20] = "Hell";
  // char str33[20] = "Hell";
  ck_assert_pstr_eq(strncat(str3, src4, len10), s21_strncat(str3, src4, len10));
  // добавить строку больше исходной
  char str4[20] = "Hell";
  // char str44[20] = "Hell";
  ck_assert_pstr_eq(strncat(str4, src5, len1), s21_strncat(str4, src5, len1));
  // добавить символ
  char str5[20] = "Hi";
  char str55[20] = "Hi";
  ck_assert_pstr_eq(strncat(str5, src1, len1), s21_strncat(str55, src1, len1));
  // добавить пустую строку
  char str6[20] = "";
  char str66[20] = "";
  ck_assert_pstr_eq(strncat(str6, src4, len5), s21_strncat(str66, src4, len5));
  // добавить строку в пустую строку целиком
  char str7[20] = "";
  char str77[20] = "";
  ck_assert_pstr_eq(strncat(str7, src4, len1), s21_strncat(str77, src4, len1));
  // добавить строку в пустую строку НЕ целиком
  char str8[20] = "Hello";
  char str88[20] = "Hello";
  ck_assert_pstr_eq(strncat(str8, src4, len0), s21_strncat(str88, src4, len0));
  // добавить 0 символов
  char str9[20] = "Hello";
  char str99[20] = "Hello";
  ck_assert_pstr_eq(strncat(str9, src3, len2), s21_strncat(str99, src3, len2));
  // добавить символ конца строки "\0"
}
END_TEST
// 6
START_TEST(tests_strchr) {
  int not_exist = 'A';
  int exist = 'K';
  int twice = 'e';
  int end = '\0';
  int digit = 42;
  int maybe_digit = '7';
  int sym = '!';
  char s1[] = "Keep calm and code on!";
  // Несуществующий символ
  ck_assert_pstr_eq(strchr(s1, not_exist), s21_strchr(s1, not_exist));
  // Существующий символ
  ck_assert_pstr_eq(strchr(s1, exist), s21_strchr(s1, exist));
  // Существующий символ, который встречается несколько раз
  ck_assert_pstr_eq(strchr(s1, twice), s21_strchr(s1, twice));
  // Конец строки
  ck_assert_pstr_eq(strchr(s1, end), s21_strchr(s1, end));
  // Символ
  ck_assert_pstr_eq(strchr(s1, sym), s21_strchr(s1, sym));
  // Число
  ck_assert_pstr_eq(strchr(s1, digit), s21_strchr(s1, digit));
  ck_assert_pstr_eq(strchr(s1, maybe_digit), s21_strchr(s1, maybe_digit));
}
END_TEST
// 7
int reduction2(char *arr1, char *arr2, int length) {
  int ress = strncmp(arr1, arr2, length);
  ress = ress > 0 ? 1 : ress == 0 ? 0 : -1;
  return ress;
}
START_TEST(tests_strncmp) {
  s21_size_t len0 = 0;
  s21_size_t len1 = 1;
  s21_size_t len2 = 2;
  s21_size_t len11 = 11;
  s21_size_t len21 = 21;
  s21_size_t len30 = 30;
  // Сравнение массива из символов
  char song1[] = "Sweet dreams are made of this";
  char song2[] = "Sweet dreams are made of this";
  ck_assert_int_eq(reduction2(song1, song2, len30),
                   s21_strncmp(song1, song2, len30));
  ck_assert_int_eq(reduction2(song1, song2, len0),
                   s21_strncmp(song1, song2, len0));
  // Сравнение массива разных фраз
  char song3[] = "Who am I to disagree";
  char song4[] = "Who am I to disagryy";
  ck_assert_int_eq(reduction2(song3, song4, len21),
                   s21_strncmp(song3, song4, len21));
  // Сравнение массива из чисел
  char digit1[] = "4815162342";
  char digit2[] = "4815162342";
  ck_assert_int_eq(reduction2(digit1, digit2, len11),
                   s21_strncmp(digit1, digit2, len11));
  ck_assert_int_eq(reduction2(digit1, digit2, len2),
                   s21_strncmp(digit1, digit2, len2));
  ck_assert_int_eq(reduction2(digit1, digit2, len0),
                   s21_strncmp(digit1, digit2, len0));
  // Сравнение пустой строки с пробелом
  char space_str1[] = " ";
  char space_str2[] = " ";
  ck_assert_int_eq(reduction2(space_str1, space_str2, len2),
                   s21_strncmp(space_str1, space_str2, len2));
  // Сравнение пустой строки
  char empty_str1[] = "";
  char empty_str2[] = "";
  char empty_str3[] = "K";
  char empty_str4[] = "";
  ck_assert_int_eq(reduction2(empty_str1, empty_str2, len1),
                   s21_strncmp(empty_str1, empty_str2, len1));
  ck_assert_int_eq(reduction2(empty_str3, empty_str4, len1),
                   s21_strncmp(empty_str3, empty_str4, len1));
}
END_TEST
// 8
START_TEST(tests_strncpy) {
  char src1[] = "";
  char src2[] = "Life cycle";
  char src3[] = "\0";
  int len0 = 0;
  int len1 = 1;
  int len4 = 4;
  int lenStr = s21_strlen(src2);
  char dest1[] = "Eat Sleep Code Repeat";
  char dest11[] = "Eat Sleep Code Repeat";
  ck_assert_pstr_eq(strncpy(dest1, src2, lenStr),
                    s21_strncpy(dest11, src2, lenStr));
  // Скопировать полную строку
  char dest2[] = "Eat Sleep Code Repeat";
  char dest22[] = "Eat Sleep Code Repeat";
  ck_assert_pstr_eq(strncpy(dest2, src2, len4),
                    s21_strncpy(dest22, src2, len4));
  // // Первая строка короче копируемой
  char dest3[] = "Eat Sleep Code Repeat";
  char dest33[] = "Eat Sleep Code Repeat";
  ck_assert_pstr_eq(strncpy(dest3, src1, len4),
                    s21_strncpy(dest33, src1, len4));
  // Копируемая строка пустая
  char dest4[10] = "";
  char dest44[10] = "";
  ck_assert_pstr_eq(strncpy(dest4, src2, len4),
                    s21_strncpy(dest44, src2, len4));
  // Все строки пустые
  char dest5[] = "Eat Sleep Code Repeat";
  char dest55[] = "Eat Sleep Code Repeat";
  ck_assert_pstr_eq(strncpy(dest5, src3, len1),
                    s21_strncpy(dest55, src3, len1));
  // Прибавить символ конца строки
  char dest6[] = "Eat Sleep Code Repeat";
  char dest66[] = "Eat Sleep Code Repeat";
  ck_assert_pstr_eq(strncpy(dest6, src2, len1),
                    s21_strncpy(dest66, src2, len1));
  // Копирование 1 символа из копируемой строки
  char dest7[] = "Eat Sleep Code Repeat";
  char dest77[] = "Eat Sleep Code Repeat";
  ck_assert_pstr_eq(strncpy(dest7, src2, len0),
                    s21_strncpy(dest77, src2, len0));
  // Копирование 0 символов из копируемой строки
}
END_TEST
// 9
START_TEST(tests_strcspn) {
  char str1[] = "In the end";
  char str11[] = "In";
  ck_assert_int_eq(strcspn(str1, str11), s21_strcspn(str1, str11));
  // искомые символы находятся в начале строки
  char str22[] = "nI";
  ck_assert_int_eq(strcspn(str1, str22), s21_strcspn(str1, str22));
  // искомые символы находятся в начале строки, но находятся в другой
  // последовательности
  char str33[] = "the";
  ck_assert_int_eq(strcspn(str1, str33), s21_strcspn(str1, str33));
  // искомые символы находятся в середине строки
  char str44[] = "n";
  ck_assert_int_eq(strcspn(str1, str44), s21_strcspn(str1, str44));
  // один искомый символ
  char str55[] = "";
  ck_assert_int_eq(strcspn(str1, str55), s21_strcspn(str1, str55));
  // искомый символ пустой
  char str66[] = "\0";
  ck_assert_int_eq(strcspn(str1, str66), s21_strcspn(str1, str66));
  // искомый символ равен концу строки
  char str7[] = "";
  char str77[] = "";
  ck_assert_int_eq(strcspn(str7, str11), s21_strcspn(str7, str11));
  // первая строка пустая
  ck_assert_int_eq(strcspn(str1, str77), s21_strcspn(str1, str77));
  // вторая строка пустая
  ck_assert_int_eq(strcspn(str7, str77), s21_strcspn(str7, str77));
  // все строки пустые
  char str88[] = "In the end";
  ck_assert_int_eq(strcspn(str1, str88), s21_strcspn(str1, str88));
  // строки одинаковые
}
END_TEST
// 10
START_TEST(error_0) {
  char *str1 = s21_strerror(1);
  char *str2 = strerror(1);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(error_1) {
  char *str1 = s21_strerror(200);
  char *str2 = strerror(200);
  ck_assert_pstr_eq(str1, str2);
}
// 11
START_TEST(tests_strlen) {
  char wich_length1[] = "Boys";
  char wich_length2[] = "1234567890";
  char wich_length3[] = "";
  char wich_length4[] = "\0";
  char wich_length5[] = "!";
  char wich_length6[] = "I hate doing tests, it's not funny at all!!!";
  char wich_length7[] = "\n\n\n";
  char wich_length8[] = "wtf \0 wtf";
  char wich_length9[] = "\0test";
  char wich_length10[] = "        Bless you   \0    .....";
  ck_assert_int_eq(strlen(wich_length1), s21_strlen(wich_length1));
  ck_assert_int_eq(strlen(wich_length2), s21_strlen(wich_length2));
  ck_assert_int_eq(strlen(wich_length3), s21_strlen(wich_length3));
  ck_assert_int_eq(strlen(wich_length4), s21_strlen(wich_length4));
  ck_assert_int_eq(strlen(wich_length5), s21_strlen(wich_length5));
  ck_assert_int_eq(strlen(wich_length6), s21_strlen(wich_length6));
  ck_assert_int_eq(strlen(wich_length7), s21_strlen(wich_length7));
  ck_assert_int_eq(strlen(wich_length8), s21_strlen(wich_length8));
  ck_assert_int_eq(strlen(wich_length9), s21_strlen(wich_length9));
  ck_assert_int_eq(strlen(wich_length10), s21_strlen(wich_length10));
}
END_TEST
// 12
START_TEST(tests_strpbrk) {
  char str1[] = "Wow! This is horosho";
  char str11[] = "!";
  char str77[] = "";
  ck_assert_pstr_eq(strpbrk(str1, str11), s21_strpbrk(str1, str11));
  // проверка на наличие одного символа
  char str22[] = "is";
  ck_assert_pstr_eq(strpbrk(str1, str22), s21_strpbrk(str1, str22));
  // проверка на наличие одного символа из множества символов
  char str33[] = "o";
  ck_assert_pstr_eq(strpbrk(str1, str33), s21_strpbrk(str1, str33));
  // проверка на наличие несколько символов в строке
  char str44[] = "k";
  ck_assert_pstr_eq(strpbrk(str1, str44), s21_strpbrk(str1, str44));
  // нет искомого символа в строке
  char str55[] = "ky";
  ck_assert_pstr_eq(strpbrk(str1, str55), s21_strpbrk(str1, str55));
  // нет искомых символов в строке
  char str6[] = "";
  char str66[] = "";
  ck_assert_pstr_eq(strpbrk(str6, str33), s21_strpbrk(str6, str33));
  // поиск символа в пустой строке
  ck_assert_pstr_eq(strpbrk(str1, str77), s21_strpbrk(str1, str77));
  // пустое множество символов
  ck_assert_pstr_eq(strpbrk(str6, str66), s21_strpbrk(str6, str66));
  // 2 строки пустые
}
END_TEST
// 13
START_TEST(tests_strrchr) {
  int not_exist = 'A';
  int exist = 'd';
  int twice = 'e';
  int end = '\0';
  int digit = 42;
  int maybe_digit = '7';
  int sym = ',';
  char yep[] = "Eat, code, love";
  ck_assert_pstr_eq(strrchr(yep, not_exist), s21_strrchr(yep, not_exist));
  ck_assert_pstr_eq(strrchr(yep, exist), s21_strrchr(yep, exist));
  ck_assert_pstr_eq(strrchr(yep, twice), s21_strrchr(yep, twice));
  ck_assert_pstr_eq(strrchr(yep, end), s21_strrchr(yep, end));
  ck_assert_pstr_eq(strrchr(yep, sym), s21_strrchr(yep, sym));
  ck_assert_pstr_eq(strrchr(yep, digit), s21_strrchr(yep, digit));
  ck_assert_pstr_eq(strrchr(yep, maybe_digit), s21_strrchr(yep, maybe_digit));
}
END_TEST
// 14
START_TEST(tests_strstr) {
  char str1[] = "Oh Oh Oh!";
  char str11[] = "Oh Oh Oh!";
  ck_assert_pstr_eq(strstr(str1, str11), s21_strstr(str1, str11));
  // сравнить 2 одинаковые строки
  char str2[] = "";
  char str22[] = "";
  ck_assert_pstr_eq(strstr(str2, str22), s21_strstr(str2, str22));
  // сравнивать 2 пустые строки
  ck_assert_pstr_eq(strstr(str2, str11), s21_strstr(str2, str11));
  // первая строка пуста
  ck_assert_pstr_eq(strstr(str1, str11), s21_strstr(str1, str11));
  // вторая строка пуста
  char str33[] = "Ohh my god!";
  ck_assert_pstr_eq(strstr(str1, str33), s21_strstr(str1, str33));
  // строка 2 совпадает неполностью со строкой 1
  char str44[] = "h";
  ck_assert_pstr_eq(strstr(str1, str44), s21_strstr(str1, str44));
  // найти, имеющийся символ в строке
  char str55[] = "x";
  ck_assert_pstr_eq(strstr(str1, str55), s21_strstr(str1, str55));
  // поиск несуществующего символа в строке
  char str66[] = "Oh";
  ck_assert_pstr_eq(strstr(str1, str66), s21_strstr(str1, str66));
  // найти первое вхождение слова, которое встречается не 1 раз
  char str77[] = "\0";
  ck_assert_pstr_eq(strstr(str1, str77), s21_strstr(str1, str77));
  // найти символ конца строки
}
END_TEST
// 15

START_TEST(tests_strtok) {
  char str1[] = "This is/my function";
  char str11[] = "This is/my function";
  char tok1[] = "/";
  ck_assert_pstr_eq(strtok(str1, tok1), s21_strtok(str11, tok1));
  // один разделитель
  char str2[] = "";
  char str22[] = "";
  char tok2[] = "";
  ck_assert_pstr_eq(strtok(str2, tok2), s21_strtok(str22, tok2));
  // все строки пустые
  char str3[] = "This is";
  char str33[] = "This is";
  char tok3[] = "\0";
  ck_assert_pstr_eq(strtok(str3, tok3), s21_strtok(str33, tok3));
  // разделитель равен концу строки "\0"
  char str4[] = "This is";
  char str44[] = "This is";
  char tok4[] = "";
  ck_assert_pstr_eq(strtok(str4, tok4), s21_strtok(str44, tok4));
  // разделитель пустой
  char *str5 = S21_NULL;
  char *str55 = S21_NULL;
  char tok5[] = "is";
  ck_assert_pstr_eq(strtok(str5, tok5), s21_strtok(str55, tok5));
  // строки нулы
  char str6[] = "wow-wow-wow";
  char str66[] = "wow-wow-wow";
  char tok6[] = "-";
  strtok(str6, tok6);
  strtok(NULL, tok6);
  s21_strtok(str66, tok6);
  s21_strtok(NULL, tok6);
  ck_assert_pstr_eq(str6, str66);
  // несколько одинаковых разделителей (цикл)
  char str7[] = "wow-wow!wow";
  char str77[] = "wow-wow!wow";
  char tok7[] = "-!";
  strtok(str7, tok7);
  strtok(NULL, tok7);
  s21_strtok(str77, tok7);
  s21_strtok(NULL, tok7);
  ck_assert_pstr_eq(str7, str77);
  // несколько разных разделителей (цикл)
  char str8[] = "wow-wow-wow";
  char str88[] = "wow-wow-wow";
  char tok8[] = "!sl/";
  strtok(str8, tok8);
  s21_strtok(str88, tok8);
  ck_assert_pstr_eq(str8, str88);
  // нет не одного разделителя
}
END_TEST

// main_________________________________________________________

int main(void) {
  Suite *suite = suite_create("UNITS");
  TCase *tcase = tcase_create("TESTS");
  SRunner *srunner = srunner_create(suite);
  int val = 0;

  suite_add_tcase(suite, tcase);
  tcase_add_test(tcase, test_d);
  tcase_add_test(tcase, test_c);
  tcase_add_test(tcase, test_f);
  tcase_add_test(tcase, test_s);
  tcase_add_test(tcase, test_u);
  tcase_add_test(tcase, test_e);

  tcase_add_test(tcase, sprintf_1_c);
  tcase_add_test(tcase, sprintf_2_c);
  tcase_add_test(tcase, sprintf_3_c);
  tcase_add_test(tcase, sprintf_4_c);
  tcase_add_test(tcase, sprintf_5_c);
  // tcase_add_test(tcase, sprintf_6_c);
  tcase_add_test(tcase, sprintf_7_c);
  // tcase_add_test(tcase, sprintf_8_c);
  tcase_add_test(tcase, sprintf_9_c);
  tcase_add_test(tcase, sprintf_10_c);
  tcase_add_test(tcase, sprintf_11_c);
  tcase_add_test(tcase, sprintf_12_c);
  tcase_add_test(tcase, sprintf_13_c);
  tcase_add_test(tcase, sprintf_14_c);
  // tcase_add_test(tcase, sprintf_15_c);
  tcase_add_test(tcase, sprintf_16_c);
  // tcase_add_test(tcase, sprintf_17_c);
  // tcase_add_test(tcase, sprintf_18_c);
  tcase_add_test(tcase, sprintf_19_c);
  // d
  tcase_add_test(tcase, sprintf_1_signed);
  tcase_add_test(tcase, sprintf_2_signed);
  tcase_add_test(tcase, sprintf_3_signed);
  tcase_add_test(tcase, sprintf_4_signed);
  tcase_add_test(tcase, sprintf_5_signed);
  tcase_add_test(tcase, sprintf_6_signed);
  tcase_add_test(tcase, sprintf_7_signed);
  tcase_add_test(tcase, sprintf_8_signed);
  tcase_add_test(tcase, sprintf_9_signed);
  tcase_add_test(tcase, sprintf_10_signed);
  tcase_add_test(tcase, sprintf_11_signed);
  tcase_add_test(tcase, sprintf_12_signed);
  tcase_add_test(tcase, sprintf_13_signed);
  tcase_add_test(tcase, sprintf_14_signed);
  tcase_add_test(tcase, sprintf_15_signed);
  tcase_add_test(tcase, sprintf_16_signed);
  tcase_add_test(tcase, sprintf_17_signed);
  tcase_add_test(tcase, sprintf_18_signed);
  tcase_add_test(tcase, sprintf_19_signed);

  // // f
  tcase_add_test(tcase, sprintf_1_f);
  tcase_add_test(tcase, sprintf_2_f);
  tcase_add_test(tcase, sprintf_3_f);
  tcase_add_test(tcase, sprintf_4_f);
  tcase_add_test(tcase, sprintf_5_f);
  tcase_add_test(tcase, sprintf_6_f);
  tcase_add_test(tcase, sprintf_7_f);
  tcase_add_test(tcase, sprintf_8_f);
  tcase_add_test(tcase, sprintf_9_f);
  tcase_add_test(tcase, sprintf_10_f);
  tcase_add_test(tcase, sprintf_11_f);
  tcase_add_test(tcase, sprintf_12_f);
  tcase_add_test(tcase, sprintf_13_f);
  tcase_add_test(tcase, sprintf_14_f);
  tcase_add_test(tcase, sprintf_15_f);  // 15 степень
  tcase_add_test(tcase, sprintf_16_f);
  tcase_add_test(tcase, sprintf_17_f);
  tcase_add_test(tcase, sprintf_18_f);
  tcase_add_test(tcase, sprintf_19_f);
  tcase_add_test(tcase, sprintf_20_f);
  tcase_add_test(tcase, sprintf_21_f);
  tcase_add_test(tcase, sprintf_22_f);
  tcase_add_test(tcase, sprintf_23_f);
  tcase_add_test(tcase, sprintf_24_f);
  tcase_add_test(tcase, sprintf_25_f);
  tcase_add_test(tcase, sprintf_26_f);
  tcase_add_test(tcase, sprintf_27_f);
  tcase_add_test(tcase, sprintf_28_f);
  tcase_add_test(tcase, sprintf_30_f);
  tcase_add_test(tcase, sprintf_31_f);
  tcase_add_test(tcase, sprintf_32_f);
  tcase_add_test(tcase, sprintf_33_f);
  tcase_add_test(tcase, sprintf_34_f);
  tcase_add_test(tcase, sprintf_35_f);
  tcase_add_test(tcase, sprintf_36_f);
  tcase_add_test(tcase, sprintf_37_f);
  tcase_add_test(tcase, sprintf_38_f);
  tcase_add_test(tcase, sprintf_39_f);
  tcase_add_test(tcase, sprintf_40_f);
  tcase_add_test(tcase, sprintf_1_g);
  tcase_add_test(tcase, sprintf_2_g);
  tcase_add_test(tcase, sprintf_3_g);
  tcase_add_test(tcase, sprintf_4_g);
  tcase_add_test(tcase, sprintf_5_g);
  tcase_add_test(tcase, sprintf_6_g);
  tcase_add_test(tcase, sprintf_7_g);
  tcase_add_test(tcase, sprintf_8_g);
  tcase_add_test(tcase, sprintf_9_g);
  tcase_add_test(tcase, sprintf_10_g);
  tcase_add_test(tcase, sprintf_11_g);
  tcase_add_test(tcase, sprintf_12_g);
  tcase_add_test(tcase, sprintf_1_hex);
  tcase_add_test(tcase, sprintf_1_HEX);
  tcase_add_test(tcase, sprintf_1_signed_i);
  tcase_add_test(tcase, sprintf_1_octal);
  tcase_add_test(tcase, sprintf_1_percent);

  // string
  tcase_add_test(tcase, tests_memchr);
  tcase_add_test(tcase, tests_memcmp);
  tcase_add_test(tcase, tests_memcpy);
  tcase_add_test(tcase, tests_memset);
  tcase_add_test(tcase, tests_strncat);
  tcase_add_test(tcase, tests_strchr);
  tcase_add_test(tcase, tests_strncmp);
  tcase_add_test(tcase, tests_strncpy);
  tcase_add_test(tcase, error_0);
  tcase_add_test(tcase, error_1);
  tcase_add_test(tcase, tests_strcspn);
  tcase_add_test(tcase, tests_strlen);
  tcase_add_test(tcase, tests_strpbrk);
  tcase_add_test(tcase, tests_strrchr);
  tcase_add_test(tcase, tests_strstr);
  tcase_add_test(tcase, tests_strtok);

  // up
  tcase_add_test(tcase, toUp_1);
  tcase_add_test(tcase, toUp_2);
  tcase_add_test(tcase, toUp_3);
  // low
  tcase_add_test(tcase, toLow_1);
  tcase_add_test(tcase, toLow_2);
  tcase_add_test(tcase, toLow_3);
  // trim
  tcase_add_test(tcase, trim_1);
  tcase_add_test(tcase, trim_2);
  tcase_add_test(tcase, trim_3);
  tcase_add_test(tcase, trim_4);
  tcase_add_test(tcase, trim_5);
  tcase_add_test(tcase, trim_6);
  // insert
  tcase_add_test(tcase, insert_1);
  tcase_add_test(tcase, insert_2);
  tcase_add_test(tcase, insert_3);
  tcase_add_test(tcase, insert_4);
  tcase_add_test(tcase, insert_5);
  tcase_add_test(tcase, insert_6);
  tcase_add_test(tcase, insert_7);
  tcase_add_test(tcase, insert_8);
  tcase_add_test(tcase, insert_9);
  srunner_run_all(srunner, CK_NORMAL);
  val = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return val == 0 ? 0 : 1;
}
