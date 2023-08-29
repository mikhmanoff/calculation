#include "calc_support.h"

void dateCorrect(int *date, int leapYear) {
  if (*date == JANUARY || *date == MARCH || *date == MAY || *date == JULY ||
      *date == AUGUST || *date == OCTOBER || *date == DECEMBER)
    *date = 31;
  else if (*date == APRIL || *date == JUNE || *date == SEPTEMBER ||
           *date == NOVEMBER)
    *date = 30;
  else if (*date == FEBRUARY && leapYear)
    *date = 29;
  else if (*date == FEBRUARY && !leapYear)
    *date = 28;
}

void depositCalcCore(Deposit *dp) {
  double interestTemp = 0.;
  double taxTemp = 0.;
  int daysInMonth = 0;
  int month = 0;

  initialDp(dp);

  dp->sumEndTerm = dp->depositAmount;

  dp->minimumBalance = 0.;

  for (int i = 0; i < dp->periodOfPlacement; i++) {
    dp->leapYear = isLeapYear(dp, i);
    dp->nextLeapYear = isLeapYear(dp, i + 1);
    daysInMonth = (dp->currentMoth + i) % 12;
    month = daysInMonth;
    dateCorrect(&daysInMonth, dp->leapYear);

    dp->currentInterest = everyMonthCapital(dp, daysInMonth);
    interestTemp += dp->currentInterest;

    addToAmount(dp, i);
    remAmount(dp, i);

    depositPayments(dp, &interestTemp, &taxTemp, month, i);
  }

  dp->sumEndTerm = dp->depositAmount;
}

void depositPayments(Deposit *dp, double *interestTemp, double *taxTemp,
                     int month, int i) {
  if (dp->paymentsType == EVERY_MONTH) {
    addingTemp(dp, interestTemp, taxTemp);
  } else if (dp->paymentsType == EVERY_HALF_YEAR) {
    if ((i > 0 && (month == dp->currentMoth - 1 ||
                   month == (dp->currentMoth + 5) % 12)) ||
        i == dp->periodOfPlacement - 1) {
      addingTemp(dp, interestTemp, taxTemp);
    }
  } else if (dp->paymentsType == EVERY_YEAR) {
    if ((i > 0 && ((dp->currentMoth + i) % 12) == dp->currentMoth - 1) ||
        i == dp->periodOfPlacement - 1) {
      addingTemp(dp, interestTemp, taxTemp);
    }
  } else if (dp->paymentsType == END_TERM) {
    if (i == dp->periodOfPlacement - 1) {
      addingTemp(dp, interestTemp, taxTemp);
    }
  }
  if ((i > 0 && (((dp->currentMoth + i) % 12) == 11)) ||
      i == dp->periodOfPlacement - 1) {
    dp->sumTax += taxRateCalc(dp, *taxTemp);
    *taxTemp = 0.;
  }
}

void addingTemp(Deposit *dp, double *interestTemp, double *taxTemp) {
  dp->sumInterest += *interestTemp;
  *taxTemp += *interestTemp;
  if (dp->interestCapitalization) dp->depositAmount += *interestTemp;
  *interestTemp = 0.;
}

void addToAmount(Deposit *dp, int counter) {
  int month = (dp->currentMoth + counter) % 12;

  for (int i = 0; i < dp->addCount; i++) {
    if (dp->replenishmentList[i].term == EVERY_MONTH) {
      addAmountEveryTime(dp, i);
    } else if (dp->replenishmentList[i].term == EVERY_HALF_YEAR) {
      if (counter > 0 && (month == dp->currentMoth - 1 ||
                          month == (dp->currentMoth + 5) % 12)) {
        addAmountEveryTime(dp, i);
      }
    } else if (dp->replenishmentList[i].term == EVERY_YEAR) {
      if (counter > 0 && month == dp->currentMoth - 1) {
        addAmountEveryTime(dp, i);
      }
    }
  }
}

void remAmount(Deposit *dp, int counter) {
  int month = (dp->currentMoth + counter) % 12;

  for (int i = 0; i < dp->remCount; i++) {
    if (dp->listPartialWithdrawals[i].term == EVERY_MONTH) {
      remAmountEveryTime(dp, i);
    } else if (dp->listPartialWithdrawals[i].term == EVERY_HALF_YEAR) {
      if (counter > 0 && (month == dp->currentMoth - 1 ||
                          month == (dp->currentMoth + 5) % 12)) {
        remAmountEveryTime(dp, i);
      }
    } else if (dp->listPartialWithdrawals[i].term == EVERY_YEAR) {
      if (counter > 0 && month == dp->currentMoth - 1) {
        remAmountEveryTime(dp, i);
      }
    }
  }
}

void addAmountEveryTime(Deposit *dp, int num) {
  dp->depositAmount += dp->replenishmentList[num].money;
}

void remAmountEveryTime(Deposit *dp, int num) {
  if (dp->depositAmount - dp->listPartialWithdrawals[num].money >=
      dp->minimumBalance)
    dp->depositAmount -= dp->listPartialWithdrawals[num].money;
}

int isLeapYear(Deposit *dp, int i) {
  return isLeap(dp->currentYear + (dp->currentMoth - 1 + i) / 12);
}

int isLeap(int year) {
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

double everyMonthCapital(Deposit *dp, int daysInMonth) {
  double profit = 0.;
  double daysInYear = 0.;
  daysInYear = dp->leapYear ? 366. : 365.;

  if (dp->leapYear != dp->nextLeapYear) {
    if (dp->leapYear) {
      profit = dp->depositAmount * (dp->interestRate / 100.) / 366. *
                   ((double)daysInMonth - dp->currentDay) +
               dp->currentDay *
                   ((dp->interestRate / 100.) * dp->depositAmount / 365.);
    } else {
      profit = dp->depositAmount * (dp->interestRate / 100.) / 365. *
                   ((double)daysInMonth - dp->currentDay) +
               dp->currentDay *
                   ((dp->interestRate / 100.) * dp->depositAmount / 366.);
    }
  } else {
    profit = dp->depositAmount * (dp->interestRate / 100.) / daysInYear *
             (double)daysInMonth;
  }

  return profit;
}

double taxRateCalc(Deposit *dp, double accum) {
  double tax = 0.;
  double nonTaxableIncome = 75000.;  // ставка цб = 7.5%

  tax = accum - nonTaxableIncome;
  if (tax > 0.)
    tax *= (dp->taxRate / 100.);
  else
    tax = 0.;

  return tax;
}

void initialDp(Deposit *dp) {
  dp->sumEndTerm = 0.;
  dp->sumInterest = 0.;
  dp->sumTax = 0.;
  dp->leapYear = 0;
  dp->currentInterest = 0.;
  dp->countTaxArr = 0;
  for (int i = 0; i < 255; i++) {
    dp->taxArr[i] = 0.;
  }
}
