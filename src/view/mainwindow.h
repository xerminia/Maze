#ifndef SRC_VIEW_MAINWINDOW_H_
#define SRC_VIEW_MAINWINDOW_H_

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include "mazewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow() = default;
  MainWindow(s21::Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_OpenFileMaze_clicked();
  void on_OpenFileCave_clicked();
  void on_GenerateCave_clicked();
  void on_OneStepCave_clicked();
  void on_AutoStepCave_clicked();
  void on_limit_birth_Slider_valueChanged(int value);
  void on_limit_of_death_Slider_valueChanged(int value);
  void on_initialization_chance_Slider_valueChanged(int value);
  void on_milliseconds_Slider_valueChanged(int value);
  void on_tabWidget_currentChanged(int index);
  void on_pushButtonDeletePath_clicked();
  void on_pushButtonGenerate_clicked();
  void on_SaveFileCave_clicked();
  void on_SaveFIleMaze_clicked();
  void on_lenght_maze_Slider_valueChanged(int value);
  void on_height_maze_Slider_valueChanged(int value);
  void on_lenght_Slider_valueChanged(int value);
  void on_height_Slider_valueChanged(int value);

 private:
  Ui::MainWindow *ui_;
  s21::Controller *controller_;
  QTimer *timer_;

 private:
  void ErrorMessage();
};
}  // namespace s21

#endif  // SRC_VIEW_MAINWINDOW_H_
