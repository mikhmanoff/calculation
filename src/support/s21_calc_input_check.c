#include "calc_support.h"

int checkStartInput(const char *s) {
  int flag = SUCCESS;

  if (strlen(s) < 1 || strlen(s) > 256) {
    flag = NO_INPUT;
  } else if (s[0] == s[1]) {
    flag = FAILTURE;
  } else if (s[0] == '/' || s[0] == '*' || s[0] == '^' || s[0] == 'm' ||
             s[0] == '.') {
    flag = INPUT_ERR;
  }

  return flag;
}

int checkBrackets(const char *s) {
  int flag = SUCCESS;

  return flag;
}

int main() {
  char *s = "*-5";
  int err = checkStartInput(s);

  printf("%d\n", err);

  return 0;
}