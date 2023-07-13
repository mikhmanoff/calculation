#include "calc_core.h"

Node *s21_infixToPolsih(Node *list, double xValue) {
  list = inverseNode(list);
  Node *stack = NULL;
  Node *polish = NULL;

  while (list) {
    if (operatorCheck(list->funType) || functionCheck(list->funType)) {
      if (stack == NULL) {
        push(&stack, list->num, list->funType, list->priority);
      } else if (stack->priority < list->priority ||
                 stack->funType == left_bracket_t) {
        push(&stack, list->num, list->funType, list->priority);
      } else if (stack->priority == list->priority) {
        push(&polish, stack->num, stack->funType, stack->priority);
        pop(&stack);
        push(&stack, list->num, list->funType, list->priority);
      } else {
        push(&polish, stack->num, stack->funType, stack->priority);

        pop(&stack);

        if (polish->priority >= 2) {
          if (stack != NULL) {
            if (stack->priority >= 1 && stack->priority != 5) {
              push(&polish, stack->num, stack->funType, stack->priority);
              pop(&stack);
            }
          }
        }

        push(&stack, list->num, list->funType, list->priority);
      }
    }

    if (list->funType == left_bracket_t) {
      push(&stack, list->num, list->funType, list->priority);
    }

    if (list->funType == number || list->funType == zero ||
        list->funType == X) {
      if (list->funType == X) {
        list->num = xValue;
      }
      push(&polish, list->num, list->funType, list->priority);
    }

    if (list->funType == right_bracket_t) {
      if (stack != NULL) {
        while (stack != NULL) {
          push(&polish, stack->num, stack->funType, stack->priority);
          pop(&stack);
        }
      }
      pop(&stack);
    }
    // print(list);
    // printf("\n\n\n");
    pop(&list);
  }

  while (stack) {
    push(&polish, stack->num, stack->funType, stack->priority);
    pop(&stack);
  }

  polish = inverseNode(polish);
  return polish;
}

int main() {
  char str_1[200] = "12/(5*3)^2";  // -0.1+0.2

  Node *number_list = parseInput(str_1);

  print(number_list);
  printf("\n\n\n");
  // number_list = inverseNode(number_list);

  number_list = s21_infixToPolsih(number_list, 0);

  print(number_list);

  return 0;
}