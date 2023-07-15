#include "calc_core.h"

Node *s21_infixToPolsih(Node *list, double xValue) {
  list = inverseNode(list);
  Node *stack = NULL;
  Node *polish = NULL;

  while (list) {
    printf("!\n");
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
      while (stack->funType != left_bracket_t) {
        printf("###################\n");
        printf("%d\n", stack->funType);
        printf("###################\n");
        push(&polish, stack->num, stack->funType, stack->priority);
        pop(&stack);
      }

      pop(&stack);
    }

    pop(&list);
  }

  while (stack) {
    push(&polish, stack->num, stack->funType, stack->priority);
    pop(&stack);
  }

  polish = inverseNode(polish);
  return polish;
}

// void printStack(Node *stack) {
//   if (list == NULL) {
//     printf("NULL\n");
//     exit(0);
//   }
//   for (Node *p = list; p != NULL; p = p->next) {
//     printf("Приоритет - %d\nЧисло - %lf\nТип - %d\n-------------------\n",
//            p->priority, p->num, p->funType);
//   }
//   printf("\n");
// }

int main() {
  char str_1[200] = "acos(1)*asin(1)";  // -0.1+0.2

  Node *number_list = parseInput(str_1);

  print(number_list);
  printf("\n\n\n");
  // number_list = inverseNode(number_list);

  number_list = s21_infixToPolsih(number_list, 0);

  print(number_list);

  return 0;
}
