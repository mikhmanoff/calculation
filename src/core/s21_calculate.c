#include "calc_core.h"

double s21_calculation(Node *list) {
  double res = 0.;
  Node *numRes = NULL;

  for (int i = 0; list != NULL; i++) {
    if (list->funType == 0 || list->funType == 1) {
      push(&numRes, list->num, list->funType, list->priority);
      pop(&list);
    }
    if (list->funType > 1 && list->funType < 8) {
      double val2 = numRes->num;
      pop(&numRes);
      double val1 = numRes->num;
      pop(&numRes);

      funcType operator= list->funType;
      pop(&list);
      res = evaluate(val1, val2, operator);
      push(&numRes, res, 0, NO_PRIORITY);
    }

    if (list->funType > 7 && list->funType < 17) {
      double val2 = numRes->num;
      pop(&numRes);
      double val1 = 0;
      funcType operator= list->funType;
      pop(&list);
      res = evaluate(val1, val2, operator);
      push(&numRes, res, 0, NO_PRIORITY);
    }
  }

  res = numRes->num;
  pop(&numRes);

  return res;
}

double evaluate(double val1, double val2, funcType operator) {
  double result = 0.0;

  switch (operator) {
    case plus_t:
      result = val1 + val2;
      break;
    case minus_t:
      result = val1 - val2;
      break;
    case mult_t:
      result = val1 * val2;
      break;
    case div_tt:
      result = val1 / val2;
      break;
    case mod_t:
      result = fmod(val1, val2);
      break;
    case pow_t:
      result = pow(val1, val2);
      break;
    case cos_t:
      result = cos(val2);
      break;
    case sin_t:
      result = sin(val2);
      break;
    case tan_t:
      result = tan(val2);
      break;
    case acos_t:
      result = acos(val2);
      break;
    case asin_t:
      result = asin(val2);
      break;
    case atan_t:
      result = atan(val2);
      break;
    case sqrt_t:
      result = sqrt(val2);
      break;
    case ln_t:
      result = log(val2);
      break;
    case log_t:
      result = log10(val2);
      break;

    default:
      break;
  }

  return result;
}
