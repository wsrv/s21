#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

#include "draw.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class MainWindow;

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void start(); /**< Старт программы */
  void Quit();  /**< Закрытие программы */

 private slots:
  void clean(); /**< Отчистка стека */
  void on_name_button_clicked();
  void on_screenshot_clicked();
  void on_gif_clicked();
  void on_change_y_valueChanged(int value);
  void on_change_x_valueChanged(int value);
  void on_zoom_valueChanged(int value);
  void on_spin_x_valueChanged(int value);
  void on_spin_y_valueChanged(int value);
  void on_spin_z_valueChanged(int value);
  void on_back_colour_clicked();
  void on_change_z_valueChanged(int arg1);
  void on_vert_colour_clicked();
  void on_Edges_colour_clicked();
  void on_central_type_clicked();
  void on_parall_type_clicked();
  void on_solid_clicked();
  void on_dashed_clicked();
  void on_is_no_clicked();
  void on_is_square_clicked();
  void on_is_round_clicked();
  void on_thick_valueChanged(int value);
  void on_size_valueChanged(int value);

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
