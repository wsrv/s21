#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

class S21Matrix {
  //  private:
 public:
  int rows_, cols_;
  double** matrix_;

  void memory_allocation();
  void destroy_matrix();
  void copy_matrix(const S21Matrix& other);
  S21Matrix MinorMatrix(const S21Matrix& other, int i_rows, int j_cols);

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  //----------------------------------------
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  //----------------------------------------
  double& operator()(int row, int col);
  bool operator==(const S21Matrix& other);
  friend S21Matrix operator*(const double num, const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  //----------------------------------------
  int get_rows();
  int get_cols();
  void set_rows(int rows);
  void set_cols(int cols);
};

#endif  // S21_MATRIX_OOP_HPP