#include <stdlib.h>
#include <stdio.h>

#include <JFF.h>
#include <Object.h>
#include <extend/Object.h>
#include <String.h>
#include <extend/ArrayList.h>
#include <ArrayList.h>
#include <base/log.h>

#define DEFAULT_CAPACITY 16

struct ArrayList_c {
  struct Class_c* clazz;
  Object_t* data;   // underlying array of object pointers
  int size;         // number of elements currently stored
  int capacity;     // allocated capacity of the array
};

struct ArrayListClass_c {
  Class_t clazz;
  Class_t superclazz;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct ArrayListClass_c arrayList = {};
static struct Class_c arrayListClass = {};

const Class_t ArrayList = (Class_t) &arrayList;
const Class_t ArrayListClass = &arrayListClass;

static void _resize(ArrayList_t thiz) {
  thiz->capacity *= 2;
  thiz->data = realloc(thiz->data, sizeof(Object_t) * thiz->capacity);
}

static void _init(ArrayList_t thiz, va_list* list) {
  int initialCapacity = va_arg(*list, int);
  thiz->capacity = initialCapacity > 0 ? initialCapacity : DEFAULT_CAPACITY;
  thiz->data = malloc(sizeof(Object_t) * thiz->capacity);
  thiz->size = 0;
}

static void _add(ArrayList_t thiz, va_list* list) {
  Object_t obj = va_arg(*list, Object_t);

  if (thiz->size == thiz->capacity) {
    _resize(thiz);
  }

  thiz->data[thiz->size++] = obj;
  send(obj, retain);
}

static Object_t _get(ArrayList_t thiz, va_list* list) {
  int index = va_arg(*list, int);

  if (index < 0 || index >= thiz->size) {
    char buffer[128];
    sprintf(buffer, "ArrayList index out of bounds: %d (size=%d)", index, thiz->size);
    ERROR(buffer);
    print_trace();
    exit(1);
  }

  return thiz->data[index];
}

static Object_t _delete(ArrayList_t thiz, va_list* list) {
  int index = va_arg(*list, int);

  if (index < 0 || index >= thiz->size) {
    char buffer[128];
    sprintf(buffer, "ArrayList index out of bounds: %d (size=%d)", index, thiz->size);
    ERROR(buffer);
    print_trace();
    exit(1);
  }

  Object_t data = thiz->data[index];

  // Shift elements down to fill the gap
  for (int i = index; i < thiz->size - 1; i++) {
    thiz->data[i] = thiz->data[i + 1];
  }

  thiz->size--;
  return data;
}

static int _length(ArrayList_t thiz, va_list* list) {
  return thiz->size;
}

static void _dealloc(ArrayList_t thiz, va_list* list) {
  for (int i = 0; i < thiz->size; i++) {
    send(thiz->data[i], release);
  }
  free(thiz->data);
  thiz->data = NULL;
  thiz->size = 0;
  thiz->capacity = 0;
}

static String_t _toString(ArrayList_t thiz, va_list* list) {
  char buffer[64];
  sprintf(buffer, "ArrayList[size=%d,capacity=%d]", thiz->size, thiz->capacity);
  return send(String, new, buffer);
}

void loadArrayList(Class_t clazz) {
  loadObject(clazz);

  struct ArrayListClass_c *ac = clazz;

  ac->clazz = ArrayListClass;
  ac->superclazz = Object;
  ac->name = "ArrayList";
  ac->instanceSize = sizeof(struct ArrayList_c);

  ac->methods[init]    = (Method_t) &_init;
  ac->methods[dealloc] = (Method_t) &_dealloc;
  ac->methods[toString]= (Method_t) &_toString;
  ac->methods[length]  = (Method_t) &_length;
  ac->methods[add]     = (Method_t) &_add;
  ac->methods[get]     = (Method_t) &_get;
  ac->methods[delete]  = (Method_t) &_delete;
}

void loadArrayListClass(Class_t clazz) {
  loadClass(clazz);
  clazz->name = "ArrayListClass";
}

void ClassLoader_ArrayList() {
  loadArrayList(ArrayList);
  loadArrayListClass(ArrayListClass);
}
