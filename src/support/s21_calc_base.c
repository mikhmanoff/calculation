#include "calc_support.h"

void print(Node *list) {
  if (list == NULL) {
    printf("NULL\n");
    exit(0);
  }
  for (Node *p = list; p != NULL; p = p->next) {
    printf("Приоритет - %d\nЧисло - %lf\nТип - %d\n-------------------\n",
           p->priority, p->num, p->funType);
  }
  printf("\n");
}

void push(Node **pList, double num, funcType funType, int priority) {
  Node *p = malloc(sizeof(Node));
  p->num = num;
  p->priority = priority;
  p->funType = funType;
  p->next = *pList;
  *pList = p;
}

void pop(Node **pList) {
  if (*pList == NULL) {
    exit(0);
  }
  Node *p = *pList;
  *pList = p->next;
  free(p);
}

int isEmpty(Node *List) { return List == NULL; }

int main() {
  Node *list = NULL;

  push(&list, 14.48, tan_t, ULTRA_PRIORITY);
  push(&list, 23.8, sin_t, LOW_PRIORITY);
  push(&list, 4.4, cos_t, MEDIUM_PRIORITY);
  push(&list, 400.4, cos_t, LOW_PRIORITY);

  push(&list, 46.657, mod_t, LOW_PRIORITY);
  push(&list, 344.345, tan_t, HIGH_PRIORITY);
  push(&list, 23324.546, sin_t, ULTRA_PRIORITY);
  push(&list, 2323423.657, atan_t, MEDIUM_PRIORITY);

  //   print(list);
  //   printf("\n\n\n");

  //   print(list);

  //   pop(&list);
  //   printf("\n\n\n\n");

  //   print(list);
  while (!isEmpty(list)) {
    pop(&list);
    if (!isEmpty(list)) {
      printf("%lf\n", list->num);
    };
  }

  return 0;
}