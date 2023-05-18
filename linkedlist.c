//
// Created by Eric on 18/05/2023.
//

#include "linkedlist.h"


LinkedList LINKEDLIST_Create(){
    LinkedList list;
    list.head = (Node*) malloc(sizeof (Node));
    if(list.head == NULL){
        list.error = LIST_ERROR_MALLOC;
    } else{
        list.error = LIST_NO_ERROR;
        list.previous = list.head;
        list.previous->next = NULL;
    }

    return list;
}


void LINKEDLIST_add (LinkedList * list, Element element) {
    // 1- Create a new node to store the new element.
    Node * new_node = (Node*) malloc (sizeof(Node));
    if (NULL != new_node) {
        // 2- Set the element field in the new node with the provided element.
        new_node->element = element;
        // 3- Set the next field in the new node.
        //    The next node will be the node in the point of view.
        new_node->next = list->previous->next;

        // 4- Link the new node to the list. The new node will go before the
        //    point of view, so
        list->previous->next = new_node;
        // 5- Move the previous pointer.
        list->previous = new_node;

        // As everything was fine, set the error code to NO_ERROR
        list->error = LIST_NO_ERROR;

    }else{

        // Could not get dynamic memory for the new node, so we set the
        //  error to malloc error code.
        list->error = LIST_ERROR_MALLOC;

    }
}


void LINKEDLIST_remove(LinkedList *list){
    Node *aux;
    if(LINKEDLIST_isAtEnd(*list)){
        list->error = LIST_ERROR_END;
    } else{
        list->error = LIST_NO_ERROR;
        aux= list->previous;
        list->previous = aux->next;
        free(aux);
    }
}

Element LINKEDLIST_get(LinkedList *list){
    Element element;
    if(LINKEDLIST_isAtEnd(*list)){
        list->error = LIST_ERROR_END;
    }else{
        list->error = LIST_NO_ERROR;
        element = list->previous->next->element;
    }

    return element;
}

int LINKEDLIST_isEmpty(LinkedList list){
    return list.head->next == NULL;
}

void LINKEDLIST_goToHead(LinkedList *list){
    list->previous = list->head;
}

void LINKEDLIST_next(LinkedList *list){
    if(LINKEDLIST_isEmpty(*list)){
        list->error = LIST_ERROR_END;
    } else{
        list->error = LIST_NO_ERROR;
        list->previous = list->previous->next;
    }
}

int LINKEDLIST_isAtEnd(LinkedList list){
    return list.previous->next == NULL;
}

void LINKEDLIST_destroy(LinkedList *list){
    LINKEDLIST_goToHead(list);
    while(!LINKEDLIST_isEmpty(*list)){
        LINKEDLIST_remove(list);
    }
    free(list->head);
}

int LINKEDLIST_getErrorCode(LinkedList list){
    return list.error;
}


