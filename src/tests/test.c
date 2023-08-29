#include <check.h>

#include "../core/calc_core.h"

START_TEST(s21_check_input) {
  int err = 0;
  char string[] = "1+2+3-log(6)*sqrt(10)+ln(10)";
  err = checkInputString(string);
  ck_assert_int_eq(0, err);

  char string_1[] = "1+2+3*ln()";
  err = checkInputString(string_1);
  ck_assert_int_eq(1, err);

  char string_2[] = "1.123123+2mod4+(3*7)+sqrt(7)";
  err = checkInputString(string_2);
  ck_assert_int_eq(0, err);

  char string_3[] = "1+2mod4+3*(7+1)+acos(1/2)+5^2";
  err = checkInputString(string_3);
  ck_assert_int_eq(0, err);

  char string_4[] = "1+2mod4+3*(7+1d)+asin(1/2)";
  err = checkInputString(string_4);
  ck_assert_int_eq(1, err);

  char string_5[] = "^1+2mod4+3*(7+1)+atan(1/2)";
  err = checkInputString(string_5);
  ck_assert_int_eq(1, err);

  char string_6[] = "cos(1/2)+2mod4+3*(7+1)+sin(0)";
  err = checkInputString(string_6);
  ck_assert_int_eq(0, err);

  char string_7[] = "tan(1/2)+2mod4+3*(7+1)+asin(0)+atan(0)";
  err = checkInputString(string_7);
  ck_assert_int_eq(0, err);

  char string_8[] = "123456789+";
  err = checkInputString(string_8);
  ck_assert_int_eq(1, err);

  char string_9[] = "1/2+aco(3)-lo(6)+l(8)-asi(5)+at(3)+tcos(213)^";
  err = checkInputString(string_9);
  ck_assert_int_eq(1, err);

  char string_10[] = "";
  err = checkInputString(string_10);
  ck_assert_int_eq(1, err);

  char string_11[] = "!1+4-f+d/";
  err = checkInputString(string_11);
  ck_assert_int_eq(1, err);

  char string_12[] = "1+4/";
  err = checkInputString(string_12);
  ck_assert_int_eq(1, err);

  char string_13[] = "1+4*";
  err = checkInputString(string_13);
  ck_assert_int_eq(1, err);

  char string_14[] = "1+5-4*)";
  err = checkInputString(string_14);
  ck_assert_int_eq(1, err);

  char string_15[] = "1+((5-4)/410";
  err = checkInputString(string_15);
  ck_assert_int_eq(1, err);

  char string_16[] = "4mid2+(5-4)";
  err = checkInputString(string_16);
  ck_assert_int_eq(1, err);

  char string_17[] = "0+(5-4)";
  err = checkInputString(string_17);
  ck_assert_int_eq(0, err);

  char string_18[] = "*0+(5-4)";
  err = checkInputString(string_18);
  ck_assert_int_eq(1, err);

  char string_19[] = "1/0 + 2";
  err = checkInputString(string_19);
  ck_assert_int_eq(1, err);

  char string_20[] = "1+";
  err = checkInputString(string_20);
  ck_assert_int_eq(1, err);

  char string_21[] = "()";
  err = checkInputString(string_21);
  ck_assert_int_eq(1, err);

  char string_22[] = "hello";
  err = checkInputString(string_22);
  ck_assert_int_eq(1, err);

  char string_23[] = "2*2/4";
  err = checkInputString(string_23);
  ck_assert_int_eq(0, err);
}
END_TEST

START_TEST(calculator) {
  Node *number_list = NULL;
  double res_21 = 0.0;
  double res_original = 0.0;

  char input[] = "-cos(1)+3";
  number_list = parseInput(input);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = -cos(1) + 3;
  ck_assert_double_eq(res_original, res_21);

  char input_1[] = "-0.1+0.2";
  number_list = parseInput(input_1);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = -0.1 + 0.2;
  ck_assert_double_eq(res_original, res_21);

  char input_3[] = "2^(2.1+1)-11mod2";
  number_list = parseInput(input_3);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = pow(2, (2.1 + 1)) - fmod(11, 2);
  ck_assert_double_eq(res_original, res_21);

  char input_5[] = "sqrt(4.123456789)+3-1.12";
  number_list = parseInput(input_5);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = sqrt(4.123456789) + 3 - 1.12;
  ck_assert_double_eq(res_original, res_21);

  char input_6[] = "log(+10.2)-ln(10.2)";
  number_list = parseInput(input_6);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = log10(10.2) - log(10.2);
  ck_assert_double_eq(res_original, res_21);

  char input_7[] = "11+(-2)^5";
  number_list = parseInput(input_7);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = 11 + pow(-2, 5);
  ck_assert_double_eq(res_original, res_21);

  char input_8[] = "log(10.2)+ln(10.2)";
  number_list = parseInput(input_8);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = log10(10.2) + log(10.2);
  ck_assert_double_eq(res_original, res_21);

  char input_9[] = "sqrt(+4+1)+(-3+1)";
  number_list = parseInput(input_9);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = sqrt(4 + 1) + (-3 + 1);
  ck_assert_double_eq(res_original, res_21);

  char input_10[] = "sqrt(3+1)-(-3+1)";
  number_list = parseInput(input_10);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = sqrt(3 + 1) - (-3 + 1);
  ck_assert_double_eq(res_original, res_21);

  char input_11[] = "+1.1122-(-1)";
  number_list = parseInput(input_11);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = +1.1122 - (-1);
  ck_assert_double_eq(res_original, res_21);

  char input_12[] = "sin(x)";
  number_list = parseInput(input_12);
  number_list = s21_infixToPolsih(number_list, 1.1);
  res_21 = s21_calculation(number_list);
  res_original = sin(1.1);

  ck_assert_double_eq(res_original, res_21);

  char input_13[] = "cos(x)";
  number_list = parseInput(input_13);
  number_list = s21_infixToPolsih(number_list, 0);
  res_21 = s21_calculation(number_list);
  res_original = cos(0);
  ck_assert_double_eq(res_original, res_21);

  char input_14[] = "tan(x)";
  number_list = parseInput(input_14);
  number_list = s21_infixToPolsih(number_list, 7);
  res_21 = s21_calculation(number_list);
  res_original = tan(7);
  ck_assert_double_eq(res_original, res_21);

  char input_15[] = "asin(x)";
  number_list = parseInput(input_15);
  number_list = s21_infixToPolsih(number_list, 1);
  res_21 = s21_calculation(number_list);
  res_original = asin(1);
  ck_assert_double_eq(res_original, res_21);

  char input_16[] = "acos(x)";
  number_list = parseInput(input_16);
  number_list = s21_infixToPolsih(number_list, 1);
  res_21 = s21_calculation(number_list);
  res_original = acos(1);
  ck_assert_double_eq(res_original, res_21);

  char input_17[] = "atan(x)";
  number_list = parseInput(input_17);
  number_list = s21_infixToPolsih(number_list, 1);
  res_21 = s21_calculation(number_list);
  res_original = atan(1);
  ck_assert_double_eq(res_original, res_21);

  char input_18[] = "hello";
  int err = checkInputString(input_18);
  if (err == 0) {
    Node *number_list = parseInput(input_18);
    number_list = s21_infixToPolsih(number_list, 0);
    res_21 = s21_calculation(number_list);
  }
  ck_assert_int_eq(1, err);

  char input_19[] = "2^(2.1+1)-11mid2";
  err = checkInputString(input_19);
  if (err == 0) {
    Node *number_list = parseInput(input_19);
    number_list = s21_infixToPolsih(number_list, 0);
    res_21 = s21_calculation(number_list);
  }
  ck_assert_int_eq(1, err);

  char input_20[] = "2^(2.1+1)+(";
  err = checkInputString(input_20);
  if (err == 0) {
    Node *number_list = parseInput(input_20);
    number_list = s21_infixToPolsih(number_list, 0);
    res_21 = s21_calculation(number_list);
  }
  ck_assert_int_eq(1, err);

  char input_21[] = "2^(2.1+1)+()";
  err = checkInputString(input_21);
  if (err == 0) {
    Node *number_list = parseInput(input_21);
    number_list = s21_infixToPolsih(number_list, 0);
    res_21 = s21_calculation(number_list);
  }
  ck_assert_int_eq(1, err);

  char input_22[] = "2^(2.1+1)+2-(3+1)";
  err = checkInputString(input_22);
  if (err == 0) {
    Node *number_list = parseInput(input_22);
    number_list = s21_infixToPolsih(number_list, 0);
    res_21 = s21_calculation(number_list);
  }
  ck_assert_int_eq(0, err);

  char input_23[] = "cos(x)";
  err = checkInputString(input_23);
  if (err == 0) {
    Node *number_list = parseInput(input_23);
    number_list = s21_infixToPolsih(number_list, 0);
    res_21 = s21_calculation(number_list);
  }
  ck_assert_int_eq(0, err);
}
END_TEST

Suite *s21_SmartCalc_tests_create() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_SmartCalc");
  tc_core = tcase_create("tests");
  tcase_add_test(tc_core, s21_check_input);
  tcase_add_test(tc_core, calculator);
  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  Suite *s = s21_SmartCalc_tests_create();
  SRunner *s21_SmartCalc_runner = srunner_create(s);
  int number_failed;
  srunner_run_all(s21_SmartCalc_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_SmartCalc_runner);
  srunner_free(s21_SmartCalc_runner);
  return number_failed == 0 ? 0 : 1;
}