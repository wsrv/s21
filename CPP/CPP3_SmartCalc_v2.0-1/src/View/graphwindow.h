#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>

#include "../Controller/controller.h"

namespace Ui {
class Graphwindow;
}

class Graphwindow : public QDialog {
  Q_OBJECT

 public:
  explicit Graphwindow(QWidget *parent = nullptr);
  void on_Draw_clicked(QString text);
  ~Graphwindow();
 private slots:
  void on_pushButton_clicked();

  void on_find_fx_clicked();

 private:
  Ui::Graphwindow *ui;
};

#endif  // GRAPHWINDOW_H
