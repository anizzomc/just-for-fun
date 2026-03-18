#include <JFF.h>
#include <Object.h>
#include <extend/Object.h>
#include <extend/LinkedList.h>
#include <extend/LinkedListIterator.h>
#include <LinkedListIterator.h>

struct LinkedListIterator_c {
  struct Class_c* clazz;
  struct Node_c* current;
};

struct LinkedListIteratorClass_c {
  Class_t clazz;
  Class_t superclazz;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct LinkedListIteratorClass_c linkedListIterator = {};
static struct Class_c linkedListIteratorClass = {};

const Class_t LinkedListIterator = (Class_t) &linkedListIterator;
const Class_t LinkedListIteratorClass = &linkedListIteratorClass;

static void _init(LinkedListIterator_t thiz, va_list* list) {
  thiz->current = va_arg(*list, struct Node_c*);
}

static int _hasNext(LinkedListIterator_t thiz, va_list* list) {
  return thiz->current != NULL;
}

static Object_t _next(LinkedListIterator_t thiz, va_list* list) {
  Object_t data = thiz->current->data;
  thiz->current = thiz->current->next;
  return data;
}

void loadLinkedListIterator(Class_t clazz) {
  loadObject(clazz);

  struct LinkedListIteratorClass_c *lic = clazz;

  lic->clazz = LinkedListIteratorClass;
  lic->superclazz = Object;
  lic->name = "LinkedListIterator";
  lic->instanceSize = sizeof(struct LinkedListIterator_c);

  lic->methods[init]    = (Method_t) &_init;
  lic->methods[hasNext] = (Method_t) &_hasNext;
  lic->methods[next]    = (Method_t) &_next;
}

void loadLinkedListIteratorClass(Class_t clazz) {
  loadClass(clazz);
  clazz->name = "LinkedListIteratorClass";
}

void ClassLoader_LinkedListIterator() {
  loadLinkedListIterator(LinkedListIterator);
  loadLinkedListIteratorClass(LinkedListIteratorClass);
}