

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