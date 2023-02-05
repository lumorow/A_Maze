#include "cave.h"
namespace s21 {

void Cave::ReadFile(const std::string &fileName) {
  std::ifstream file(fileName);
  if (!file) {
    throw std::invalid_argument("No file");
  }
  SizeParse(file);
  CreateMap();
  MapParse(file);
}

void Cave::SetTime(int time) { time_ = time; }

void Cave::CreateMap() { map_ = Matrix(rows_, cols_); }

void Cave::SizeParse(std::ifstream &file) {
  std::string lineSizeMatrix = "";
  getline(file, lineSizeMatrix);
  size_t idx = 0;
  rows_ = std::stoi(lineSizeMatrix, &idx);
  cols_ = std::stoi(lineSizeMatrix.substr(idx + 1));
  if (rows_ > 50 || cols_ > 50) {
    throw std::invalid_argument("Incorrect size");
  }
}

void Cave::MapParse(std::ifstream &file) {
  for (int i = 0; i < rows_; i++) {
    std::string lineDataMatrix;
    getline(file, lineDataMatrix);
    for (int j = 0, step = 0; j < cols_; j++, step += 2) {
      int check = 0;
      check = std::stoi(lineDataMatrix.substr(step));
      if (check == 0 || check == 1) {
        map_(i, j) = check;
      } else {
        throw std::invalid_argument("Incorrect value");
      }
    }
  }
}

int Cave::BirthOrDeath(int currentI, int currentJ, int aliveDead) {
  int countAlive = 0;
  for (int i = currentI - 1, stepRows = 0; stepRows < 3; i++, stepRows++) {
    for (int j = currentJ - 1, stepCols = 0; stepCols < 3; j++, stepCols++) {
      if ((i >= 0 && i < rows_) && (j >= 0 && j < cols_)) {
        if (!(stepCols == 1 && stepRows == 1)) {
          if (map_(i, j) == ALIVE) {
            countAlive++;
          }
        }
      }
    }
  }
  if (aliveDead == ALIVE && countAlive < deathLimit_) {
    aliveDead = DEAD;
  } else if (aliveDead == DEAD && countAlive > birthLimit_) {
    aliveDead = ALIVE;
  }
  return aliveDead;
}

void Cave::UpdateMap() {
  Matrix oldMap = map_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      map_(i, j) = BirthOrDeath(i, j, oldMap(i, j));
    }
  }
}

void Cave::SetLimitsBD(int birth, int death) {
  birthLimit_ = birth;
  deathLimit_ = death;
}

void Cave::GenerateRandomMap(int rows, int cols, int chance) {
  rows_ = rows;
  cols_ = cols;
  map_ = Matrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (rand() % 100 < chance)
        map_(i, j) = 1;
      else
        map_(i, j) = 0;
    }
  }
}

}  // namespace s21
