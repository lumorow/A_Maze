#ifndef MAZE_H
#define MAZE_H

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../matrix.h"

namespace s21 {
class Maze {
 private:
  std::fstream fout_;
  std::string line_;
  Matrix height_, width_;
  int height_matrix_{0}, width_matrix_{0}, countUnicSet_{1};
  std::vector<int> generatingLine_, element_;

 public:
  Maze() = default;
  ~Maze() = default;
  int GetRows() { return height_matrix_; }
  int GetCols() { return width_matrix_; }
  Matrix& GetHeightMatrix() { return height_; }
  Matrix& GetWidthtMatrix() { return width_; }
  void ParseFileMaze(const std::string& fileName);
  void GenerateMaze(int rows, int cols);

 private:
  void MazeSize();
  void MatrixAllocate(int height_matrix_, int width_matrix_);
  void FillMatrix(Matrix& matrix);
  bool GetRandomBoolValue();
  void SetZeroValues();
  void SetNewLine();
  void JoinSet(int index, int value);
  void AddWalls(int row);
  void AddVertical(int row);
  void AddHorizontal(int row);
  void CorrectLine(int j);
  void CorrectEndLine();
  void AddBottomLine();
  void ClearGenerator();
  int Count(int value);
  void CheckWalls(int row);
  int CalculateHorizontal(int element, int row);
};
}  // namespace s21
#endif  // MAZE_H
