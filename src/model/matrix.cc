#include "matrix.h"

void Matrix::Memory_alloc() {
  _matrix = new double*[_rows];
  for (int i = 0; i < _rows; i++) {
    _matrix[i] = new double[_cols]{0};
  }
}

void Matrix::Memory_free() {
  if (_matrix) {
    for (int i = 0; i < _rows; i++) {
      delete _matrix[i];
    }
    delete[] _matrix;
    _rows = 0;
    _cols = 0;
    _matrix = nullptr;
  }
}

// Methods
Matrix::Matrix() {
  _rows = 0;
  _cols = 0;
  _matrix = nullptr;
}

Matrix::Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw std::invalid_argument("rows or cols can't be <= 0");
  _rows = rows;
  _cols = cols;
  Memory_alloc();
}

Matrix::~Matrix() { Memory_free(); }

Matrix::Matrix(const Matrix& other) {
  if (!(*this == other)) {
    _rows = other._rows;
    _cols = other._cols;
    Memory_alloc();
    for (int i = 0; i < other._rows; i++) {
      for (int j = 0; j < other._cols; j++) {
        _matrix[i][j] = other._matrix[i][j];
      }
    }
  }
}

Matrix::Matrix(Matrix&& other) {
  _rows = other._rows;
  _cols = other._cols;
  _matrix = other._matrix;
  other._rows = 0;
  other._cols = 0;
  other._matrix = nullptr;
}

// accessor & mutator
int Matrix::GetRows() { return _rows; }

int Matrix::GetCols() { return _cols; }

void Matrix::SetRows(int rows) {
  if (rows < 0) throw std::out_of_range("wrong size");
  if (rows != _rows) {
    Matrix tmp(rows, _cols);
    int range = rows;
    if (rows > _rows) range = _rows;
    for (int i = 0; i < range; i++) {
      for (int j = 0; j < _cols; j++) {
        tmp._matrix[i][j] = _matrix[i][j];
      }
    }
    Memory_free();
    _rows = rows;
    _cols = tmp._cols;
    Memory_alloc();
    for (int i = 0; i < tmp._rows; i++) {
      for (int j = 0; j < tmp._cols; j++) {
        _matrix[i][j] = tmp._matrix[i][j];
      }
    }
    tmp.Memory_free();
  }
}

void Matrix::SetCols(int cols) {
  if (cols < 0) throw std::out_of_range("wrong size");
  if (cols != _cols) {
    Matrix tmp(_rows, cols);
    int range = cols;
    if (cols > _cols) range = _cols;
    for (int i = 0; i < _rows; i++) {
      for (int j = 0; j < range; j++) {
        tmp._matrix[i][j] = _matrix[i][j];
      }
    }
    Memory_free();
    _rows = tmp._rows;
    _cols = cols;
    Memory_alloc();
    for (int i = 0; i < tmp._rows; i++) {
      for (int j = 0; j < tmp._cols; j++) {
        _matrix[i][j] = tmp._matrix[i][j];
      }
    }
    tmp.Memory_free();
  }
}

// Operations

bool Matrix::Eq_matrix(const Matrix& other) {
  bool res = true;
  if (Disparity(other)) {
    res = false;
  } else {
    for (int i = 0; i < _rows && res == true; i++) {
      for (int j = 0; j < _cols; j++) {
        if (fabs(_matrix[i][j] - other._matrix[i][j]) > 0.0000001) {
          res = false;
        }
      }
    }
  }
  return res;
}

void Matrix::Sum_matrix(const Matrix& other) {
  if (Disparity(other)) throw std::invalid_argument("Different Dimensions");
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] += other._matrix[i][j];
    }
  }
}

void Matrix::Sub_matrix(const Matrix& other) {
  if (Disparity(other)) throw std::invalid_argument("Different Dimensions");
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] -= other._matrix[i][j];
    }
  }
}

void Matrix::Mul_number(const double num) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _matrix[i][j] *= num;
    }
  }
}

void Matrix::Mul_matrix(const Matrix& other) {
  if (_cols != other._rows) {
    throw std::invalid_argument("Invalid dimensions");
  }
  Matrix temp(_rows, other._cols);
  for (int n = 0; n < _rows; n++) {
    for (int m = 0; m < other._cols; m++) {
      for (int i = 0; i < _cols; i++) {
        temp._matrix[n][m] += _matrix[n][i] * other._matrix[i][m];
      }
    }
  }
  *this = temp;
}

// Operators

Matrix& Matrix::operator=(const Matrix& other) {
  if (*this == other) return *this;
  if (this->_cols == other._cols && this->_rows == other._rows) {
    for (int n = 0; n < this->_rows; n++) {
      for (int m = 0; m < this->_cols; m++) {
        this->_matrix[n][m] = other._matrix[n][m];
      }
    }
  } else {
    this->Memory_free();
    this->_cols = other._cols;
    this->_rows = other._rows;
    this->Memory_alloc();
    for (int n = 0; n < this->_rows; n++) {
      for (int m = 0; m < this->_cols; m++) {
        this->_matrix[n][m] = other._matrix[n][m];
      }
    }
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix result(*this);
  result.Sum_matrix(other);
  return result;
}

Matrix Matrix::operator-(const Matrix& other) {
  Matrix result(*this);
  result.Sub_matrix(other);
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result(*this);
  result.Mul_matrix(other);
  return result;
}

Matrix Matrix::operator*(double num) {
  Matrix result(*this);
  result.Mul_number(num);
  return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
  this->Sum_matrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  this->Sub_matrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  this->Mul_matrix(other);
  return *this;
}

Matrix& Matrix::operator*=(double num) {
  this->Mul_number(num);
  return *this;
}

bool Matrix::operator==(const Matrix& other) {
  return (this->Eq_matrix(other));
}

double& Matrix::operator()(int row, int col) {
  if (row > _rows || col > _cols) throw std::invalid_argument("wrong size");
  return _matrix[row][col];
}

// Dopp

bool Matrix::Disparity(const Matrix& other) {
  return (_rows != other._rows || _cols != other._cols);
}
