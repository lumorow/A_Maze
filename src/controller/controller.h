#pragma once

#include "../model/cave/cave.h"
#include "../model/maze/maze.h"
#include "../model/maze/solver.h"

namespace s21 {
class Controller {
 public:
  Controller(Maze* maze, Cave* cave, Solver* solver)
      : maze_(maze), cave_(cave), solver_(solver){};
  ~Controller() = default;

  int GetRowsMaze() { return maze_->GetRows(); }
  int GetColsMaze() { return maze_->GetCols(); }
  Matrix& GetHeightMatrix() { return maze_->GetHeightMatrix(); }
  Matrix& GetWidthtMatrix() { return maze_->GetWidthtMatrix(); }
  void ParseFileMaze(const std::string& fileName) {
    maze_->ParseFileMaze(fileName);
  }
  int GetRowsCave() { return cave_->GetRows(); }
  int GetColsCave() { return cave_->GetCols(); }
  void SetLimitsBD(int birth, int death);
  void SetTime(int time);
  void GenerateRandomMap(int rows, int cols, int chance);
  void MapUpd();
  void ReadFile(const std::string& fileName);
  Matrix& MapCave() { return cave_->MapCave(); }
  std::vector<Point> SolveMaze(Point start, Point end);
  void GenerateMaze(int rows, int cols);

 private:
  Maze* maze_;
  Cave* cave_;
  Solver* solver_;
};
}  // namespace s21
