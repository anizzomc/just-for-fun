#include <stdlib.h>
#include <stdio.h>

#include <JFF.h>
#include <extend/JFF.h>
#include <Object.h>
#include <extend/Object.h>
#include <String.h>
#include <extend/LinkedList.h>
#include <LinkedList.h>
#include <LinkedListIterator.h>
#include <base/log.h>

struct LinkedList_c {
  struct Class_c* clazz;
  struct Node_c* head;
  struct Node_c* tail;
  int size;
};

struct LinkedListClass_c {
  Class_t clazz;
  Class_t superclazz;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct LinkedListClass_c linkedList = {};
static struct Class_c linkedListClass = {};

const Class_t LinkedList = (Class_t) &linkedList;
const Class_t LinkedListClass = &linkedListClass;

static const Class_t clazz = (Class_t) &linkedList;


static void _init(LinkedList_t thiz, va_list* list) {
  thiz->head = NULL;
  thiz->tail = NULL;
  thiz->size = 0;
}

/* Appends obj at the end of the list */
static void _add(LinkedList_t thiz, va_list* list) {
  Object_t obj = va_arg(*list, Object_t);

  struct Node_c* node = malloc(sizeof(struct Node_c));
  node->data = obj;
  send(obj, retain);
  node->next = NULL;

  if (thiz->head == NULL) {
    thiz->head = node;
    thiz->tail = node;
  } else {
   thiz->tail->next = node;
   thiz->tail = node;
  }

  thiz->size++;
}

/* Returns the object at position index, aborts if out of bounds */
static Object_t _get(LinkedList_t thiz, va_list* list) {
  int index = va_arg(*list, int);

  if (index < 0 || index >= thiz->size) {
    char buffer[128];
    sprintf(buffer, "LinkedList index out of bounds: %d (size=%d)", index, thiz->size);
    ERROR(buffer);
    print_trace();
    exit(1);
  }

  struct Node_c* current = thiz->head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }

  return current->data;
}

/* Removes the node at position index and returns the stored object, aborts if out of bounds */
static Object_t _delete(LinkedList_t thiz, va_list* list) {
  int index = va_arg(*list, int);

  if (index < 0 || index >= thiz->size) {
    char buffer[128];
    sprintf(buffer, "LinkedList index out of bounds: %d (size=%d)", index, thiz->size);
    ERROR(buffer);
    print_trace();
    exit(1);
  }

  struct Node_c* removed;

  if (index == 0) {
    removed = thiz->head;
    thiz->head = thiz->head->next;
  } else {
    struct Node_c* prev = thiz->head;
    for (int i = 0; i < index - 1; i++) {
      prev = prev->next;
    }
    removed = prev->next;
    prev->next = removed->next;
  }

  Object_t data = removed->data;
  free(removed);
  thiz->size--;
  return data;
}

static int _length(LinkedList_t thiz, va_list* list) {
  return thiz->size;
}

static void _dealloc(LinkedList_t thiz, va_list* list) {
  struct Node_c* current = thiz->head;
  while (current != NULL) {
    struct Node_c* next = current->next;
    send(current->data, release);
	free(current);
    current = next;
  }
  thiz->head = NULL;
  thiz->size = 0;
}

static Object_t _iterator(LinkedList_t thiz, va_list* list) {
  return (Object_t) send(LinkedListIterator, new, thiz->head);
}

static String_t _toString(LinkedList_t thiz, va_list* list) {
  char buffer[64];
  sprintf(buffer, "LinkedList[size=%d]", thiz->size);
  return send(String, new, buffer);
}


void loadLinkedList(Class_t clazz) {
  loadObject(clazz);

  struct LinkedListClass_c *lc = (struct LinkedListClass_c*) clazz;

  lc->clazz = LinkedListClass;
  lc->superclazz = Object;
  lc->name = "LinkedList";
  lc->instanceSize = sizeof(struct LinkedList_c);

  lc->methods[init]     = (Method_t) &_init;
  lc->methods[dealloc]  = (Method_t) &_dealloc;
  lc->methods[toString] = (Method_t) &_toString;
  lc->methods[length]   = (Method_t) &_length;
  lc->methods[add]      = (Method_t) &_add;
  lc->methods[get]      = (Method_t) &_get;
  lc->methods[delete]   = (Method_t) &_delete;
  lc->methods[iterator] = (Method_t) &_iterator;
}

void loadLinkedListClass(Class_t clazz) {
  loadClass(clazz);
  clazz->name = "LinkedListClass";
}

void ClassLoader_LinkedList() {
  loadLinkedList(LinkedList);
  loadLinkedListClass(LinkedListClass);
}