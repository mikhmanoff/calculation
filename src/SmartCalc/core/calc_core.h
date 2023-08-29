#include "../backend/calc_support.h"

Node *s21_infixToPolsih(Node *list, double xValue);
double calculateOperands(double val1, double val2, funcType operation);
double evaluate(double val1, double val2, funcType opType);
double s21_calculation(Node *list);
