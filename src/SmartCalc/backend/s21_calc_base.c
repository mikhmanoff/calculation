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

Node *inverseNode(Node *list) {
    Node *tmp = NULL;

    while (list != NULL) {
        push(&tmp, list->num, list->funType, list->priority);
        pop(&list);
    }

    return tmp;
}
