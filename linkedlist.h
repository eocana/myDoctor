//
// Created by Eric on 18/05/2023.
//

#ifndef MYDOCTOR_LINKEDLIST_H
#define MYDOCTOR_LINKEDLIST_H
#include <stdlib.h>

#define LIST_NO_ERROR 0
#define LIST_ERROR_FULL 1
#define LIST_ERROR_EMPTY 2
#define LIST_ERROR_MALLOC 3
#define LIST_ERROR_END 4
#define MAX_CHAR 50

typedef struct {

    char sintoma[MAX_CHAR];
    int relevancia;

} Sintoma;

typedef Sintoma Element;

typedef struct _Node{
    Element element;
    struct _Node *next;
}Node;

typedef struct {
    int error;
    Node *head;
    Node *previous;
}LinkedList;

LinkedList  LINKEDLIST_Create();
void LINKEDLIST_add(LinkedList *list, Element element);
void LINKEDLIST_remove(LinkedList *list);
Element LINKEDLIST_get(LinkedList *list);
int LINKEDLIST_isEmpty(LinkedList list);
void LINKEDLIST_goToHead(LinkedList *list);
void LINKEDLIST_next(LinkedList *list);
int LINKEDLIST_isAtEnd(LinkedList list);
void LINKEDLIST_destroy(LinkedList *list);
int LINKEDLIST_getErrorCode(LinkedList list);

#endif //MYDOCTOR_LINKEDLIST_H
