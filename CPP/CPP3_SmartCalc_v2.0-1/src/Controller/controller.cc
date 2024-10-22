#include "controller.h"
namespace s21 {
double Controller::Calculation(std::string& str, double x) {
  return this->model_.s21_smart_calc(str, x);
}

double Controller::cred_monthly(double months, double summ, double procents) {
  return this->model_.s21_credit_calc_monthly(months, summ, procents);
}

double Controller::cred_total_1(double monthly, double time) {
  return this->model_.s21_credit_calc_total_1(monthly, time);
}

double Controller::cred_over_1(double total, double sum) {
  return this->model_.s21_credit_calc_over_1(total, sum);
}

std::list<double> Controller::cred_monthly2(double months, double summ,
                                            double procents) {
  return this->model_.s21_credit_calc2(months, summ, procents);
}

}  // namespace s21
