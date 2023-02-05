#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

#include "../controller/controller.h"
#include "caveform.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_UploadFile_clicked();
  void on_actionCave_menu_triggered();

  void on_Generation_clicked();

 private:
  Ui::MainWindow *ui;
  CaveForm *cave;
  Controller *controller_;
};
}  // namespace s21
#endif  // MAINWINDOW_H
