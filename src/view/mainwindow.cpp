#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(s21::Controller *controller, QWidget *parent)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      controller_(controller),
      timer_(new QTimer) {
  ui_->setupUi(this);
  ui_->widget->GetController(controller_);
  connect(timer_, SIGNAL(timeout()), this, SLOT(on_OneStepCave_clicked()));
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::on_OpenFileMaze_clicked() {
  QString filepath = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt");
  if (!filepath.isEmpty()) {
    if (!controller_->Parsing(filepath.toStdString())) {
      ui_->lenght_maze_Slider->setSliderPosition(
          controller_->GetObject().GetRows());
      ui_->height_maze_Slider->setSliderPosition(
          controller_->GetObject().GetCols());
      ui_->widget->update();
    } else {
      ErrorMessage();
    }
  }
}

void MainWindow::on_OpenFileCave_clicked() {
  QString filepath = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt");
  if (!filepath.isEmpty()) {
    if (!controller_->ParsingCave(filepath.toStdString())) {
      ui_->lenght_spinBox->setValue(controller_->GetColsCave());
      ui_->height_spinBox->setValue(controller_->GetRowsCave());
      ui_->lenght_Slider->setSliderPosition(controller_->GetColsCave());
      ui_->height_Slider->setSliderPosition(controller_->GetRowsCave());
      ui_->widget->update();
    } else {
      ErrorMessage();
    }
  }
}

void MainWindow::ErrorMessage() {
  QMessageBox *error = new QMessageBox;
  error->setMaximumSize(2500, 2500);
  error->setWindowTitle("Fatal!");
  error->setText("Error input!");
  error->show();
  controller_->ClearMaze();
  controller_->ClearCave();
}

void MainWindow::on_GenerateCave_clicked() {
  controller_->SetRowsAndColsCave(ui_->height_spinBox->text().toInt(),
                                  ui_->lenght_spinBox->text().toInt());
  controller_->GenerateCave();
  ui_->widget->update();
}

void MainWindow::on_OneStepCave_clicked() {
  if (controller_->GetColsCave() && controller_->GetRowsCave()) {
    controller_->OneStep();
    ui_->widget->update();
  }
}

void MainWindow::on_AutoStepCave_clicked() {
  if (timer_->isActive()) {
    ui_->AutoStepCave->setText("Auto");
    timer_->stop();
  } else {
    ui_->AutoStepCave->setText("Stop");
    timer_->start(ui_->milliseconds_spinBox->text().toInt());
  }
}

void MainWindow::on_limit_birth_Slider_valueChanged(int value) {
  ui_->limit_birth_spinBox->setValue(value);
  controller_->SetLimitBirth(ui_->limit_birth_spinBox->text().toInt());
}

void MainWindow::on_limit_of_death_Slider_valueChanged(int value) {
  ui_->limit_of_death_spinBox->setValue(value);
  controller_->SetLimitOfDeath(ui_->limit_of_death_spinBox->text().toInt());
}

void MainWindow::on_initialization_chance_Slider_valueChanged(int value) {
  ui_->initialization_chance_spinBox->setValue(value);
  controller_->SetInitChance(
      ui_->initialization_chance_spinBox->text().toInt());
}

void MainWindow::on_milliseconds_Slider_valueChanged(int value) {
  ui_->milliseconds_spinBox->setValue(value);
  timer_->setInterval(ui_->milliseconds_spinBox->text().toInt());
}

void MainWindow::on_tabWidget_currentChanged(int index) {
  if (!index) {
    controller_->ClearCave();
    if (timer_->isActive()) {
      timer_->stop();
      ui_->AutoStepCave->setText("Auto");
    }
  } else if (index == 1) {
    controller_->ClearMaze();
  }
  ui_->widget->update();
}

void MainWindow::on_pushButtonDeletePath_clicked() { ui_->widget->ClearPath(); }

void MainWindow::on_pushButtonGenerate_clicked() {
  ui_->widget->ClearPath();
  controller_->GenerateMaze(ui_->height_maze_spinBox->text().toInt(),
                            ui_->lenght_maze_spinBox->text().toInt());
  ui_->widget->update();
}

void MainWindow::on_SaveFileCave_clicked() {
  if (controller_->GetColsCave() && controller_->GetRowsCave()) {
    QString path = QFileDialog::getSaveFileName(
        this, "Open a file", QDir::homePath(), "TXT (*.txt)");
    controller_->SaveFileCave(path.toStdString());
  }
}

void MainWindow::on_SaveFIleMaze_clicked() {
  if (controller_->GetObject().GetCols() &&
      controller_->GetObject().GetRows()) {
    QString path = QFileDialog::getSaveFileName(
        this, "Open a file", QDir::homePath(), "TXT (*.txt)");
    controller_->SaveFileMaze(path.toStdString());
  }
}

void MainWindow::on_lenght_maze_Slider_valueChanged(int value) {
  ui_->lenght_maze_spinBox->setValue(value);
}

void MainWindow::on_height_maze_Slider_valueChanged(int value) {
  ui_->height_maze_spinBox->setValue(value);
}

void MainWindow::on_lenght_Slider_valueChanged(int value) {
  ui_->lenght_spinBox->setValue(value);
}

void MainWindow::on_height_Slider_valueChanged(int value) {
  ui_->height_spinBox->setValue(value);
}
}  // namespace s21
