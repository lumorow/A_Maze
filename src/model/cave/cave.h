#pragma once
#include <stdlib.h>

#include <ctime>
#include <fstream>
#include <iostream>
#include <random>

#include "../matrix.h"

namespace s21 {

enum cell { DEAD, ALIVE };

class Cave {
 public:
  Cave() = default;
  void ReadFile(const std::string &fileName);
  void SetLimitsBD(int birth, int death);
  int GetRows() { return rows_; }
  int GetCols() { return cols_; }
  Matrix &MapCave() { return map_; };
  int BirthOrDeath(int currentI, int currentJ, int aliveDead);
  void GenerateRandomMap(int rows, int cols, int chance);
  void UpdateMap();
  void SetTime(int time);

 private:
  Matrix map_;
  int time_;
  int rows_{0};
  int cols_{0};
  int birthLimit_{0};
  int deathLimit_{0};

  void SizeParse(std::ifstream &file);
  void MapParse(std::ifstream &file);
  void CreateMap();
};
}  // namespace s21
