#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(char *file_name, int fcount, char all_patterns[250][1000], int pcount,
          int no_reg_i, int invert_v, int str_match_c, int file_match_l,
          int num_n, int no_names_h, int no_errors_s, int match_parts_o);

int main(int argc, char **argv) {
  int rez = 0;
  char all_patterns[250][1000] = {0};
  char all_files[250][256] = {0};
  char str[1000] = {0};
  int pcount = 0, fcount = 0;
  FILE *f;
  if (argc < 3) {
    fprintf(stderr, "Usage: %s pattern file1 [file2 ...]\n", argv[0]);
  } else {
    int no_reg_i = 0, invert_v = 0, str_match_c = 0, file_match_l = 0,
        num_n = 0, no_names_h = 0, no_errors_s = 0, match_parts_o = 0,
        flag_e = 0;
    while ((rez = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
      switch (rez) {
        case 'i':
          no_reg_i = 1;
          break;
        case 'v':
          invert_v = 1;
          break;
        case 'c':
          str_match_c = 1;
          break;
        case 'l':
          file_match_l = 1;
          break;
        case 'n':
          num_n = 1;
          break;
        case 'h':
          no_names_h = 1;
          break;
        case 's':
          no_errors_s = 1;
          break;
        case 'o':
          match_parts_o = 1;
          break;
        case 'e':
          flag_e = 1;
          strcpy(all_patterns[pcount], optarg);
          pcount++;
          break;
        case 'f':
          f = fopen(optarg, "r");
          if (f != NULL) {
            while (!feof(f)) {
              if (fgets(str, 1000, f) != NULL) {
                if (str[strlen(str) - 1] == '\n' && strlen(str) - 1 != 0)
                  str[strlen(str) - 1] = '\0';
                strcpy(all_patterns[pcount], str);
                pcount++;
              }
            }
            fclose(f);
          }
          break;
        default:
          return 1;
      }
    }
    int check_er;
    check_er = argc - optind;
    if (check_er != 0) {
      if (flag_e == 0) {
        strcpy(all_patterns[0], argv[optind]);
        pcount++;
        for (int i = 0, j = optind + 1; j < argc; j++, i++) {
          strcpy(all_files[i], argv[j]);
          fcount++;
        }
      }
      if (flag_e == 1) {
        for (int i = 0, j = optind; j < argc; j++, i++) {
          strcpy(all_files[i], argv[j]);
          fcount++;
        }
      }
    }
    for (int i = 0; i < fcount; i++) {
      grep(all_files[i], fcount, all_patterns, pcount, no_reg_i, invert_v,
           str_match_c, file_match_l, num_n, no_names_h, no_errors_s,
           match_parts_o);
    }
  }
  return 0;
}  // main

void grep(char *file_name, int fcount, char all_patterns[250][1000], int pcount,
          int no_reg_i, int invert_v, int str_match_c, int file_match_l,
          int num_n, int no_names_h, int no_errors_s, int match_parts_o) {
  char str[1000];
  int match_flag = 0;
  char buffLine[1000];
  int line_count = 0;
  int match_count = 0;
  int rz = 0;
  int v_count = 0;
  regex_t regex = {0};
  regmatch_t matches = {0};
  if (invert_v == 1) match_parts_o = 0;
  if (fcount < 2) no_names_h = 1;
  FILE *f = fopen(file_name, "r");
  if (f != NULL) {
    while (fgets(str, 1000, f) != NULL && match_flag == 0) {
      if (match_parts_o == 1) strcpy(buffLine, str);
      line_count++;
      for (int j = 0; j < pcount; j++) {
        if (no_reg_i)
          rz = regcomp(&regex, all_patterns[j], REG_EXTENDED | REG_ICASE);
        else
          rz = regcomp(&regex, all_patterns[j], REG_EXTENDED);
        if (rz == 0) {
          rz = regexec(&regex, str, 1, &matches, 0);
          if (rz == REG_NOMATCH) v_count++;
          if ((invert_v == 0 && rz == 0) ||
              (invert_v == 1 && rz == REG_NOMATCH && v_count == pcount)) {
            if (str_match_c == 0) {
              if (file_match_l == 0) {
                if (no_names_h == 0) printf("%s:", file_name);
                if (num_n == 1) printf("%d:", line_count);
                if (match_parts_o == 0) {
                  printf("%s", str);
                  if (str[strlen(str) - 1] != '\n') printf("\n");
                } else {
                  char *pt = buffLine;
                  while (regexec(&regex, pt, 1, &matches, 0) == 0) {
                    printf("%.*s\n", (int)(matches.rm_eo - matches.rm_so),
                           pt + matches.rm_so);
                    pt += matches.rm_eo;
                  }
                }
                regfree(&regex);
                break;
              } else if (file_match_l == 1) {
                printf("%s", file_name);
                if (file_name[strlen(file_name) - 1] != '\n') printf("\n");
                match_flag = 1;
                regfree(&regex);
                break;
              }
            } else if (str_match_c == 1) {
              match_count = match_count + 1;
              if (file_match_l == 1) match_flag = 1;
              regfree(&regex);
              break;
            }
          }
          regfree(&regex);
        }
      }
      v_count = 0;
    }

    line_count = 0;
    match_flag = 0;
    if (str_match_c == 1 && file_match_l == 0) {
      if (no_names_h == 0) printf("%s:", file_name);
      printf("%d", match_count);
      if (file_name[strlen(file_name) - 1] != '\n') printf("\n");
    }
    if (str_match_c == 1 && file_match_l == 1) {
      if (fcount > 1) {
        if (match_count > 0) {
          if (no_names_h == 0) printf("%s:", file_name);
          printf("%d\n%s\n", match_count, file_name);
        } else {
          if (no_names_h == 0) printf("%s:", file_name);
          printf("%d\n", match_count);
        }
      } else {
        if (match_count == 0)
          printf("0\n");
        else {
          printf("%d\n%s", match_count, file_name);
          if (file_name[strlen(file_name) - 1] != '\n') printf("\n");
        }
      }
    }
    fclose(f);
  }

  else if (no_errors_s == 0)
    fprintf(stderr, "%s: No such file or directory\n", file_name);
}
