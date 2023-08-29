#include "calc_support.h"

int checkInputString(const char *s) {
  int flag = SUCCESS;
  if (checkStartInput(s) == 0 && checkAllBrackets(s) == 0) {
    int length = strlen(s);
    int leftBrackets = 0, rightBrackets = 0;

    for (int i = 0; i < length; i++) {
      if (checkOperator(s, i, length) == 0 && checkCurrentBrackets(s, i) == 0 &&
          checkCorrectness(s, &leftBrackets, &rightBrackets, &i) == 0) {
        flag = SUCCESS;
      } else {
        flag = FAILTURE;
        break;
      }
    }
  } else {
    flag = FAILTURE;
  }

  return flag;
}

int checkStartInput(const char *s) {
  int flag = SUCCESS;

  if (strlen(s) < 1 || strlen(s) > 256) {
    flag = NO_INPUT;  // еще нужно посмотреть, нужно ли больше кодов
  } else if ((s[0] == '+' || s[0] == '-' || s[0] == '/' || s[0] == '*' ||
              s[0] == '^') &&
             (s[1] == '+' || s[1] == '-' || s[1] == '/' || s[1] == '*' ||
              s[1] == '^')) {
    flag = FAILTURE;
  } else if (s[0] == '/' || s[0] == '*' || s[0] == '^' || s[0] == 'm' ||
             s[0] == '.') {
    flag = INPUT_ERR;
  }

  return flag;
}

int checkAllBrackets(const char *s) {
  int flag = SUCCESS;
  char *copy = malloc(strlen(s) + 1);
  strcpy(copy, s);

  int length = strlen(copy);
  char *stack = malloc(length * sizeof(char));
  int top = -1;

  for (int i = 0; i < length; i++) {
    if (copy[i] == '(') {
      stack[++top] = copy[i];  // Помещаем открывающую скобку в стек
    } else if (copy[i] == ')') {
      if (top == -1) {
        flag = FAILTURE;  // Если встретилась закрывающая скобка, но стек
                          // пустой, то порядок скобок неверный
        break;
      } else {
        char last = stack[top--];
        if (last == '(' && copy[i] != ')') {
          flag = FAILTURE;  // Если встретилась закрывающая скобка, но она не
                            // соответствует последней открывающей скобке, то
                            // порядок скобок неверный
          break;
        }
      }
    }
  }

  if (top != -1) {
    flag = FAILTURE;  // Если в конце остались открывающие скобки в стеке, то
                      // порядок скобок неверный
  }

  free(stack);  // Освобождение памяти стека
  free(copy);

  return flag;
}

int checkOperator(const char *s, int i, int length) {
  int flag = SUCCESS;

  if ((s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*' ||
       s[i] == '^') &&
      (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '/' ||
       s[i + 1] == '*' || s[i + 1] == '^')) {
    flag = FAILTURE;
  }

  int last = length - 1;

  if (s[last] == '+' || s[last] == '-' || s[last] == '/' || s[last] == '*' ||
      s[last] == '^') {
    flag = FAILTURE;
  }

  if (s[i] == '0' && s[i + 1] == 0) {
    // flag == FAILTURE;
  }

  return flag;
}

int checkCurrentBrackets(const char *s, int i) {
  int flag = SUCCESS;

  if ((s[i] == '(') && (s[i + 1] == ')')) {
    flag = FAILTURE;
  }
  if ((s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' ||
       s[i] == '^') &&
      (s[i + 1] == ')')) {
    flag = FAILTURE;
  }

  return flag;
}

int checkCorrectness(const char *s, int *leftBrackets, int *rightBrackets,
                     int *i) {
  int flag = SUCCESS;

  if (s[*i] == '.') {
    *i = *i;
  }
  if (s[*i] == '.') {
    *i = *i;
  } else if (s[*i] == 'x') {
    *i = *i;
  } else if (s[*i] >= '0' && s[*i] <= '9') {
    *i = *i;
  } else if (s[*i] == '+' || s[*i] == '-' || s[*i] == '*' || s[*i] == '/' ||
             s[*i] == '^') {
    *i = *i;
  } else if (s[*i] == '(') {
    *leftBrackets = *leftBrackets + 1;
  } else if (s[*i] == ')') {
    *rightBrackets = *rightBrackets + 1;
  } else if ((s[*i] == 'm' && s[*i + 1] == 'o' && s[*i + 2] == 'd') &&
             (s[*i + 3] >= '0' && s[*i + 3] <= '9')) {
    *i = *i + 2;
  } else if (s[*i] == 'c' && s[*i + 1] == 'o' && s[*i + 2] == 's' &&
             s[*i + 3] == '(') {
    *i = *i + 2;
  } else if (s[*i] == 's' && s[*i + 1] == 'i' && s[*i + 2] == 'n' &&
             s[*i + 3] == '(') {
    *i = *i + 2;
  } else if (s[*i] == 't' && s[*i + 1] == 'a' && s[*i + 2] == 'n' &&
             s[*i + 3] == '(') {
    *i = *i + 2;
  } else if (s[*i] == 'a' && s[*i + 1] == 'c' && s[*i + 2] == 'o' &&
             s[*i + 3] == 's' && s[*i + 4] == '(') {
    *i = *i + 3;
  } else if (s[*i] == 'a' && s[*i + 1] == 's' && s[*i + 2] == 'i' &&
             s[*i + 3] == 'n' && s[*i + 4] == '(') {
    *i = *i + 3;
  } else if (s[*i] == 'a' && s[*i + 1] == 't' && s[*i + 2] == 'a' &&
             s[*i + 3] == 'n' && s[*i + 4] == '(') {
    *i = *i + 3;
  } else if (s[*i] == 's' && s[*i + 1] == 'q' && s[*i + 2] == 'r' &&
             s[*i + 3] == 't' && s[*i + 4] == '(') {
    *i = *i + 3;
  } else if (s[*i] == 'l' && s[*i + 1] == 'n' && s[*i + 2] == '(') {
    *i = *i + 1;
  } else if (s[*i] == 'l' && s[*i + 1] == 'o' && s[*i + 2] == 'g' &&
             s[*i + 3] == '(') {
    *i = *i + 2;
  } else {
    flag = FAILTURE;
  }
  if (*rightBrackets > *leftBrackets) flag = FAILTURE;
  return flag;
}
