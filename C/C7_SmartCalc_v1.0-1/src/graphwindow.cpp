#include "graphwindow.h"

#include "qcustomplot.h"
#include "ui_graphwindow.h"

extern "C" {
#include "s21_smartcalc.h"
}

Graphwindow::Graphwindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::Graphwindow) {
  ui->setupUi(this);
}

Graphwindow::~Graphwindow() { delete ui; }

void Graphwindow::on_Draw_clicked(QString text) {
  ui->widget->clearGraphs();
  ui->function_is->setText(text);
}

void Graphwindow::on_pushButton_clicked() {
  ui->widget->clearGraphs();
  double minx = ui->x_min->text().toDouble();
  double maxx = ui->x_max->text().toDouble();
  double miny = ui->y_min->text().toDouble();
  double maxy = ui->y_max->text().toDouble();
  if (minx < maxx && miny < maxy) {
    int N = 500;
    double h = (maxx - minx) / N;
    QVector<double> x(N), y(N);
    int i = 0;
    char *str = new char(ui->function_is->text().length());
    QByteArray barr = ui->function_is->text().toLatin1();
    strlcpy(str, barr, ui->function_is->text().length() + 1);

    for (double X = minx; X <= maxx && i < N; X += h) {
      x[i] = X;
      y[i] = s21_smart_calc(str, X);
      i++;
    }
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    ui->widget->xAxis->setRange(minx, maxx);
    ui->widget->yAxis->setRange(miny, maxy);
    ui->widget->replot();
  }
}
