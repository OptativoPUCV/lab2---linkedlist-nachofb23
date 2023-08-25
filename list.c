#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* newList = (List*)malloc(sizeof(List));
  if (newList == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria para la lista.");
    exit(1);
  }

  newList->head = NULL;
  return newList;
}

void * firstList(List * list) {
  if (list->head != NULL) {
    list->current = list->head;
    return list->head->data;
  }
  return NULL;
}  


void * nextList(List * list) {
  if (list->current == NULL) {
    return NULL;
  }

  if (list->current->next != NULL) {
    list->current = list->current->next;
    return list->current->data;
  }
  
  return NULL;
}

void * lastList(List * list) {
  if (list->head == NULL) {
    return NULL;
  }

  Node* current = list->head;
  while (current->next != NULL) {
    current = current->next;
  }

  list->current = current;
  return current->data;
}

void * prevList(List * list) {
  if (list->head == NULL || list->current == NULL || list->current == list->head) {
    return NULL;
  }

  Node* current = list->head;
  while (current->next != list->current) {
    current = current->next;
  }

  list->current = current;
  return current->data;
}

void pushFront(List * list, void * data) {
  Node* newNode = createNode(data);

  if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
  } else {
    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
  }
}

void pushBack(List * list, void * data) {
}

void pushCurrent(List * list, void * data) {
  if (list->current == NULL) {
    return;
  }

  Node* newNode = createNode(data);
  newNode->prev = list->current;
  newNode->next = list->current->next;

  if (list->current->next) {
    list->current->next->prev = newNode;
  } else {
    list->tail = newNode;
  }

  list->current->next = newNode;
} 

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list->current == NULL) {
    return NULL;
  }
  void* data = list->current->data;
  Node* toDelete = list->current;

  if (list->current->prev) {
    list->current->prev->next = list->current->next;
  } else {
    list->head = list->current->next;
  }
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}