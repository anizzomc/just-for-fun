#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include <JFF.h>
#include <Object.h>
#include <extend/Object.h>
#include <extend/String.h>
#include <String.h>

#include <mm.h>
#include <mm_pool.h>

struct String_c {
  struct Class_c* clazz;
  char *str;
};

struct StringClass_c {
  Class_t clazz;
  Class_t superclazz;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};


static struct StringClass_c string = {};
static struct Class_c stringClass = {};

const Class_t String = &string;
const Class_t StringClass = &stringClass;

static const Class_t clazz = &string;

static char* _toCharArray(String_t thiz, va_list* list) {
  char *ret = D_mm_pool_add(D_mm_alloc(strlen(thiz->str)+1, NULL));
  strcpy(ret, thiz->str);
  return ret;
}

static String_t _toString(String_t thiz, va_list* list) {
  return thiz;
}

static int _equals(String_t thiz, va_list* list) {
  String_t other = va_arg(*list, String_t);
  if(other == NULL) {
    return false;
  }
  if(thiz->clazz != other->clazz) {
    return false;
  }

  return strcmp(thiz->str, other->str) == 0;
}

static int _length(String_t thiz, va_list* list) {
  return strlen(thiz->str);
}


static void _init(String_t thiz, va_list* list) {
  char *str = va_arg(*list, char*);
  thiz->str = malloc(strlen(str)+1); //TODO: Collect memory when deallocking the object
  strcpy(thiz->str, str);
}


void loadString(Class_t clazz) {
  loadObject(clazz);

  struct StringClass_c *sc = clazz;

  // Basic Properties
  sc->clazz = StringClass;
  sc->superclazz = Object;
  sc->name = "String";
  sc->instanceSize = sizeof(struct String_c);


  // Instance Methods
  sc->methods[init] = (Method_t) &_init;
  sc->methods[toString] = (Method_t) &_toString;
  sc->methods[toCharArray] = (Method_t) &_toCharArray;
  sc->methods[equals] = (Method_t) &_equals;
  sc->methods[length] = (Method_t) &_length;
}

void loadStringClass(Class_t clazz) {
  loadClass(clazz);

  clazz->name = "StringClass";

}

void ClassLoader_String() {
  loadString(String);
  loadStringClass(StringClass);
}