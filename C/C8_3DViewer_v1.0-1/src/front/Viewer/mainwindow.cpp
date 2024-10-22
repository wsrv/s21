#include "mainwindow.h"

#include <QSettings>

#include "draw.h"
#include "ui_mainwindow.h"

extern "C" {
#include "../../back/transformations.h"
#include "gif.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  start();
}

MainWindow::~MainWindow() {
  if (ui->openGLWidget->firstOpen) {
    free(ui->openGLWidget->test.facetsArr);
    free(ui->openGLWidget->test.vertexesArr);
  }
  Quit();  // внутри точно ошибка
  delete ui;
}

void MainWindow::on_name_button_clicked() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "Open a file", "/Users", "*.obj");
  if (fileName != "") {
    ui->openGLWidget->firstOpen = 1;
    ui->name_display->setText(" " + fileName.split('/').last());

    std::string str_expr = fileName.toStdString();
    char *file_way = (char *)str_expr.c_str();
    ui->openGLWidget->file_name = file_way;

    ui->openGLWidget->error =
        readFile(ui->openGLWidget->file_name, &ui->openGLWidget->test);

    if (!ui->openGLWidget->error) {
      ui->num_edges->setText(
          " Number of edges: " +
          QString::number(ui->openGLWidget->test.count_of_facets / 6));
      ui->num_vert->setText(
          " Number of vertices: " +
          QString::number(ui->openGLWidget->test.count_of_vertexes / 3));
      nurlanization(&ui->openGLWidget->test);
      shiftObj(&ui->openGLWidget->test, (ui->openGLWidget->translation[0]),
               'x');
      shiftObj(&ui->openGLWidget->test, (ui->openGLWidget->translation[1]),
               'y');
      shiftObj(&ui->openGLWidget->test, (ui->openGLWidget->translation[2]),
               'z');
      rotateObj(&ui->openGLWidget->test, (ui->openGLWidget->rotation[0]), 'x');
      rotateObj(&ui->openGLWidget->test, (ui->openGLWidget->rotation[1]), 'y');
      rotateObj(&ui->openGLWidget->test, (ui->openGLWidget->rotation[2]), 'z');
      scalingObj(&ui->openGLWidget->test,
                 ((ui->openGLWidget->scale / (double)100)));
    }
  }
  if (ui->openGLWidget->firstOpen > 1) {
    free(ui->openGLWidget->test.facetsArr);
    free(ui->openGLWidget->test.vertexesArr);
  }
  // ui->is_round->setChecked(true);
  ui->openGLWidget->update();
}

void MainWindow::clean() {
  ui->change_x->setValue(0);
  ui->change_y->setValue(0);
  ui->change_z->setValue(0);
  ui->openGLWidget->translation[0] = 0.0;
  ui->openGLWidget->translation[1] = 0.0;
  ui->openGLWidget->translation[2] = 0.0;
  ui->spin_x->setValue(0);
  ui->spin_y->setValue(0);
  ui->spin_z->setValue(0);
  ui->openGLWidget->rotation[0] = 0.0;
  ui->openGLWidget->rotation[1] = 0.0;
  ui->openGLWidget->rotation[2] = 0.0;
  ui->zoom->setValue(100);
  ui->openGLWidget->scale = 100;
  ui->openGLWidget->projection = 1;  // включена парал. проекция
  ui->parall_type->setChecked(true);  // чекбокс включен
  ui->is_round->setChecked(true);
  ui->openGLWidget->typeVertices = 1;
  ui->dashed->setChecked(true);
  ui->openGLWidget->typeLines = 1;
}

void MainWindow::on_screenshot_clicked() {
  QImage img(ui->openGLWidget->size(), QImage::Format_RGB32);
  QPainter painter(&img);
  QString temp = QCoreApplication::applicationDirPath();
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save file"), temp + "/images", tr("JPG (*.jpg);; BMP (*.bmp)"));
  bool res = false;
  ui->openGLWidget->render(&painter);
  res = img.save(fileName);
  if (res == true) {
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
    QImage img(ui->openGLWidget->size(), QImage::Format_RGB32);
    QPainter painter(&img);
    QTime dieTime;
    GifWriter gif;
    QByteArray ba = fileName.toLocal8Bit();
    const char *c_str = ba.data();
    GifBegin(&gif, c_str, 640, 480, 10);
    for (int i = 0; i < 50; ++i) {
      ui->openGLWidget->render(&painter);
      GifWriteFrame(&gif, img.bits(), 640, 480, 10);
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
  shiftObj(&ui->openGLWidget->test, value - ui->openGLWidget->translation[0],
           'x');
  ui->openGLWidget->translation[0] = value;  // сохранение в масив
  ui->howmuch_x->setText(QString::number(value));
  ui->openGLWidget->update();
}

void MainWindow::on_change_y_valueChanged(int value) {  // смещение по y
  shiftObj(&ui->openGLWidget->test, value - ui->openGLWidget->translation[1],
           'y');
  ui->openGLWidget->translation[1] = value;  // сохранение в масив
  ui->howmuch_y->setText(QString::number(value));
  ui->openGLWidget->update();
}

void MainWindow::on_change_z_valueChanged(int value) {  // смещение по z
  shiftObj(&ui->openGLWidget->test, value - ui->openGLWidget->translation[2],
           'z');
  ui->openGLWidget->translation[2] = value;  // сохранение в масив
  ui->openGLWidget->lastValueZ = value;
  ui->openGLWidget->update();
}

void MainWindow::on_zoom_valueChanged(
    int value) {  // изменение размеров объекта
  scalingObj(&ui->openGLWidget->test,
             (((double)value) / ui->openGLWidget->scale));
  ui->howmuch_zoom->setText(QString::number(value));
  ui->openGLWidget->scale = value;
  ui->openGLWidget->update();
}

void MainWindow::on_spin_x_valueChanged(int value) {  // вращение по x
  rotateObj(&ui->openGLWidget->test, (value - ui->openGLWidget->rotation[0]),
            'x');
  ui->x_spin_is->setText(QString::number(value));
  ui->openGLWidget->rotation[0] = value;
  ui->openGLWidget->update();
}

void MainWindow::on_spin_y_valueChanged(int value) {  // вращение по y
  rotateObj(&ui->openGLWidget->test, (value - ui->openGLWidget->rotation[1]),
            'y');
  ui->y_spin_is->setText(QString::number(value));
  ui->openGLWidget->rotation[1] = value;
  ui->openGLWidget->update();
}

void MainWindow::on_spin_z_valueChanged(int value) {  // вращение по z
  rotateObj(&ui->openGLWidget->test, (value - ui->openGLWidget->rotation[2]),
            'z');
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

void MainWindow::start() {
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

  ui->openGLWidget->sizeVertices =
      settings.value("sizeVertices", 10.0).value<int>();

  ui->openGLWidget->typeLines = settings.value("typeLines", 0).value<int>();

  ui->openGLWidget->typeVertices =
      settings.value("typeVertices", 1).value<int>();

  ui->openGLWidget->scale = settings.value("scale", 100).value<double>();

  ui->openGLWidget->rotation[0] = settings.value("rotation0", 0.0).value<int>();
  ui->openGLWidget->rotation[1] = settings.value("rotation1", 0.0).value<int>();
  ui->openGLWidget->rotation[2] = settings.value("rotation2", 0.0).value<int>();

  ui->openGLWidget->translation[0] =
      settings.value("translation0", 0.0).value<double>();
  ui->openGLWidget->translation[1] =
      settings.value("translation1", 0.0).value<double>();
  ui->openGLWidget->translation[2] =
      settings.value("translation2", 0.0).value<double>();

  settings.endGroup();

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

  ui->openGLWidget->update();
}

void MainWindow::Quit() {
  QString temp = QCoreApplication::applicationDirPath();
  QSettings settings(temp + "/settings.ini", QSettings::IniFormat);

  settings.beginGroup("Settings");

  settings.setValue("colorBackground", ui->openGLWidget->colorBackground);
  settings.setValue("colorLines", ui->openGLWidget->colorLines);
  settings.setValue("colorVertices", ui->openGLWidget->colorVertices);
  settings.setValue("sizeLines", ui->openGLWidget->sizeLines);
  settings.setValue("sizeVertices", ui->openGLWidget->sizeVertices);

  settings.setValue("typeLines", ui->openGLWidget->typeLines);
  settings.setValue("typeVertices", ui->openGLWidget->typeVertices);
  settings.setValue("scale", ui->openGLWidget->scale);

  settings.setValue("rotation0", ui->openGLWidget->rotation[0]);
  settings.setValue("rotation1", ui->openGLWidget->rotation[1]);
  settings.setValue("rotation2", ui->openGLWidget->rotation[2]);
  settings.setValue("translation0", ui->openGLWidget->translation[0]);
  settings.setValue("translation1", ui->openGLWidget->translation[1]);
  settings.setValue("translation2", ui->openGLWidget->translation[2]);

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
