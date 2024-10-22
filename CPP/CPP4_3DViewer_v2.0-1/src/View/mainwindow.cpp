#include "mainwindow.h"

#include <QApplication>
#include <QImage>
#include <QImageWriter>
#include <QOpenGLWidget>
#include <QPainter>
#include <QSettings>
#include <cstdint>

#include "../Controller/Controller.h"
#include "draw.h"
#include "gif.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ReadSettings();
  SetFront();
}

MainWindow::~MainWindow() {
  SaveSettings();
  delete ui;
}

void MainWindow::on_name_button_clicked() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "Open a file", "/Users", "*.obj");
  file_name = fileName.toStdString();
  try {
    ui->openGLWidget->object.Read(file_name);
    ui->openGLWidget->object.Save();
  } catch (std::exception &e) {
    QMessageBox::warning(this, "Failed 😕", e.what());
  }

  ui->name_display->setText(" " + fileName.split('/').last());
  ui->num_edges->setText(QString::fromStdString(
      std::to_string(ui->openGLWidget->object.GetAreaSize())));
  ui->num_vert->setText(QString::fromStdString(
      std::to_string(ui->openGLWidget->object.GetVertexSize() / 3)));
  SetDefaultSettings();
  SetFront();
  ui->openGLWidget->update();
}

void MainWindow::SetDefaultSettings() {
  ui->openGLWidget->scale = 100;
  ui->openGLWidget->translation[0] = 0;
  ui->openGLWidget->translation[1] = 0;
  ui->openGLWidget->translation[2] = 0;
  ui->openGLWidget->rotation[0] = 0;
  ui->openGLWidget->rotation[1] = 0;
  ui->openGLWidget->rotation[2] = 0;
}

void MainWindow::on_screenshot_clicked() {
  QImage img(ui->openGLWidget->size(), QImage::Format_RGB32);
  QPainter painter(&img);
  QString temp = QCoreApplication::applicationDirPath();
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save file"), temp + "/images", tr("JPG (*.jpg);; BMP (*.bmp)"));
  ui->openGLWidget->render(&painter);
  if (img.save(fileName)) {
    QMessageBox msgBox;
    msgBox.setText("Saved successfully ✨");
    msgBox.exec();
  } else {
    QMessageBox::warning(this, "", "Failed 😕");
  }
}

void MainWindow::on_gif_clicked() {
  QString temp = QCoreApplication::applicationDirPath();
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save gif"), temp + "/images", tr("GIF (*.gif)"));
  if (!fileName.isEmpty()) {
    QImage img(ui->openGLWidget->size(), QImage::Format_RGBA8888);
    QPainter painter(&img);
    QTime dieTime;
    GifWriter gif;
    QByteArray ba = fileName.toLocal8Bit();
    const char *c_str = ba.data();
    GifBegin(&gif, c_str, 640, 480, 10);
    for (int i = 0; i < 50; ++i) {
      ui->openGLWidget->render(&painter);
      GifWriteFrame(&gif, img.scaled(640, 480).bits(), 640, 480, 10);
      dieTime = QTime::currentTime().addMSecs(100);
      while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    GifEnd(&gif);
    QMessageBox msgBox;
    msgBox.setText("Saved successfully ✨");
    msgBox.exec();
  } else {
    QMessageBox::warning(this, "", "Failed 😕");
  }
}

void MainWindow::on_change_x_valueChanged(int value) {  // смещение по x
  ui->openGLWidget->object.Shift(value - ui->openGLWidget->translation[0], 'x');
  ui->openGLWidget->translation[0] = value;  // сохранение в масив
  ui->howmuch_x->setText(QString::number(value));
  ui->openGLWidget->update();
}

void MainWindow::on_change_y_valueChanged(int value) {  // смещение по y
  ui->openGLWidget->object.Shift(value - ui->openGLWidget->translation[1], 'y');
  ui->openGLWidget->translation[1] = value;  // сохранение в масив
  ui->howmuch_y->setText(QString::number(value));
  ui->openGLWidget->update();
}

void MainWindow::on_change_z_valueChanged(int value) {  // смещение по z
  ui->openGLWidget->object.Shift(value - ui->openGLWidget->translation[2], 'z');
  ui->openGLWidget->translation[2] = value;  // сохранение в масив
  ui->openGLWidget->update();
}

void MainWindow::on_zoom_valueChanged(
    int value) {  // изменение размеров объекта
  ui->openGLWidget->object.Scaling(double(value) / ui->openGLWidget->scale);
  ui->howmuch_zoom->setText(QString::number(value));
  ui->openGLWidget->scale = value;
  ui->openGLWidget->update();
}

void MainWindow::on_spin_x_valueChanged(int value) {  // вращение по x
  ui->openGLWidget->object.Rotate((value - ui->openGLWidget->rotation[0]), 'x');
  ui->x_spin_is->setText(QString::number(value));
  ui->openGLWidget->rotation[0] = value;
  ui->openGLWidget->update();
}

void MainWindow::on_spin_y_valueChanged(int value) {  // вращение по y
  ui->openGLWidget->object.Rotate((value - ui->openGLWidget->rotation[1]), 'y');
  ui->y_spin_is->setText(QString::number(value));
  ui->openGLWidget->rotation[1] = value;
  ui->openGLWidget->update();
}

void MainWindow::on_spin_z_valueChanged(int value) {  // вращение по z
  ui->openGLWidget->object.Rotate((value - ui->openGLWidget->rotation[2]), 'z');
  ui->z_spin_is->setText(QString::number(value));
  ui->openGLWidget->rotation[2] = value;
  ui->openGLWidget->update();
}

void MainWindow::on_back_colour_clicked() {
  QColor colour = QColorDialog::getColor(Qt::white, this, "Select color:");
  ui->openGLWidget->colorBackground = colour;
  ui->openGLWidget->update();
}

void MainWindow::on_vert_colour_clicked() {
  QColor colour = QColorDialog::getColor(Qt::white, this, "Select color:");
  ui->openGLWidget->colorVertices = colour;
  ui->openGLWidget->update();
}

void MainWindow::on_Edges_colour_clicked() {
  QColor colour = QColorDialog::getColor(Qt::white, this, "Select color:");
  ui->openGLWidget->colorLines = colour;
  ui->openGLWidget->update();
}

void MainWindow::ReadSettings() {
  QString temp = QCoreApplication::applicationDirPath();
  QSettings settings(temp + "/settings.ini", QSettings::IniFormat);

  settings.beginGroup("Settings");  // начало списака начальных настроек

  ui->openGLWidget->colorBackground =
      settings.value("colorBackground", QColor(Qt::black)).value<QColor>();

  ui->openGLWidget->colorLines =
      settings.value("colorLines", QColor(Qt::white)).value<QColor>();

  ui->openGLWidget->colorVertices =
      settings.value("colorVertices", QColor(Qt::red)).value<QColor>();

  ui->openGLWidget->sizeLines = settings.value("sizeLines", 1.0).value<int>();

  ui->openGLWidget->projection = settings.value("projection", 1.0).value<int>();
  ui->openGLWidget->sizeVertices =
      settings.value("sizeVertices", 10.0).value<int>();

  ui->openGLWidget->typeLines = settings.value("typeLines", 0).value<int>();

  ui->openGLWidget->typeVertices =
      settings.value("typeVertices", 1).value<int>();

  // ui->openGLWidget->rotation[0] = settings.value("rotation0",
  // 0.0).value<int>(); ui->openGLWidget->rotation[1] =
  // settings.value("rotation1", 0.0).value<int>();
  // ui->openGLWidget->rotation[2] = settings.value("rotation2",
  // 0.0).value<int>();
  settings.endGroup();

  ui->openGLWidget->update();
}

void MainWindow::SetFront() {
  ui->change_x->setValue(ui->openGLWidget->translation[0]);
  ui->change_y->setValue(ui->openGLWidget->translation[1]);
  ui->change_z->setValue(ui->openGLWidget->translation[2]);

  ui->spin_x->setValue(ui->openGLWidget->rotation[0]);
  ui->spin_y->setValue(ui->openGLWidget->rotation[1]);
  ui->spin_z->setValue(ui->openGLWidget->rotation[2]);
  ui->zoom->setValue(ui->openGLWidget->scale);

  ui->thick->setValue(ui->openGLWidget->sizeLines);
  ui->size->setValue(ui->openGLWidget->sizeVertices);

  if (ui->openGLWidget->projection == 1)
    ui->parall_type->setChecked(true);
  else
    ui->central_type->setChecked(true);

  if (ui->openGLWidget->typeVertices == 0) {
    ui->is_no->setChecked(true);
  } else if (ui->openGLWidget->typeVertices == 1)
    ui->is_round->setChecked(true);
  else
    ui->is_square->setChecked(true);

  if (ui->openGLWidget->typeLines == 1)
    ui->dashed->setChecked(true);
  else
    ui->solid->setChecked(true);
}

void MainWindow::SaveSettings() {
  QString temp = QCoreApplication::applicationDirPath();
  QSettings settings(temp + "/settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");
  settings.setValue("colorBackground", ui->openGLWidget->colorBackground);
  settings.setValue("colorLines", ui->openGLWidget->colorLines);
  settings.setValue("colorVertices", ui->openGLWidget->colorVertices);
  settings.setValue("sizeLines", ui->openGLWidget->sizeLines);
  settings.setValue("sizeVertices", ui->openGLWidget->sizeVertices);
  settings.setValue("projection", ui->openGLWidget->projection);
  settings.setValue("typeLines", ui->openGLWidget->typeLines);
  settings.setValue("typeVertices", ui->openGLWidget->typeVertices);
  settings.endGroup();
}

void MainWindow::on_central_type_clicked() {
  ui->openGLWidget->projection = 0;
  ui->openGLWidget->update();  // рендер с новой проекцией
}

void MainWindow::on_parall_type_clicked() {
  ui->openGLWidget->projection = 1;
  ui->openGLWidget->update();  // рендер с новой проекцией
}

void MainWindow::on_solid_clicked() {
  ui->openGLWidget->typeLines = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_dashed_clicked() {
  ui->openGLWidget->typeLines = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_is_no_clicked() {
  ui->openGLWidget->typeVertices = 0;
  ui->openGLWidget->update();
}

void MainWindow::on_is_square_clicked() {
  ui->openGLWidget->typeVertices = 2;
  ui->openGLWidget->update();
}

void MainWindow::on_is_round_clicked() {
  ui->openGLWidget->typeVertices = 1;
  ui->openGLWidget->update();
}

void MainWindow::on_thick_valueChanged(int value) {
  ui->openGLWidget->sizeLines = value;
  ui->openGLWidget->update();
}

void MainWindow::on_size_valueChanged(int value) {
  ui->openGLWidget->sizeVertices = value;
  ui->openGLWidget->update();
}

void MainWindow::on_pushButton_clicked() {
  SetDefaultSettings();
  ui->change_x->setValue(0);
  ui->change_y->setValue(0);
  ui->change_z->setValue(0);
  ui->spin_x->setValue(0);
  ui->spin_y->setValue(0);
  ui->spin_z->setValue(0);
  ui->zoom->setValue(100);
  ui->openGLWidget->projection = 1;  // включена парал. проекция
  ui->parall_type->setChecked(true);  // чекбокс включен
  ui->is_round->setChecked(true);
  ui->openGLWidget->typeVertices = 0;
  ui->dashed->setChecked(true);
  ui->openGLWidget->typeLines = 0;
  ui->openGLWidget->sizeLines = 2;
  ui->openGLWidget->object.RestoreArea();
  ui->openGLWidget->object.RestoreVertex();
  SetFront();
  ui->openGLWidget->update();
}
