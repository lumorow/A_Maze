#ifndef CAVESCENE_H
#define CAVESCENE_H

#include <QtGui/QImage>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QWidget>

#include "../controller/controller.h"

class CaveScene : public QWidget {
  Q_OBJECT
 public:
  explicit CaveScene(QWidget *parent = nullptr);
  void SetController(s21::Controller *controller) { controller_ = controller; }
  void DrawCave(QString filename);
  void ClearCave();
  void setLimitsBD(int birth, int death);
  void generateRandomMap(int rows, int cols, int chance);

 private:
  s21::Controller *controller_;
  QImage image_cave;
  double Width_, Height_;

 private:
  void paintEvent(QPaintEvent *event) override;
  void DrawCaveScene();
};

#endif  // CAVESCENE_H
