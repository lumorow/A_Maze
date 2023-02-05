#include "mainwindow.h"

#include "caveform.h"
#include "ui_caveform.h"
#include "ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(controller) {
  ui->setupUi(this);
  ui->widget->SetController(controller);
  cave = new CaveForm(controller);
}

MainWindow::~MainWindow() {
  delete ui;
  delete cave;
}

void MainWindow::on_UploadFile_clicked() {
  QString str =
      QFileDialog::getOpenFileName(this, "open file", "/src/", "*.txt");
  if (!str.isEmpty()) {
    ui->widget->DrawMaze(str);
    QList<QString> name = str.split('/');
    ui->label->setText(name.last());
  }
}

void MainWindow::on_actionCave_menu_triggered() {
  cave = new CaveForm(controller_);
  cave->show();
}

void MainWindow::on_Generation_clicked() {
  ui->widget->GenerateMaze(ui->Height->value(), ui->Width->value());
}

}  // namespace s21
