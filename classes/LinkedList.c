#include <stdlib.h>
#include <stdio.h>

#include <JFF.h>
#include <extend/JFF.h>
#include <Object.h>
#include <extend/Object.h>
#include <String.h>
#include <extend/LinkedList.h>
#include <LinkedList.h>

/* Internal node — not a JFF object, managed manually */
struct Node_c {
  Object_t data;
  struct Node_c* next;
};

struct LinkedList_c {
  struct Class_c* class;
  struct Node_c* head;
  int size;
};

struct LinkedListClass_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct LinkedListClass_c linkedList = {};
static struct Class_c linkedListClass = {};

const Class_t LinkedList = (Class_t) &linkedList;
const Class_t LinkedListClass = &linkedListClass;

static const Class_t class = (Class_t) &linkedList;


static void _init(LinkedList_t this, va_list* list) {
  this->head = NULL;
  this->size = 0;
}

/* Appends obj at the end of the list */
static void _add(LinkedList_t this, va_list* list) {
  Object_t obj = va_arg(*list, Object_t);

  struct Node_c* node = malloc(sizeof(struct Node_c));
  node->data = obj;
  node->next = NULL;

  if (this->head == NULL) {
    this->head = node;
  } else {
    struct Node_c* current = this->head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = node;
  }

  this->size++;
}

/* Returns the object at position index, or NULL if out of bounds */
static Object_t _get(LinkedList_t this, va_list* list) {
  int index = va_arg(*list, int);

  if (index < 0 || index >= this->size) {
    return NULL;
  }

  struct Node_c* current = this->head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }

  return current->data;
}

/* Removes the node at position index and returns the stored object, or NULL if out of bounds */
static Object_t _delete(LinkedList_t this, va_list* list) {
  int index = va_arg(*list, int);

  if (index < 0 || index >= this->size) {
    return NULL;
  }

  struct Node_c* removed;

  if (index == 0) {
    removed = this->head;
    this->head = this->head->next;
  } else {
    struct Node_c* prev = this->head;
    for (int i = 0; i < index - 1; i++) {
      prev = prev->next;
    }
    removed = prev->next;
    prev->next = removed->next;
  }

  Object_t data = removed->data;
  free(removed);
  this->size--;
  return data;
}

static int _length(LinkedList_t this, va_list* list) {
  return this->size;
}

static void _dealloc(LinkedList_t this, va_list* list) {
  struct Node_c* current = this->head;
  while (current != NULL) {
    struct Node_c* next = current->next;
    free(current);
    current = next;
  }
  this->head = NULL;
  this->size = 0;
}

static String_t _toString(LinkedList_t this, va_list* list) {
  char buffer[64];
  sprintf(buffer, "LinkedList[size=%d]", this->size);
  return send(String, new, buffer);
}


void loadLinkedList(Class_t class) {
  loadObject(class);

  struct LinkedListClass_c *clazz = (struct LinkedListClass_c*) class;

  clazz->class = LinkedListClass;
  clazz->superclass = Object;
  clazz->name = "LinkedList";
  clazz->instanceSize = sizeof(struct LinkedList_c);

  clazz->methods[init]     = (Method_t) &_init;
  clazz->methods[dealloc]  = (Method_t) &_dealloc;
  clazz->methods[toString] = (Method_t) &_toString;
  clazz->methods[length]   = (Method_t) &_length;
  clazz->methods[add]      = (Method_t) &_add;
  clazz->methods[get]      = (Method_t) &_get;
  clazz->methods[delete]   = (Method_t) &_delete;
}

void loadLinkedListClass(Class_t class) {
  loadClass(class);
  class->name = "LinkedListClass";
}

void ClassLoader_LinkedList() {
  loadLinkedList(LinkedList);
  loadLinkedListClass(LinkedListClass);
}