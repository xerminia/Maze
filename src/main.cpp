#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Maze maze;
  s21::Cave cave;
  s21::Controller controller(&maze, &cave);
  s21::MainWindow view(&controller);
  view.setWindowTitle("MAZE");
  view.show();
  return a.exec();
}
