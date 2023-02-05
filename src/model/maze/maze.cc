#include "maze.h"

namespace s21 {

void Maze::MazeSize() {
  for (size_t i = 0; i < 1; i++) std::getline(fout_, line_);
  size_t pos = 0;
  height_matrix_ = stoi(line_, &pos);
  width_matrix_ = stoi(line_.substr(pos + 1), &pos);
  if (width_matrix_ > 50 || height_matrix_ > 50) {
    throw std::invalid_argument("Incorrect size");
  }
}

void Maze::MatrixAllocate(int height_matrix_, int width_matrix_) {
  height_ = Matrix(height_matrix_, width_matrix_);
  width_ = Matrix(height_matrix_, width_matrix_);
}

void Maze::ParseFileMaze(const std::string &fileName) {
  fout_ = std::fstream(fileName);
  if (!fout_.is_open()) throw std::invalid_argument("Wrong file name!");
  MazeSize();
  MatrixAllocate(height_matrix_, width_matrix_);
  FillMatrix(height_);
  std::getline(fout_, line_);
  FillMatrix(width_);
  fout_.close();
}

void Maze::FillMatrix(Matrix &matrix) {
  for (int i = 0; i < height_matrix_; i++) {
    std::getline(fout_, line_);
    size_t pos = 0;
    for (int j = 0; j < width_matrix_; j++) {
      int element = 0;
      element = stoi(line_.substr(pos + j));
      pos++;
      if (element == 0 || element == 1) {
        matrix(i, j) = element;
      } else {
        throw std::invalid_argument("Incorrect value");
      }
    }
  }
}
}  // namespace s21
