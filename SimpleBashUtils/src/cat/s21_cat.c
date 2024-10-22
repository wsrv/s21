#include <stdio.h>
#include <string.h>

void print_file(char *name, int flag_v, int num_no_empty_b, int print_end_e,
                int num_all_n, int delete_empty_s, int tabt);

int main(int argc, char **argv) {
  int flag_v = 0, num_no_empty_b = 0, print_end_e = 0, num_all_n = 0,
      delete_empty_s = 0, tabt = 0;
  int file_flag = 0, error_flag = 0;

  for (int i = 1; i < argc; i++) {
    //обработка длинных флагов
    if ((argv[i][0] == '-' && argv[i][1] == '-') && file_flag == 0) {
      if (strcmp(argv[i], "--number-nonblank") == 0)
        num_no_empty_b = 1;
      else if (strcmp(argv[i], "--number") == 0)
        num_all_n = 1;
      else if (strcmp(argv[i], "--squeeze-blank") == 0)
        delete_empty_s = 1;
      else if (strlen(argv[i]) != 2)
        error_flag = 1;
    }
    //обработка коротких флагов
    else if ((argv[i][0] == '-' && argv[i][1] != '-') && file_flag == 0) {
      int len = strlen(argv[i]);
      for (int j = 1; j < len; j++) {
        if (argv[i][j] == 'b')
          num_no_empty_b = 1;
        else if (argv[i][j] == 'e') {
          print_end_e = 1;
          flag_v = 1;
        } else if (argv[i][j] == 'n')
          num_all_n = 1;
        else if (argv[i][j] == 'v')
          flag_v = 1;
        else if (argv[i][j] == 's')
          delete_empty_s = 1;
        else if (argv[i][j] == 't') {
          tabt = 1;
          flag_v = 1;
        } else if (argv[i][j] == 'E')
          print_end_e = 1;
        else if (argv[i][j] == 'T')
          tabt = 1;
        else
          error_flag = 1;
      }  // for
    }    // if
    //работа с файлов
    else if (error_flag != 1) {
      file_flag = 1;
      print_file(argv[i], flag_v, num_no_empty_b, print_end_e, num_all_n,
                 delete_empty_s, tabt);
    }
  }
  return 0;
}  // main

void print_file(char *name, int flag_v, int num_no_empty_b, int print_end_e,
                int num_all_n, int delete_empty_s, int tabt) {
  FILE *f;
  int lines = 1;
  int end_flag = 0;
  char c, c1 = '\n';
  if ((f = fopen(name, "r")) != NULL) {
    while (fscanf(f, "%c", &c) != EOF && end_flag != 1) {
      //флаг s
      if (delete_empty_s == 1 && c == '\n' && c1 == '\n') {
        if (num_all_n == 1 && num_no_empty_b == 0) {
          printf("%6d\t", lines);
          lines++;
        } else if (num_no_empty_b == 1 && c != '\n' && c1 == '\n') {
          printf("%6d\t", lines);
          lines++;
        }
        if (print_end_e == 1)
          printf("$\n");
        else
          printf("\n");
        while (c == '\n' && end_flag == 0) {
          c1 = c;
          if (fscanf(f, "%c", &c) == EOF) end_flag = 1;
        }
      }
      if (end_flag != 1) {
        //нумерация
        if (num_all_n == 1 && num_no_empty_b == 0 && c1 == '\n') {
          printf("%6d\t", lines);
          lines++;
        } else if (num_no_empty_b == 1 && c != '\n' && c1 == '\n') {
          printf("%6d\t", lines);
          lines++;
        }
        //флаги e t v
        if (print_end_e == 1 && c == '\n')
          printf("$%c", c);
        else if (flag_v == 1 && c < ' ' && c != '\n' && c != '\t')
          printf("^%c", c + '@');
        else if (flag_v == 1 && (int)c == 127)
          printf("^?");
        else if (tabt == 1 && c == '\t')
          printf("^I");
        else if (end_flag != 1)
          printf("%c", c);
        c1 = c;
      }
    }  // while*/
  }    // else
  fclose(f);
}
