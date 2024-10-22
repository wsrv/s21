#include "mainwindow.h"

#include <QLabel>
#include <QPixmap>
#include <QString>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  graphwindow = new Graphwindow(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_left, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_right, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(functions()));
  connect(ui->pushButton_clean, SIGNAL(clicked()), this,
          SLOT(on_button_delete_clicked()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(on_button_x_clicked()));
  connect(ui->pushButton_point, SIGNAL(clicked()), this,
          SLOT(on_button_point_clicked()));
  connect(ui->pushButton_eq, SIGNAL(clicked()), this,
          SLOT(on_button_eq_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();

  QString new_label = ui->result->text() + button->text();

  ui->result->setText(new_label);
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();

  QString new_label;

  new_label = ui->result->text();

  if (button->text() == "÷" && !(ui->result->text().endsWith("÷")) &&
      !(ui->result->text().endsWith("/"))) {
    new_label += "/";
  } else if (button->text() == "*" && !(ui->result->text().endsWith("*")) &&
             !(ui->result->text().endsWith("*"))) {
    new_label += "*";
  } else if (button->text() == "+" && !(ui->result->text().endsWith("+"))) {
    new_label += "+";
  } else if (button->text() == "-" && !(ui->result->text().endsWith("-"))) {
    new_label += "-";
  } else if (button->text() == "^" && !(ui->result->text().endsWith("^"))) {
    new_label += "^";
  } else if (button->text() == "mod" && !(ui->result->text().endsWith("mod"))) {
    new_label += "mod";
  } else if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")") {
    new_label += ")";
  }

  ui->result->setText(new_label);
}

void MainWindow::functions() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  new_label = ui->result->text() + button->text() + "(";
  ui->result->setText(new_label);
}

void MainWindow::on_button_delete_clicked() { ui->result->setText(""); }

void MainWindow::on_button_x_clicked() {
  QString new_label;
  if (!(ui->result->text().endsWith("x"))) new_label = ui->result->text() + "x";
  ui->result->setText(new_label);
}

void MainWindow::on_button_point_clicked() {
  if (!(ui->result->text().endsWith('.')))
    ui->result->setText(ui->result->text() + ".");
}

void MainWindow::on_pushButton_exp_clicked() {
  if (!(ui->result->text().endsWith('e')))
    ui->result->setText(ui->result->text() + "e");
}

void MainWindow::on_button_eq_clicked() {
  std::string str = ui->result->text().toStdString();
  s21::Controller controller;
  if (ui->result->text().contains("x") &&
      !(isnan(controller.Calculation(str, 0.0)))) {
    graphwindow->on_Draw_clicked(ui->result->text());
    graphwindow->show();
  } else {
    double result = controller.Calculation(str, 0.0);
    QString numberResult = QString::number(result);
    ui->result->setText(numberResult);
  }
}

void MainWindow::on_pushButton_calc_cred_clicked() {
  s21::Controller controller;
  QString n = " ";
  double monthly = controller.cred_monthly(ui->time->value(), ui->summ->value(),
                                           ui->procents->value());
  QString monthlyResult = QString::number(monthly, 'f', 2);
  ui->monthly->setText(n + monthlyResult);
  double total = controller.cred_total_1(monthly, (ui->time->value()));
  QString totalResult = QString::number(total, 'f', 2);
  ui->totalpay->setText(n + totalResult);
  double over = controller.cred_over_1(total, ui->summ->value());
  QString overResult = QString::number(over, 'f', 2);
  ui->overpay->setText(n + overResult);

  std::list<double> monthly2;
  monthly2 = controller.cred_monthly2(ui->time->value(), ui->summ->value(),
                                      ui->procents->value());
  QString overResult2 = QString::number(monthly2.front(), 'f', 2);
  overResult2 = " " + overResult2;
  ui->overpay_2->setText(overResult2);
  monthly2.pop_front();
  QString totalResult2 = QString::number(monthly2.front(), 'f', 2);
  totalResult2 = " " + totalResult2;
  ui->totalpay_2->setText(totalResult2);
  monthly2.pop_front();
  int i = 1;
  while (monthly2.size() > 0) {
    QString monthlyResult = QString::number(monthly2.front(), 'f', 2);
    QString day_Res = QString::number(i);
    n += "Платеж №" + day_Res + "   " + monthlyResult + "\n ";
    monthly2.pop_front();
    i++;
  }
  ui->monthly_2->setText(n);
}
