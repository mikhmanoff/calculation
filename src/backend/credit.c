#include "calc_support.h"

double monthAnnuity(double loan, int period, double rate) {
  double monthRate = rate / 12.0 / 100.0;
  double temp = pow((1 + monthRate), period);

  return loan * monthRate * temp / (temp - 1);
}