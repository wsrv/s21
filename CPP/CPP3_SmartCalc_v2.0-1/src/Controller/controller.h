#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../Model/model.h"
namespace s21 {

class Controller {
 public:
  Controller() {}
  ~Controller() {}
  double Calculation(std::string &str, double x);
  double cred_monthly(double months, double summ, double procents);
  std::list<double> cred_monthly2(double months, double summ, double procents);
  double cred_total_1(double monthly, double time);
  double cred_over_1(double total, double sum);

 private:
  s21::Model model_;
};  // Controller

}  //  namespace s21

#endif  // CONTROLLER_H
