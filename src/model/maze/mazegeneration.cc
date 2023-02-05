#include "maze.h"
namespace s21 {

void Maze::GenerateMaze(int rows, int cols) {
  // иницилизация всех переменных должна быть
  height_matrix_ = rows;
  width_matrix_ = cols;
  for (int j = 0; j < width_matrix_; j++) {
    generatingLine_.push_back(0);
  }
  width_ = Matrix(rows, cols);
  height_ = Matrix(rows, cols);

  for (int j = 0; j < height_matrix_ - 1; j++) {
    SetNewLine();
    AddWalls(j);
    CorrectLine(j);
  }
  AddBottomLine();
  ClearGenerator();
}

bool Maze::GetRandomBoolValue() {
  std::random_device rd;
  std::default_random_engine engine(rd());
  std::uniform_int_distribution<int> dist(0, 1);
  return static_cast<bool>(dist(engine));
}

void Maze::SetZeroValues() {
  for (int j = 0; j < width_matrix_; j++) {
    generatingLine_[j] = 0;
  }
}

void Maze::SetNewLine() {
  for (int j = 0; j < width_matrix_; j++) {
    if (generatingLine_[j] == 0) {
      generatingLine_[j] = countUnicSet_;
      countUnicSet_++;
    }
  }
}

void Maze::JoinSet(int index, int value) {
  int mutableSet = generatingLine_[index + 1];
  for (int j = 0; j < width_matrix_; j++) {
    if (generatingLine_[j] == mutableSet) {
      generatingLine_[j] = value;
    }
  }
}

void Maze::CorrectEndLine() {
  for (int i = 0; i < width_matrix_ - 1; i++) {
    if (generatingLine_[i] != generatingLine_[i + 1]) {
      height_(height_matrix_ - 1, i) = 0;
      JoinSet(i, generatingLine_[i]);
    }
    width_(height_matrix_ - 1, i) = 1;
  }
  width_(height_matrix_ - 1, width_matrix_ - 1) = 1;
}

void Maze::CorrectLine(int row) {
  for (int i = 0; i < width_matrix_; i++) {
    if (width_(row, i) == true) {
      generatingLine_[i] = 0;
    }
  }
}

void Maze::AddWalls(int row) {
  AddVertical(row);
  AddHorizontal(row);
  CheckWalls(row);
}

void Maze::AddVertical(int row) {
  for (int i = 0; i < width_matrix_ - 1; i++) {
    bool choise = GetRandomBoolValue();
    if (choise == true || generatingLine_[i] == generatingLine_[i + 1]) {
      height_(row, i) = 1;
    } else {
      JoinSet(i, generatingLine_[i]);
    }
  }
  height_(row, width_matrix_ - 1) = 1;
}

void Maze::AddHorizontal(int row) {
  for (int i = 0; i < width_matrix_; i++) {
    bool choise = GetRandomBoolValue();
    if (Count(generatingLine_[i]) != 1 && choise == true) {
      width_(row, i) = 1;
    }
  }
}

void Maze::CheckWalls(int row) {
  for (int i = 0; i < width_matrix_; i++) {
    if (CalculateHorizontal(generatingLine_[i], row) == 0) {
      width_(row, i) = 0;
    }
  }
}

int Maze::CalculateHorizontal(int element, int row) {
  int countHorizontalWalls = 0;
  for (int i = 0; i < width_matrix_; i++) {
    if (generatingLine_[i] == element && width_(row, i) == 0) {
      countHorizontalWalls++;
    }
  }
  return countHorizontalWalls;
}

int Maze::Count(int value) {
  int count = 0;
  for (int i = 0; i < width_matrix_; i++) {
    if (generatingLine_[i] == value) {
      count++;
    }
  }
  return count;
}

void Maze::AddBottomLine() {
  SetNewLine();
  AddVertical(height_matrix_ - 1);
  CorrectEndLine();
}

void Maze::ClearGenerator() {
  generatingLine_.clear();
  countUnicSet_ = 1;
}

}  // namespace s21
