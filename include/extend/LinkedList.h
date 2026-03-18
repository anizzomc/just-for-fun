#ifndef _EXTEND_LINKED_LIST_H_
#define _EXTEND_LINKED_LIST_H_

#include <extend/Object.h>
#include <LinkedList.h>

/* Internal node — shared with LinkedListIterator */
struct Node_c {
  Object_t data;
  struct Node_c* next;
};

extern const Class_t LinkedListClass;

void loadLinkedListClass(Class_t clazz);

void loadLinkedList(Class_t clazz);

#endif