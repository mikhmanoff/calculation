#include "calc_support.h"

int checkOperator(funcType operator) {
  int res = 0;

  if (operator== plus_t || operator== minus_t || operator== div_tt || operator==
      mult_t ||
      operator== pow_t ||
      operator== mod_t) {
    res = 1;
  }
  return res;
}

int checkFunction(funcType function) {
  int res = 0;

  if (function == cos_t || function == sin_t || function == tan_t ||
      function == atan_t || function == asin_t || function == acos_t ||
      function == sqrt_t || function == log_t || function == ln_t) {
    res = 1;
  }

  return res;
}
