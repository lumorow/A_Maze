#include "controller.h"
using namespace s21;

void Controller::SetLimitsBD(int birth, int death) {
  cave_->SetLimitsBD(birth, death);
}

void Controller::SetTime(int time) { cave_->SetTime(time); }

void Controller::GenerateRandomMap(int rows, int cols, int chance) {
  cave_->GenerateRandomMap(rows, cols, chance);
}

void Controller::MapUpd() { cave_->UpdateMap(); }

void Controller::ReadFile(const std::string &fileName) {
  cave_->ReadFile(fileName);
}

std::vector<Point> Controller::SolveMaze(Point start, Point end) {
  solver_->GetMaze(maze_);
  auto vec = solver_->SolveMaze(start, end);
  return vec;
}

void Controller::GenerateMaze(int rows, int cols) {
  maze_->GenerateMaze(rows, cols);
}
