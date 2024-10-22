#include "s21_matrix.h"

// create_matrix (создание),
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = INCORRECT_MATRIX;
  if (rows > 0 && columns > 0) {
    error = OK;
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++) result->matrix[i][j] = 0.0;
  }
  return error;
}
// remove_matrix (очистка и уничтожение)
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_is_normal(matrix_t *A) {
  int res = SUCCESS;
  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1)
    res = FAILURE;
  return res;
}
// eq_matrix (сравнение)
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (s21_is_normal(A) == SUCCESS && s21_is_normal(B) == SUCCESS &&
      A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (round(A->matrix[i][j] * pow(10, 7)) !=
            round(B->matrix[i][j] * pow(10, 7))) {
          res = FAILURE;
          j = A->columns;
          i = A->rows;
        }
      }
    }
  } else
    res = FAILURE;
  return res;
}
// Все операции (кроме сравнения матриц) должны возвращать результирующий код:
//  0 - OK
//  1 - Ошибка, некорректная матрица
//  2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

// sum_matrix (сложение)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if ((s21_is_normal(A) == SUCCESS && s21_is_normal(B) == SUCCESS)) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else
      res = ERROR;
  } else
    res = INCORRECT_MATRIX;
  return res;
}
// sub_matrix (вычитание)
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if ((s21_is_normal(A) == SUCCESS && s21_is_normal(B) == SUCCESS)) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else
      res = ERROR;
  } else
    res = INCORRECT_MATRIX;
  return res;
}
// mult_number (умножение на число)
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (s21_is_normal(A) == SUCCESS) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
    }
  } else
    res = INCORRECT_MATRIX;
  return res;
}
// mult_matrix (умножение)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (s21_is_normal(A) == SUCCESS && s21_is_normal(B) == SUCCESS) {
    if ((A->columns == B->rows)) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < B->columns; j++)
          for (int k = 0; k < B->rows; k++)
            result->matrix[i][j] =
                result->matrix[i][j] + A->matrix[i][k] * B->matrix[k][j];
    } else
      res = ERROR;
  } else
    res = INCORRECT_MATRIX;
  return res;
}
// transpose (транспонирование)
int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (s21_is_normal(A) == SUCCESS) {
    if (s21_create_matrix(A->columns, A->rows, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++)
          result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else
    res = INCORRECT_MATRIX;
  return res;
}
// calc_complements (вычисление матрицы алгебраических дополнений)
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (s21_is_normal(A) == SUCCESS) {
    if (A->rows == A->columns) {
      if (A->rows != 1) {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            matrix_t minor = {0};
            double det = 0;
            s21_create_matrix(A->columns - 1, A->rows - 1, &minor);
            s21_fix_matrix(i, j, A, &minor);
            s21_determinant(&minor, &det);
            result->matrix[i][j] = pow(-1, (i + j)) * det;
            s21_remove_matrix(&minor);
          }
        }
      } else {
        s21_create_matrix(1, 1, result);
        result->matrix[0][0] = A->matrix[0][0];
      }
    } else {
      res = ERROR;
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}
// determinant (вычисление определителя)
int s21_determinant(matrix_t *A, double *result) {
  *result = 0.0;
  int res = OK;
  if (s21_is_normal(A) == SUCCESS) {
    if (A->rows == A->columns) {
      *result = A->matrix[0][0];
      *result = s21_det(A);
    } else
      res = ERROR;
  } else
    res = INCORRECT_MATRIX;
  return res;
}

double s21_det(matrix_t *A) {
  double det = 0.0;
  if (A->rows == 1) {
    det = A->matrix[0][0];
  } else {
    matrix_t tmp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_fix_matrix(0, i, A, &tmp);
      if (i % 2)
        det -= A->matrix[0][i] * s21_det(&tmp);
      else
        det += A->matrix[0][i] * s21_det(&tmp);
    }
    s21_remove_matrix(&tmp);
  }
  return det;
}

void s21_fix_matrix(int row, int col, matrix_t *A, matrix_t *result) {
  int x = 0;
  int y = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    y = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) continue;
      result->matrix[x][y] = A->matrix[i][j];
      y++;
    }
    x++;
  }
}
// inverse_matrix (поиск обратной матрицы).
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (s21_is_normal(A) == SUCCESS) {
    double det = 0.0;
    s21_determinant(A, &det);
    if (A->rows != A->columns || (fabs(det) <= 1e-6))
      res = ERROR;
    else if (A->rows == 1 && A->columns == 1 && (fabs(det) > 1e-6)) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1.0 / A->matrix[0][0];
    } else if (A->rows == A->columns && (fabs(det) > 1e-6)) {
      int flag = 0;
      matrix_t tmp_calc = {0};
      flag = s21_calc_complements(A, &tmp_calc);
      if (flag == 0) {
        matrix_t tmp_trans = {0};
        flag = s21_transpose(&tmp_calc, &tmp_trans);
        if (flag == 0) {
          s21_mult_number(&tmp_trans, 1 / det, result);
        }
        s21_remove_matrix(&tmp_trans);
      }
      s21_remove_matrix(&tmp_calc);
    }
  } else
    res = INCORRECT_MATRIX;
  return res;
}
