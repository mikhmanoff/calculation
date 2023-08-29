#include "calc_support.h"

Node *parseInput(const char *str) {
  Node *operandList = NULL;
  char numberTempStr[256] = {};
  //   printf("%s\n", str); НУЖНО ПОТОМ УБРАТЬ

  for (size_t i = 0, j = 0; str[i] != '\0'; i++) {
    if ((str[i] >= '0' && str[i] <= '9') ||
        (str[i] == '.' && isdigit(str[i - 1]))) {
      numberTempStr[j] = str[i];
      j++;
    }
    if ((!(str[i] >= '0' && str[i] <= '9') && (j && str[i] != '.')) ||
        (str[i + 1] == '\0' && j)) {
      push(&operandList, atof(numberTempStr), number, NO_PRIORITY);
      memset(numberTempStr, 0, sizeof(numberTempStr));

      j = 0;
    }
    if (str[i] == 'x') {
      push(&operandList, 0, X, NO_PRIORITY);
    }
    if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' ||
        str[i] == '%') {
      if (str[i] == '+') {
        if (str[0] == '+' && i == 0) {
          push(&operandList, 0, number, NO_PRIORITY);
        }
        push(&operandList, 0, plus_t, LOW_PRIORITY);
      }
      if (str[i] == '-') {
        if (str[0] == '-' && i == 0) {
          push(&operandList, 0, number, NO_PRIORITY);
        }
        push(&operandList, 0, minus_t, LOW_PRIORITY);
      }
      if (str[i] == '*') {
        push(&operandList, 0, mult_t, MEDIUM_PRIORITY);
      }
      if (str[i] == '/') {
        push(&operandList, 0, div_tt, MEDIUM_PRIORITY);
      }
      if (str[i] == '%') {
        push(&operandList, 0, mod_t, MEDIUM_PRIORITY);
      }
    } else if (str[i] == '^') {
      push(&operandList, 0, pow_t, HIGH_PRIORITY);
    } else if (str[i] == 'c' || str[i] == 's' || str[i] == 't' ||
               str[i] == 'a' || str[i] == 'l' || str[i] == 'm') {
      if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
        push(&operandList, 0, mod_t, HIGH_PRIORITY);
        i = i + 2;
      }
      if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
          str[i + 3] == 't') {
        push(&operandList, 0, sqrt_t, HIGH_PRIORITY);
        i = i + 3;
      }
      if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
        push(&operandList, 0, cos_t, HIGH_PRIORITY);
        i = i + 2;
      }
      if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
        push(&operandList, 0, sin_t, HIGH_PRIORITY);
        i = i + 2;
      }
      if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
        push(&operandList, 0, tan_t, HIGH_PRIORITY);
        i = i + 2;
      }
      if (str[i] == 'c' && str[i + 1] == 'o' &&
          str[i + 2] == 's') {  // не заходит
        push(&operandList, 0, cos_t, HIGH_PRIORITY);
        i = i + 2;
      }
      if (str[i] == 'a') {
        if (str[i + 1] == 'c' && str[i + 2] == 'o' && str[i + 3] == 's') {
          push(&operandList, 0, acos_t, HIGH_PRIORITY);
          i = i + 3;
        }
        if (str[i + 1] == 's' && str[i + 2] == 'i' && str[i + 3] == 'n') {
          push(&operandList, 0, asin_t, HIGH_PRIORITY);
          i = i + 3;
        }
        if (str[i + 1] == 't' && str[i + 2] == 'a' && str[i + 3] == 'n') {
          push(&operandList, 0, atan_t, HIGH_PRIORITY);
          i = i + 3;
        }
      }
      if (str[i] == 'l') {
        if (str[i + 1] == 'n') {
          push(&operandList, 0, ln_t, HIGH_PRIORITY);
          i = i + 1;
        }
        if (str[i + 1] == 'o' && str[i + 2] == 'g') {
          push(&operandList, 0, log_t, HIGH_PRIORITY);
          i = i + 2;
        }
      }
    } else if (str[i] == '(' || str[i] == ')') {
      if (str[i] == '(') {
        push(&operandList, 0, left_bracket_t, ULTRA_PRIORITY);
        if (str[i + 1] == '+' || str[i + 1] == '-') {
          push(&operandList, 0, number, NO_PRIORITY);
        }
      }
      if (str[i] == ')') {
        push(&operandList, 0, right_bracket_t, ULTRA_PRIORITY);
      }
    }
  }
  return operandList;
}

// int main() {
//   char *s = "1+2+3-log(6)*sqrt(10)+ln(10)";
//   Node *list = NULL;
//   int rightBracket = 0, leftBracket = 0;
//   list = parseInput(s);

//   //   print(list);
//   //   printf("\n\n\n");
//   Node *tmp = inverseNode(list);
//   print(tmp);
//   //   push(&list, 14.48, tan_t, ULTRA_PRIORITY);
//   //   print(list);

//   return 0;
// }
