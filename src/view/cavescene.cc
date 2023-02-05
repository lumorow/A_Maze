#include "cavescene.h"

CaveScene::CaveScene(QWidget *parent)
    : QWidget(parent), image_cave(QSize(501, 501), QImage::Format_ARGB32) {
  ClearCave();
}

void CaveScene::DrawCave(QString filename) {
  try {
    controller_->ReadFile(filename.toStdString());
    DrawCaveScene();
  } catch (std::exception &e) {
  }
}

void CaveScene::ClearCave() { image_cave.fill(QColor(0, 0, 0, 0)); }

void CaveScene::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, image_cave, dirtyRect);
}

void CaveScene::DrawCaveScene() {
  ClearCave();
  QPainter painter(&image_cave);
  Matrix caveMap = controller_->MapCave();
  Width_ = 500.0 / controller_->GetColsCave();
  Height_ = 500.0 / controller_->GetRowsCave();
  for (int i = 0; i < controller_->GetRowsCave(); i++) {
    for (int j = 0; j < controller_->GetColsCave(); j++) {
      if (caveMap(i, j) == 1) {
        int x = Width_ * j;
        int y = Height_ * i;
        painter.setBrush(Qt::red);
        painter.setPen(Qt::red);
        painter.drawRect(x, y, Width_, Height_);
      }
    }
  }
  painter.setPen(QPen(Qt::black, 2));
  painter.drawLine(0, 0, 0, 501);
  painter.drawLine(0, 501, 501, 501);
  painter.drawLine(501, 501, 501, 0);
  painter.drawLine(0, 0, 501, 0);
  update();
}

void CaveScene::setLimitsBD(int birth, int death) {
  controller_->SetLimitsBD(birth, death);
  controller_->MapUpd();
  DrawCaveScene();
}

void CaveScene::generateRandomMap(int rows, int cols, int chance) {
  controller_->GenerateRandomMap(rows, cols, chance);
  DrawCaveScene();
}
