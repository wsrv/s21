#include "transformations.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rotateObj(dataNur* inputdata, double degree, char axis) {
  int add1 = 0, add2 = 0, error = 0;
  degree *= S21_PI / 180.0;
  switch (axis) {
    case 'x':
      add1 = 1;
      add2 = 2;
      break;
    case 'y':
      add1 = 0;
      add2 = 2;
      break;
    case 'z':
      add1 = 0;
      add2 = 1;
      break;
    default:
      error = 1;
      break;
  }
  for (int i = 0; i < inputdata->count_of_vertexes; i += 3) {
    double axis1 = inputdata->vertexesArr[i + add1];
    double axis2 = inputdata->vertexesArr[i + add2];
    inputdata->vertexesArr[i + add1] =
        cos(degree) * axis1 - sin(degree) * axis2;
    inputdata->vertexesArr[i + add2] =
        sin(degree) * axis1 + cos(degree) * axis2;
  }

  return degree > 359 ? error : 1;
}

int scalingObj(dataNur* inputdata, double scale) {
  for (int i = 0; i < inputdata->count_of_vertexes; i++)
    inputdata->vertexesArr[i] *= scale;
  return scale > 0 ? 0 : 1;
}

int shiftObj(dataNur* inputdata, double shift, char axis) {
  shift /= 100.0;
  int error = 0, add = 0;
  switch (axis) {
    case 'x':
      add = 0;
      break;
    case 'y':
      add = 1;
      break;
    case 'z':
      add = 2;
      break;
    default:
      error = 1;
      break;
  }
  for (int i = 0; i < inputdata->count_of_vertexes; i += 3)
    inputdata->vertexesArr[i + add] += shift;
  return error;
}

int nurlanization(dataNur* inputdata) {
  if (!inputdata) return 1;
  double max = inputdata->vertexesArr[0];
  for (int i = 0; i < inputdata->count_of_vertexes; i++)
    if (inputdata->vertexesArr[i] > max) max = inputdata->vertexesArr[i];
  scalingObj(inputdata, 0.5 / max);
  return 0;
}