#ifndef MAZESCENE_H
#define MAZESCENE_H

#include <QGraphicsSceneMouseEvent>
#include <QtGui/QImage>
#include <QtGui/QKeyEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QWidget>

#include "../controller/controller.h"

class MazeScene : public QWidget {
  Q_OBJECT
 private:
  s21::Controller *controller_;
  QImage image_;
  double Width_{0}, Height_{0};
  QPoint startPoint_, endPoint_;
  int countstart = 0, countend = 0;
  s21::Point firstPoint_, secondPoint_;

 public:
  explicit MazeScene(QWidget *parent = nullptr);
  void SetController(s21::Controller *controller) { controller_ = controller; }
  void DrawMaze(QString filename);
  void ClearMaze();
  void GenerateMaze(int width, int height);

 private:
  void paintEvent(QPaintEvent *event) override;
  void drawScene();
  void mousePressEvent(QMouseEvent *event) override;
  QPoint ConvertCellToPoint(s21::Point pos);
  void ConvertPointToCell();
  void PathToDraw();
  void DrawToPointStart();
  void DrawToPointEnd();
};

#endif  // MAZESCENE_H
