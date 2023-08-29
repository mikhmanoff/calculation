#ifndef CALC_SUPPORT_H
#define CALC_SUPPORT_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// коды ошибок
#define SUCCESS 0       // success
#define FAILTURE 1      // failure
#define NO_INPUT 2      // null input
#define BRACKETS_ERR 4  // ошибка в скобках
#define OPERATOR_ERR 5  // ошибка в операторах
#define FUNC_ERR 6      // ошибка в функции (при вводе)
#define INPUT_ERR 7     // некорректный ввод

// приоритет операций
#define NO_PRIORITY 0      // нет приоритета
#define LOW_PRIORITY 1     // низкий приоритет (+, -)
#define MEDIUM_PRIORITY 2  // средний приоритет (*, /, %)
#define HIGH_PRIORITY 3  // высокий приоритет (степень + функции)
#define ULTRA_PRIORITY 4  // высший приоритет (скобки)

typedef enum funcType {
  zero = -1,
  number = 0,
  X = 1,
  plus_t = 2,
  minus_t = 3,
  mult_t = 4,
  div_tt = 5,
  mod_t = 6,
  pow_t = 7,
  cos_t = 8,
  sin_t = 9,
  tan_t = 10,
  acos_t = 11,
  asin_t = 12,
  atan_t = 13,
  sqrt_t = 14,
  ln_t = 15,
  log_t = 16,
  left_bracket_t = 17,
  right_bracket_t = 18
} funcType;

////доп
typedef struct AddMoney {
  int term;
  double money;
} AddMoney;

typedef struct RemMoney {
  int term;
  double money;
} RemMoney;

typedef struct Deposit {
  double depositAmount;        // сумма вклада
  double periodOfPlacement;    // срок размещния
  double interestRate;         // процентная ставка
  double taxRate;              // налоговая ставка
  int periodOfPayments;        // периодичность выплат
  int interestCapitalization;  // капитализация процентов

  AddMoney replenishmentList[255];  // список пополнений
  int addCount;
  RemMoney listPartialWithdrawals[255];  // список частичных снятий
  int remCount;
  double minimumBalance;

  int paymentsType;

  double currentInterest;

  int currentMoth;
  int currentYear;
  int currentDay;
  int leapYear;
  int nextLeapYear;

  double taxArr[255];
  int countTaxArr;

  double sumInterest;
  double sumTax;
  double sumEndTerm;
} Deposit;

enum Dates {
  JANUARY = 1,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER = 0
};

enum PaymentsPeriod { EVERY_MONTH, EVERY_HALF_YEAR, EVERY_YEAR, END_TERM };

//   priority - приоритет
//   num - число
//   funcType - тип функции
//   Node* next - указатель на след;
typedef struct Node {
  int priority;
  double num;
  funcType funType;
  struct Node* next;  // указатель на след
} Node;

void print(Node* list);
void push(Node** pList, double num, funcType funType, int priority);
void pop(Node** pList);
int isEmpty(Node* List);

int checkStartInput(const char* s);
int checkAllBrackets(const char* s);
int checkInputString(const char* s);
int checkOperator(const char* s, int i, int length);
int checkCurrentBrackets(const char* s, int i);
int checkCorrectness(const char* s, int* leftBrackets, int* rightBrackets,
                     int* i);

Node* parseInput(const char* str);
Node* inverseNode(Node* list);

int operatorCheck(funcType opType);
int functionCheck(funcType function);

double monthAnnuity(double loan, int period, double rate);

// Функции для депозитного калькулятора
void depositCalcCore(Deposit* dp);
void depositPayments(Deposit* dp, double* interestTemp, double* taxTemp,
                     int month, int i);
void initialDp(Deposit* dp);
double taxRateCalc(Deposit* dp, double accum);
double everyMonthCapital(Deposit* dp, int daysInMonth);
int isLeapYear(Deposit* dp, int i);
int isLeap(int year);
void addToAmount(Deposit* dp, int counter);
void remAmount(Deposit* dp, int counter);
void addingTemp(Deposit* dp, double* interestTemp, double* taxTemp);
void remAmountEveryTime(Deposit* dp, int num);
void addAmountEveryTime(Deposit* dp, int num);

#endif  // CALC_SUPPORT_H
