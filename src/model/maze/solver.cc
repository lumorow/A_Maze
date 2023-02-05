#include "solver.h"

namespace s21 {

void Solver::GetMaze(Maze* maze) {
  horizontal_ = maze->GetWidthtMatrix();
  vertical_ = maze->GetHeightMatrix();
  rows_ = maze->GetRows();
  cols_ = maze->GetCols();
  counter_ = 0;
  helper_ = Matrix(rows_, cols_);
  FillHelper();
}

bool Solver::CheckRightCell(const Point& point, int value) {
  return point.j < cols_ - 1 && helper_(point.i, point.j + 1) == value &&
         vertical_(point.i, point.j) == 0;
}

bool Solver::CheckLeftCell(const Point& point, int value) {
  return point.j != 0 && helper_(point.i, point.j - 1) == value;
}

bool Solver::CheckTopCell(const Point& point, int value) {
  return point.i != 0 && helper_(point.i - 1, point.j) == value;
}

bool Solver::CheckBottomCell(const Point& point, int value) {
  return point.i < rows_ - 1 && helper_(point.i + 1, point.j) == value;
}

bool Solver::CheckRight(const Point& point) {
  return point.j < cols_ - 1 && vertical_(point.i, point.j) == 0;
}

bool Solver::CheckLeft(const Point& point) {
  return point.j != 0 && vertical_(point.i, point.j - 1) == 0;
}

bool Solver::CheckTop(const Point& point) {
  return point.i != 0 && horizontal_(point.i - 1, point.j) == 0;
}

bool Solver::CheckBottom(const Point& point) {
  return point.i < rows_ - 1 && horizontal_(point.i, point.j) == 0;
}

std::vector<Point> Solver::SolveMaze(Point begin, Point end) {
  SetValue(begin.i, begin.j);
  while (helper_(end.i, end.j) == -1) {
    NewStep();
  }
  return FindSolution(begin, end);
}

std::vector<Point> Solver::FindSolution(Point begin, Point end) {
  std::vector<Point> result;
  int i = end.i;
  int j = end.j;
  result.push_back({i, j});
  while (begin.i != i || begin.j != j) {
    Point currentPoint(i, j);
    int currentStep = helper_(i, j) - 1;
    if (CheckRight(currentPoint) &&
        helper_(currentPoint.i, currentPoint.j + 1) == currentStep) {
      j++;
    } else if (CheckLeft(currentPoint) &&
               helper_(currentPoint.i, currentPoint.j - 1) == currentStep) {
      j--;
    } else if (CheckBottom(currentPoint) &&
               helper_(currentPoint.i + 1, currentPoint.j) == currentStep) {
      i++;
    } else if (CheckTop(currentPoint) &&
               helper_(currentPoint.i - 1, currentPoint.j) == currentStep) {
      i--;
    }
    result.push_back({i, j});
  }
  return result;
}

void Solver::NewStep() {
  int prevStep = counter_;
  counter_++;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (helper_(i, j) == prevStep) CheckPossible(i, j);
    }
  }
}

void Solver::CheckPossible(int i, int j) {
  Point currentPoint(i, j);
  if (CheckRight(currentPoint)) SetValue(i, j + 1);
  if (CheckLeft(currentPoint)) SetValue(i, j - 1);
  if (CheckBottom(currentPoint)) SetValue(i + 1, j);
  if (CheckTop(currentPoint)) SetValue(i - 1, j);
}

void Solver::SetValue(int i, int j) {
  if (helper_(i, j) == -1) {
    helper_(i, j) = counter_;
  }
}

void Solver::FillHelper() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      helper_(i, j) = -1;
    }
  }
}

}  // namespace s21
