#include "MazeScene.h"

MazeScene::MazeScene(QWidget *parent)
    : QWidget(parent),
      controller_(nullptr),
      image_(QSize(500, 500), QImage::Format_ARGB32) {}

void MazeScene::DrawMaze(QString filename) {
  try {
    controller_->ParseFileMaze(filename.toStdString());
    drawScene();
  } catch (std::exception &e) {
  }
}
void MazeScene::GenerateMaze(int width, int height) {
  ClearMaze();
  controller_->GenerateMaze(width, height);
  drawScene();
}

void MazeScene::ClearMaze() {
  image_.fill(QColor(0, 0, 0, 0));
  countstart = 0;
  countend = 0;
}

void MazeScene::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, image_, dirtyRect);
}

void MazeScene::drawScene() {
  ClearMaze();
  QPainter painter(&image_);
  painter.setPen(QPen(Qt::black, 2));
  painter.drawLine(0, 1, 500, 1);
  painter.drawLine(1, 500, 1, 0);
  Width_ = 500.0 / controller_->GetColsMaze();
  Height_ = 500.0 / controller_->GetRowsMaze();
  for (int i = 0; i < controller_->GetRowsMaze(); i++) {
    for (int j = 0; j < controller_->GetColsMaze(); j++) {
      int x0 = Width_ * j;
      int y0 = Height_ * i;
      int x1 = Width_ * (j + 1);
      int y1 = Height_ * (i + 1);
      if (controller_->GetHeightMatrix()(i, j)) {
        if (j + 1 == controller_->GetColsMaze()) {
          x0--;
          x1--;
        }
        painter.drawLine(x1, y0, x1, y1);
      }
      if (controller_->GetWidthtMatrix()(i, j)) {
        if (i + 1 == controller_->GetRowsMaze()) {
          y0--;
          y1--;
        }
        if (j + 1 == controller_->GetColsMaze()) {
          x0++;
          x1++;
        }
        painter.drawLine(x0, y1, x1, y1);
      }
    }
  }
  update();
}

void MazeScene::PathToDraw() {
  std::vector<s21::Point> path =
      controller_->SolveMaze(firstPoint_, secondPoint_);
  QPainter painter(&image_);
  for (size_t h = 0; h < path.size() - 1; h++) {
    painter.setPen(QPen(Qt::red, 3));
    painter.drawLine(ConvertCellToPoint(path[h]),
                     ConvertCellToPoint(path[h + 1]));
    painter.drawLine(startPoint_.x(), startPoint_.y(),
                     firstPoint_.j * Width_ + Width_ / 2,
                     firstPoint_.i * Height_ + Height_ / 2);
    painter.drawLine(endPoint_.x(), endPoint_.y(),
                     secondPoint_.j * Width_ + Width_ / 2,
                     secondPoint_.i * Height_ + Height_ / 2);
  }
}

void MazeScene::DrawToPointStart() {
  QPainter painter(&image_);
  painter.setPen(QPen(Qt::red, 5));
  painter.drawEllipse(startPoint_.x(), startPoint_.y(), 5, 5);
  ConvertPointToCell();
}

void MazeScene::DrawToPointEnd() {
  QPainter painter(&image_);
  painter.setPen(QPen(Qt::red, 5));
  painter.drawEllipse(endPoint_.x(), endPoint_.y(), 5, 5);
  ConvertPointToCell();
}

void MazeScene::ConvertPointToCell() {
  firstPoint_.i = startPoint_.y() / Height_;
  firstPoint_.j = startPoint_.x() / Width_;
  secondPoint_.i = endPoint_.y() / Height_;
  secondPoint_.j = endPoint_.x() / Width_;
}

void MazeScene::mousePressEvent(QMouseEvent *event) {
  if (controller_->GetRowsMaze() != 0 && controller_->GetColsMaze() != 0) {
    if (event->button() == Qt::LeftButton) {
      startPoint_ = event->pos();
      countstart++;
      if (countstart == 1) {
        DrawToPointStart();
      }
    }
    if (event->button() == Qt::RightButton) {
      endPoint_ = event->pos();
      countend++;
      if (countend == 1) {
        DrawToPointEnd();
      }
    }
    if (countend == 1 && countstart == 1) {
      PathToDraw();
    }
  }
  update();
}

QPoint MazeScene::ConvertCellToPoint(s21::Point pos) {
  int i = pos.i * Height_ + Height_ / 2;
  int j = pos.j * Width_ + Width_ / 2;
  return QPoint(j, i);
}
