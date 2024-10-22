#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transformations.h"

int readFile(char* filename, dataNur* outputdata) {
  FILE* fp;
  size_t len = 0;
  int vertexesNum = 0;
  int facetsNum = -1;
  int error = 0;
  char* buffer = NULL;
  outputdata->count_of_vertexes = 0;
  outputdata->count_of_facets = 0;
  fp = fopen(filename, "r");

  if (fp != NULL) {
    error = countSize(fp, outputdata);
    outputdata->vertexesArr =
        (double*)calloc(outputdata->count_of_vertexes, sizeof(double));
    outputdata->count_of_facets *= 2;
    outputdata->facetsArr =
        (int*)calloc(outputdata->count_of_facets, sizeof(int));

    while (!error && getline(&buffer, &len, fp) != -1) {
      if (buffer[0] == 'v' && buffer[1] == ' ')
        parsVertexes(outputdata, &vertexesNum, buffer);
      if (buffer[0] == 'f' && buffer[1] == ' ')
        parsFacets(outputdata, &facetsNum, buffer);
    }
  } else
    error = 1;

  free(buffer);
  fclose(fp);
  return error;
}

int parsVertexes(dataNur* outputdata, int* vertexesNum, char* buffer) {
  for (int i = 1; buffer[i] != '\n' && buffer[i] != '\0'; i++)
    if (buffer[i] != ' ')
      outputdata->vertexesArr[(*vertexesNum)++] = makeNum(buffer, &i);
  return 0;
}

int parsFacets(dataNur* outputdata, int* facetsNum, char* buffer) {
  int flag = 0, first = 0;
  for (char *start = buffer, *end = start;
       *start && *start != '\n' && *start != '\0' && *start != EOF; start++) {
    while ((*start > '9' || *start < '0') && *start) start++;

    if ((*(start - 1) == ' ') && *start) {
      outputdata->facetsArr[++(*facetsNum)] =
          ((int)strtol(start, &end, 10)) - 1;
      if (flag)
        outputdata->facetsArr[++(*facetsNum)] =
            abs(((int)strtol(start, &end, 10)) - 1);
      if (!flag++) first = outputdata->facetsArr[(*facetsNum)];
      start = end;
    }
  }
  outputdata->facetsArr[++(*facetsNum)] = first;
  return 0;
}

double makeNum(char* content, int* i) {
  double res = 0.0;
  int j = 0;
  int flag = 0;
  int dot = 0;
  int minus = 0;

  for (; content[(*i)] != ' ' && content[(*i)] != '\0' && content[(*i)] != '\n';
       (*i)++) {
    if (content[(*i)] == '.') {
      flag = j;
      dot++;
    } else if (content[(*i)] >= '0' && content[(*i)] <= '9') {
      j++;
      res += (double)(content[(*i)] - '0') / ((int)pow(10, j));
    } else if (content[(*i)] == '-') {
      minus = 1;
    } else
      break;
  }
  if (!flag) flag = j;
  res *= pow(10, (flag));
  if (minus) res *= -1;
  return res;
}

int countSize(FILE* fp, dataNur* outputdata) {
  char* line = NULL;
  int error = 0;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1) {
    if (line[0] == 'v' && line[1] == ' ')
      for (int i = 1; i < (int)strlen(line); i++)
        if (line[i - 1] == ' ' &&
            ((line[i] >= '0' && line[i] <= '9') || line[i] == '-'))
          outputdata->count_of_vertexes++;

    if (line[0] == 'f' && line[1] == ' ')
      for (int i = 1; i < (int)strlen(line); i++) {
        if (line[i - 1] == ' ' &&
            ((line[i] >= '0' && line[i] <= '9') || line[i] == '-'))
          outputdata->count_of_facets++;
        if (line[i - 1] == ' ' && line[i] == '-') error = 1;
      }
  }
  rewind(fp);
  free(line);
  return error;
}