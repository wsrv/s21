#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include "qcustomplot.h"
#include <QMainWindow>

#include "graphwindow.h"

extern "C" {
#include "s21_smartcalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class MainWindow;  //
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graphwindow *graphwindow;

 private slots:
  void digits_numbers();
  void operations();
  void functions();
  void on_button_delete_clicked();
  void on_button_x_clicked();
  void on_button_point_clicked();
  void on_button_eq_clicked();
  void on_pushButton_calc_cred_clicked();
};
#endif  // MAINWINDOW_H
