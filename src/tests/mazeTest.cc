#include <iostream>

#include "../model/maze/maze.h"
#include "../model/maze/solver.h"
#include "caveTest.h"
#include "gtest/gtest.h"

TEST(maze, createMaze) {
  s21::Maze mazeTest;
  mazeTest.ParseFileMaze("model/maze/second.txt");
  ASSERT_EQ(mazeTest.GetCols(), 2);
  ASSERT_EQ(mazeTest.GetRows(), 4);
  Matrix height = mazeTest.GetHeightMatrix();
  Matrix width = mazeTest.GetWidthtMatrix();
  Matrix testH(4, 2);
  testH(0, 0) = 0;
  testH(0, 1) = 1;
  testH(1, 0) = 1;
  testH(1, 1) = 1;
  testH(2, 0) = 0;
  testH(2, 1) = 1;
  testH(3, 0) = 0;
  testH(3, 1) = 1;
  Matrix testW(4, 2);
  testW(0, 0) = 1;
  testW(0, 1) = 0;
  testW(1, 0) = 0;
  testW(1, 1) = 0;
  testW(2, 0) = 1;
  testW(2, 1) = 0;
  testW(3, 0) = 1;
  testW(3, 1) = 1;

  for (int i = 0; i < mazeTest.GetRows(); i++) {
    for (int j = 0; j < mazeTest.GetCols(); j++) {
      ASSERT_EQ(height(i, j), testH(i, j));
      ASSERT_EQ(width(i, j), testW(i, j));
    }
  }
}

TEST(maze, solveMaze) {
  s21::Maze mazeTest;
  mazeTest.ParseFileMaze("model/maze/second.txt");
  s21::Solver solver;
  solver.GetMaze(&mazeTest);
  std::vector<s21::Point> points = solver.SolveMaze({0, 0}, {1, 0});
  ASSERT_EQ(points[0].i, 1);
  ASSERT_EQ(points[0].j, 0);
  ASSERT_EQ(points[1].i, 2);
  ASSERT_EQ(points[1].j, 0);
  ASSERT_EQ(points[2].i, 2);
  ASSERT_EQ(points[2].j, 1);
  ASSERT_EQ(points[3].i, 1);
  ASSERT_EQ(points[3].j, 1);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
