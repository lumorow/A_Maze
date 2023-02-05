#ifndef CAVE_TEST_H
#define CAVE_TEST_H

#include "../model/cave/cave.h"
#include "gtest/gtest.h"

TEST(back_create_cave, create_cave_rand_1) {
  s21::Cave caveTest;
  caveTest.GenerateRandomMap(50, 40, 0);
  ASSERT_EQ(caveTest.GetCols(), 40);
  ASSERT_EQ(caveTest.GetRows(), 50);
  Matrix testsMapCave = caveTest.MapCave();
  for (int i = 0; i < caveTest.GetRows(); i++) {
    for (int j = 0; j < caveTest.GetCols(); j++) {
      ASSERT_EQ(testsMapCave(i, j), 0);
    }
  }
}

TEST(back_create_cave, create_cave_rand_2) {
  s21::Cave caveTest;
  caveTest.GenerateRandomMap(33, 22, 100);
  ASSERT_EQ(caveTest.GetCols(), 22);
  ASSERT_EQ(caveTest.GetRows(), 33);
  Matrix testsMapCave = caveTest.MapCave();
  for (int i = 0; i < caveTest.GetRows(); i++) {
    for (int j = 0; j < caveTest.GetCols(); j++) {
      ASSERT_EQ(testsMapCave(i, j), 1);
    }
  }
}

TEST(back_create_cave, create_cave_file_1) {
  s21::Cave caveTest;
  caveTest.ReadFile("model/cave/cave_10x10.txt");
  ASSERT_EQ(caveTest.GetCols(), 10);
  ASSERT_EQ(caveTest.GetRows(), 10);
  Matrix testsMapCave = caveTest.MapCave();
  for (int i = 0; i < caveTest.GetRows(); i++) {
    for (int j = 0; j < caveTest.GetCols(); j++) {
      if (fmod(j, 2)) {
        ASSERT_EQ(testsMapCave(i, j), 0);
      } else {
        ASSERT_EQ(testsMapCave(i, j), 1);
      }
    }
  }
}

TEST(back_create_cave, cave_update_1) {
  s21::Cave caveTest;
  caveTest.ReadFile("model/cave/cave_10x10.txt");
  caveTest.SetLimitsBD(0, 0);
  caveTest.UpdateMap();
  Matrix testsMapCave = caveTest.MapCave();
  for (int i = 0; i < caveTest.GetRows(); i++) {
    for (int j = 0; j < caveTest.GetCols(); j++) {
      ASSERT_EQ(testsMapCave(i, j), 1);
    }
  }
}

TEST(back_create_cave, cave_update_2) {
  s21::Cave caveTest;
  caveTest.ReadFile("model/cave/cave_5x5.txt");
  caveTest.SetLimitsBD(1, 3);
  caveTest.UpdateMap();
  Matrix testsMapCave = caveTest.MapCave();
  ASSERT_EQ(testsMapCave(0, 0), 1);
  ASSERT_EQ(testsMapCave(0, 1), 1);
  ASSERT_EQ(testsMapCave(1, 0), 1);
  ASSERT_EQ(testsMapCave(1, 1), 1);
  ASSERT_EQ(testsMapCave(0, 4), 0);
  ASSERT_EQ(testsMapCave(2, 0), 1);
  ASSERT_EQ(testsMapCave(2, 1), 1);
  ASSERT_EQ(testsMapCave(3, 0), 0);
  ASSERT_EQ(testsMapCave(3, 3), 1);
  ASSERT_EQ(testsMapCave(4, 4), 1);
}

#endif  // CAVE_TEST_H
