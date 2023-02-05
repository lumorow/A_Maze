#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class Matrix {
 private:
  // Attributes
  int _rows, _cols;
  double** _matrix;
  void Memory_alloc();
  void Memory_free();

  // Dopp
  bool Disparity(const Matrix& other);

 public:
  // accessor & mutator
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);

  // Methods
  Matrix();
  Matrix(int rows, int cols);
  ~Matrix();
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);

  // Operations
  bool Eq_matrix(const Matrix& other);
  void Sum_matrix(const Matrix& other);
  void Sub_matrix(const Matrix& other);
  void Mul_number(const double num);
  void Mul_matrix(const Matrix& other);

  Matrix& operator=(const Matrix& other);
  Matrix operator+(const Matrix& other);
  Matrix operator-(const Matrix& other);
  Matrix operator*(const Matrix& other);
  Matrix operator*(double num);
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(double num);
  bool operator==(const Matrix& other);
  double& operator()(const int row, const int col);
};

#endif  // SRC_S21_MATRIX_OOP_H_
