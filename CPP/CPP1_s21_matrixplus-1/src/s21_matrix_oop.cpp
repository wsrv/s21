#include "s21_matrix_oop.h"
using namespace std;
// -------------helpers-------------
void S21Matrix::memory_allocation() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();
}

void S21Matrix::destroy_matrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; i++) delete[] this->matrix_[i];
    delete[] this->matrix_;
  }
  this->matrix_ = nullptr;
  this->cols_ = 0;
  this->rows_ = 0;
}

void S21Matrix::copy_matrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::out_of_range("Matrix have different size");
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] = other.matrix_[i][j];
}
//-------------standert methods-------------
S21Matrix::S21Matrix() {  // Базовый конструктор, инициализирующий матрицу
                          // некоторой заранее заданной размерностью
  this->rows_ = 2;
  this->cols_ = 2;
  this->memory_allocation();
}

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols) {  // Параметризированный конструктор с
                                  // количеством строк и столбцов
  if (this->rows_ < 1 || this->cols_ < 1)
    throw std::invalid_argument("invalid_argument");
  this->memory_allocation();
}

S21Matrix::S21Matrix(const S21Matrix &other)  // Конструктор копирования
    : rows_(other.rows_), cols_(other.cols_) {
  this->memory_allocation();
  this->copy_matrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other)  // Конструктор переноса
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  this->copy_matrix(other);
  other.destroy_matrix();
}

S21Matrix::~S21Matrix() {  // Деструктор
  if (matrix_ != nullptr) this->destroy_matrix();
}
//-------------operators-------------
S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix temp(*this);
  temp.SumMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix temp(*this);
  temp.SubMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix temp(*this);
  temp.MulNumber(num);
  return temp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix operator*(const double num, const S21Matrix &other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    destroy_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    memory_allocation();
    copy_matrix(other);
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= this->rows_ || col >= this->cols_ || row < 0 || col < 0)
    throw std::invalid_argument("invalid argument");
  return this->matrix_[row][col];
}

//-------------- operations 2 --------------

bool S21Matrix::EqMatrix(
    const S21Matrix &other) {  // Проверяет матрицы на равенство между собой
  bool result = true;
  if (other.cols_ == cols_ && other.rows_ == rows_) {
    for (int i = 0; i < other.rows_; i++)
      for (int j = 0; j < other.cols_; j++)
        if (fabs(other.matrix_[i][j] - matrix_[i][j]) >= 1e-7) result = false;
  } else
    result = false;
  return result;
}

void S21Matrix::SumMatrix(
    const S21Matrix &other) {  // Прибавляет вторую матрицы к текущей.
                               // Исключение - различная размерность матриц
  if ((rows_ != other.rows_) || (cols_ != other.cols_))
    throw std::invalid_argument("Wrong size of matrix");
  for (int i = 0; i < other.rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
}

void S21Matrix::SubMatrix(
    const S21Matrix &other) {  // Вычитает из текущей матрицы другую. Исключение
                               // - различная размерность матриц
  if ((rows_ != other.rows_) || (cols_ != other.cols_))
    throw std::invalid_argument("Wrong size of matrix");
  for (int i = 0; i < other.rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
}

void S21Matrix::MulNumber(
    const double num) {  // Умножает текущую матрицу на число
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = matrix_[i][j] * num;
}

void S21Matrix::MulMatrix(
    const S21Matrix &
        other) {  // Умножает текущую матрицу на вторую. Исключение - число
                  // столбцов первой матрицы не равно числу строк второй матрицы
  if (cols_ != other.rows_) throw std::invalid_argument("Wrong size of matrix");
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      for (int k = 0; k < rows_; k++)
        result.matrix_[i][j] =
            result.matrix_[i][j] + matrix_[i][k] * other.matrix_[k][j];
  *this = result;
}

S21Matrix S21Matrix::Transpose() {  // Создает новую транспонированную матрицу
                                    // из текущей и возвращает ее
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix
S21Matrix::CalcComplements() {  // Вычисляет матрицу алгебраических дополнений
                                // текущей матрицы и возвращает ее. Исключение -
                                // матрица не является квадратной
  if (rows_ != cols_) throw std::domain_error("Matrix is not square");
  S21Matrix temp(rows_, cols_);
  if (rows_ == 1 && cols_ == 1)
    temp.matrix_[0][0] = 1;
  else
    for (int i = 0; i < temp.rows_; i++)
      for (int j = 0; j < temp.cols_; j++) {
        // S21Matrix temp1 = MinorMatrix(*this, i, j);
        temp.matrix_[i][j] =
            MinorMatrix(*this, i, j).Determinant() * pow(-1.0, (i + j));
      }
  return temp;
}

S21Matrix S21Matrix::MinorMatrix(
    const S21Matrix &other, int i_rows,
    int j_cols) {  // Вспомогатеьлная функция помощник для вычисления
                   // определителя. Получение матрицы миноров.

  S21Matrix temp(other.rows_ - 1, other.cols_ - 1);
  for (int i = 0; i < other.rows_; i++)
    for (int j = 0; j < other.cols_; j++)
      if (i != i_rows && j != j_cols) {
        if (i > i_rows && j < j_cols)
          temp.matrix_[i - 1][j] = other.matrix_[i][j];
        else if (i > i_rows && j > j_cols)
          temp.matrix_[i - 1][j - 1] = other.matrix_[i][j];
        else if (i < i_rows && j > j_cols)
          temp.matrix_[i][j - 1] = other.matrix_[i][j];
        else
          temp.matrix_[i][j] = other.matrix_[i][j];
      }

  return temp;
}

double S21Matrix::Determinant() {  // Вычисляет и возвращает определитель
                                   // текущей матрицы. Исключение - матрица не
                                   // является квадратной
  if (cols_ != rows_) throw std::domain_error("Matrix is not square");
  double determinant = 0.0;
  if (rows_ == 1 && cols_ == 1)
    determinant = matrix_[0][0];
  else if (rows_ == 2 && cols_ == 2)
    determinant =
        (matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]);
  else {
    for (int j = 1; j <= cols_; j++) {
      // S21Matrix temp = MinorMatrix(*this, 0, j - 1);
      determinant += pow(-1, 1 + (double)j) * matrix_[0][j - 1] *
                     MinorMatrix(*this, 0, j - 1).Determinant();
      // }
    }
  }
  return determinant;
}

S21Matrix
S21Matrix::InverseMatrix() {  // Вычисляет и возвращает обратную матрицу.
                              // Исключение - определитель матрицы равен 0
  double determinant = Determinant();
  if (rows_ != cols_ || determinant == 0)
    throw std::invalid_argument("Determinant is zero");
  // S21Matrix temp = CalcComplements();
  S21Matrix temp = (CalcComplements().Transpose());
  temp.MulNumber(1.0 / determinant);
  return temp;
}

//-----------------accessors and mutators-----------------

int S21Matrix::get_rows() { return rows_; }

int S21Matrix::get_cols() { return cols_; }

void S21Matrix::set_rows(int rows) {
  S21Matrix temp(*this);
  destroy_matrix();
  rows_ = rows;
  cols_ = temp.cols_;
  memory_allocation();
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = temp.matrix_[i][j];
}

void S21Matrix::set_cols(int cols) {
  S21Matrix temp(*this);
  destroy_matrix();
  rows_ = temp.rows_;
  cols_ = cols;
  memory_allocation();
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = temp.matrix_[i][j];  // copy
}

// int main() {
//   S21Matrix matrix_a(2, 3);
//   // matrix_a.rows_ = 2;
//   //   matrix_a.cols_ = 2;
//   //   S21Matrix matrix_b(2, 2);
//   //   // S21Matrix result(2, 2);

//   matrix_a.matrix_[0][0] = 1;
//   matrix_a.matrix_[0][1] = 2;
//   matrix_a.matrix_[0][2] = 3;
//   matrix_a.matrix_[1][0] = 4;
//   matrix_a.matrix_[1][1] = 5;
//   matrix_a.matrix_[1][2] = 6;

//   //   matrix_b.matrix_[0][0] = -78.14;
//   //   matrix_b.matrix_[0][1] = 0;
//   //   matrix_b.matrix_[1][0] = -0.3;
//   //   matrix_b.matrix_[1][1] = 2;
//   for (int i = 0; i < matrix_a.rows_; i++) {
//     for (int j = 0; j < matrix_a.cols_; j++)
//       std::cout << matrix_a.matrix_[i][j] << " ";
//     std::cout << "\n";
//   }
//   std::cout << "\n";

//   //   // // result(0, 0) = -75;
//   //   // // result(0, 1) = 0.56;
//   //   // // result(1, 0) = -69.6;
//   //   // // result(1, 1) = 2;
//   // std::cout << matrix_a.rows_ << " ";
//   // std::cout << matrix_a.cols_ << " ";
//   matrix_a = matrix_a.Transpose();
//   // std::cout << matrix_a.rows_ << " ";
//   // std::cout << matrix_a.cols_ << " ";

//   for (int i = 0; i < matrix_a.rows_; i++) {
//     for (int j = 0; j < matrix_a.cols_; j++)
//       std::cout << matrix_a.matrix_[i][j] << " ";
//     std::cout << "\n";
//   }
// }