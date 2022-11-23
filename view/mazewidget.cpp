#include "mazewidget.h"

namespace s21 {
MazeWidget::MazeWidget(QWidget *parent)
    : QWidget{parent}, mouse_left_click_(false), mouse_right_click_(false) {}

void MazeWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  if (CheckDrawMaze()) {
    size_cols_ = 500 / controller_->GetObject().GetCols();
    size_rows_ = 500 / controller_->GetObject().GetRows();
    DrawMaze();
    if (mouse_left_click_) {
      DrawElipse(controller_->GetObject().GetBeginI(),
                 controller_->GetObject().GetBeginJ());
    }
    if (mouse_right_click_) {
      DrawElipse(controller_->GetObject().GetEndI(),
                 controller_->GetObject().GetEndJ());
    }
    if (mouse_left_click_ && mouse_right_click_ &&
        controller_->GetObject().GetFinalPath().size() &&
        controller_->ShortestPathGeneration() == true)
      DrawPath();
  } else if (CheckDrawCave()) {
    size_cols_ = 500 / controller_->GetColsCave();
    size_rows_ = 500 / controller_->GetRowsCave();
    DrawCave();
  }
}

void MazeWidget::DrawMaze() {
  QPainter painter(this);
  {
    painter.setBrush(QBrush(QColor(113, 144, 124), Qt::SolidPattern));
    painter.drawRect(0, 0, size_cols_ * controller_->GetObject().GetCols(),
                     size_rows_ * controller_->GetObject().GetRows());
  }
  painter.setPen(QPen(QBrush(QColor(247, 213, 79), Qt::SolidPattern), 2));
  painter.drawEllipse(0, 1, size_cols_ * controller_->GetObject().GetCols(), 1);
  painter.drawEllipse(1, 0, 1, size_rows_ * controller_->GetObject().GetRows());
  for (size_t i = 0; i < controller_->GetObject().GetRows(); i++) {
    for (size_t j = 0; j < controller_->GetObject().GetCols(); j++) {
      int x0 = size_cols_ * j;
      int y0 = size_rows_ * i;
      int x1 = size_cols_ * (j + 1);
      int y1 = size_rows_ * (i + 1);
      if (controller_->GetObject().GetRightWalls()[i][j]) {
        if (j + 1 == controller_->GetObject().GetCols()) {
          x0--;
          x1--;
        }
        painter.drawLine(x1, y0, x1, y1);
      }
      if (controller_->GetObject().GetDownWalls()[i][j]) {
        if (i + 1 == controller_->GetObject().GetRows()) {
          y1--;
        }
        if (j + 1 == controller_->GetObject().GetCols()) {
          x0++;
          x1++;
        }
        painter.drawLine(x0, y1, x1, y1);
      }
    }
  }
}

void MazeWidget::DrawCave() {
  QPainter painter(this);
  for (size_t i = 0; i < controller_->GetRowsCave(); i++) {
    for (size_t j = 0; j < controller_->GetColsCave(); j++) {
      if (controller_->GetValueCave(i, j)) {
        painter.setPen(QPen(Qt::black));
        painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
        painter.drawRect(j * size_cols_, i * size_rows_, size_cols_,
                         size_rows_);
      } else {
        painter.setPen(QPen(Qt::white));
        painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
        painter.drawRect(j * size_cols_, i * size_rows_, size_cols_,
                         size_rows_);
      }
    }
  }
}

void MazeWidget::DrawPath() {
  QPainter painter(this);
  painter.setPen(QPen(QBrush(QColor(223, 238, 234), Qt::SolidPattern), 2));

  int x = 1;
  int i = controller_->GetObject().GetBeginI();
  int j = controller_->GetObject().GetBeginJ();

  while (x != controller_->GetObject()
                  .GetFinalPath()[controller_->GetObject().GetEndI()]
                                 [controller_->GetObject().GetEndJ()]) {
    if (i < (int)controller_->GetObject().GetRows() - 1 &&
        controller_->GetObject().GetFinalPath()[i + 1][j] == x + 1) {
      painter.drawLine(j * size_cols_ + size_cols_ / 2,
                       i * size_rows_ + size_rows_ / 2,
                       j * size_cols_ + size_cols_ / 2,
                       (i + 1) * size_rows_ + size_rows_ / 2);
      i++;
    } else if (j < (int)controller_->GetObject().GetCols() - 1 &&
               controller_->GetObject().GetFinalPath()[i][j + 1] == x + 1) {
      painter.drawLine(j * size_cols_ + size_cols_ / 2,
                       i * size_rows_ + size_rows_ / 2,
                       (j + 1) * size_cols_ + size_cols_ / 2,
                       i * size_rows_ + size_rows_ / 2);
      j++;
    } else if (i > 0 &&
               controller_->GetObject().GetFinalPath()[i - 1][j] == x + 1) {
      painter.drawLine(j * size_cols_ + size_cols_ / 2,
                       i * size_rows_ + size_rows_ / 2,
                       j * size_cols_ + size_cols_ / 2,
                       (i - 1) * size_rows_ + size_rows_ / 2);
      i--;
    } else if (j > 0 &&
               controller_->GetObject().GetFinalPath()[i][j - 1] == x + 1) {
      painter.drawLine(j * size_cols_ + size_cols_ / 2,
                       i * size_rows_ + size_rows_ / 2,
                       (j - 1) * size_cols_ + size_cols_ / 2,
                       i * size_rows_ + size_rows_ / 2);
      j--;
    }
    x++;
  }
}

void MazeWidget::mousePressEvent(QMouseEvent *event) {
  if (!controller_->GetObject().GetRows() ||
      !controller_->GetObject().GetCols())
    return;

  int i = (int)event->position().y() / size_rows_;
  int j = (int)event->position().x() / size_cols_;

  if (i >= (int)controller_->GetObject().GetRows() ||
      j >= (int)controller_->GetObject().GetCols())
    return;

  if (event->button() == Qt::LeftButton) {
    if (mouse_left_click_ == true &&
        controller_->GetObject().GetBeginI() == i &&
        controller_->GetObject().GetBeginJ() == j) {
      mouse_left_click_ = false;
    } else {
      mouse_left_click_ = true;
      controller_->SetBeginI(i);
      controller_->SetBeginJ(j);
    }
  } else if (event->button() == Qt::RightButton) {
    if (mouse_right_click_ == true && controller_->GetObject().GetEndI() == i &&
        controller_->GetObject().GetEndJ() == j) {
      mouse_right_click_ = false;
    } else {
      mouse_right_click_ = true;
      controller_->SetEndI(i);
      controller_->SetEndJ(j);
    }
  }

  if (mouse_left_click_ == true && mouse_right_click_ == true) {
    controller_->ShortestPathGeneration();
  }
  update();
}

void MazeWidget::DrawElipse(const int &i, const int &j) {
  QPainter painter(this);
  painter.setPen(QPen(QBrush(QColor(223, 238, 234), Qt::SolidPattern), 2));
  painter.setBrush(QBrush(QColor(223, 238, 234), Qt::SolidPattern));
  painter.drawEllipse(j * size_cols_ + size_cols_ / 4,
                      i * size_rows_ + size_rows_ / 4, size_cols_ / 2,
                      size_rows_ / 2);
}

void MazeWidget::ClearPath() {
  mouse_left_click_ = false;
  mouse_right_click_ = false;
  update();
}

bool MazeWidget::CheckDrawMaze() {
  return controller_->GetObject().GetDownWalls().size() &&
         controller_->GetObject().GetRightWalls().size();
}

bool MazeWidget::CheckDrawCave() {
  return controller_->GetColsCave() && controller_->GetRowsCave();
}
}  // namespace s21
