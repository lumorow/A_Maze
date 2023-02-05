#ifndef SOLVER_H
#define SOLVER_H

#include "maze.h"

namespace s21 {

struct Point {
  int i;
  int j;
  Point() : i(0), j(0) {}
  Point(int xval, int yval) : i(xval), j(yval) {}
};

class Solver {
 private:
  Matrix vertical_;
  Matrix horizontal_;
  Matrix helper_;
  int rows_;
  int cols_;
  int counter_;

 public:
  Solver() = default;
  void GetMaze(Maze* maze);
  std::vector<Point> SolveMaze(Point begin, Point end);

 private:
  bool CheckRightCell(const Point& point, int value);
  bool CheckLeftCell(const Point& point, int value);
  bool CheckTopCell(const Point& point, int value);
  bool CheckBottomCell(const Point& point, int value);
  bool CheckRight(const Point& point);
  bool CheckLeft(const Point& point);
  bool CheckTop(const Point& point);
  bool CheckBottom(const Point& point);
  void CheckPossible(int i, int j);
  void FillHelper();
  void SetValue(int i, int j);
  void NewStep();
  std::vector<Point> FindSolution(Point begin, Point end);
};
}  // namespace s21
#endif  // SOLVER_H
