#ifndef CAVEFORM_H
#define CAVEFORM_H

#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>
#include <QtGui/QImage>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QWidget>

#include "../controller/controller.h"
namespace Ui {
class CaveForm;
}
class CaveForm : public QMainWindow {
  Q_OBJECT

 public:
  explicit CaveForm(s21::Controller *controller, QWidget *parent = nullptr);
  ~CaveForm();

 private slots:
  void on_pushButton_clicked();
  void on_Step_clicked();
  void on_Generate_clicked();
  void on_Auto_clicked();

 private:
  Ui::CaveForm *ui;
  QTimer *timer;
  bool mode;
};

#endif  // CAVEFORM_H
