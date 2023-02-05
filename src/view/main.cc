#include <QApplication>

#include "../controller/controller.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Maze maze;
  s21::Cave cavev;
  s21::Solver solver;
  s21::Controller controller(&maze, &cavev, &solver);
  s21::MainWindow view(&controller);
  view.show();
  return a.exec();
}
