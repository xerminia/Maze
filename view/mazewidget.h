#ifndef SRC_VIEW_MAZEWIDGET_H_
#define SRC_VIEW_MAZEWIDGET_H_

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

#include "controller/controller.h"

namespace s21 {
class MazeWidget : public QWidget {
  Q_OBJECT
 public:
  MazeWidget() = default;
  explicit MazeWidget(QWidget *parent = nullptr);
  ~MazeWidget() = default;

  inline void GetController(s21::Controller *control) { controller_ = control; }
  void ClearPath();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;

 private:
  s21::Controller *controller_;
  int size_cols_{}, size_rows_{};
  bool mouse_left_click_, mouse_right_click_;

 private:
  void DrawMaze();
  void DrawCave();
  void DrawPath();
  void DrawElipse(const int &i, const int &j);
  bool CheckDrawMaze();
  bool CheckDrawCave();
};
}  // namespace s21

#endif  // SRC_VIEW_MAZEWIDGET_H_
