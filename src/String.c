#include <strings.h>
#include <stdlib.h>

#include <JFF.h>
#include <Object.h>
#include <extend/Object.h>
#include <extend/String.h>
#include <String.h>

#include <mm.h>
#include <mm_pool.h>

struct String_c {
  struct Class_c* class;
  char *str;
};

struct StringClass_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};


static struct StringClass_c string = {};
static struct Class_c stringClass = {};

const Class_t String = &string;
const Class_t StringClass = &stringClass;

static char* _toCharArray(String_t this, va_list* list) {
  char *ret = D_mm_pool_add(D_mm_alloc(strlen(this->str)+1, NULL));
  strcpy(ret, this->str);
  return ret;
}

static String_t _toString(String_t this, va_list* list) {
  return this;
}

static int _equals(String_t this, va_list* list) {
  String_t other = va_arg(*list, String_t);
  if(other == NULL) {
    return false;
  }
  if(this->class != other->class) {
    return false;
  }

  return strcmp(this->str, other->str) == 0;
}

static int _lenght(String_t this, va_list* list) {
  return strlen(this->str);
}


static void _init(String_t this, va_list* list) {
  char *str = va_arg(*list, char*);
  this->str = malloc(strlen(str)+1); //TODO: Collect memory
  strcpy(this->str, str);
}


void loadString(Class_t class) {
  loadObject(class);

  struct StringClass_c *clazz = class;

  // Basic Properties
  clazz->class = StringClass;
  clazz->superclass = Object;
  clazz->name = "String";
  clazz->instanceSize = sizeof(struct String_c);


  // Instance Methods
  clazz->methods[init] = (Method_t) &_init;
  clazz->methods[toString] = (Method_t) &_toString;
  clazz->methods[toCharArray] = (Method_t) &_toCharArray;
  clazz->methods[equals] = (Method_t) &_equals;
  clazz->methods[lenght] = (Method_t) &_lenght;
}

void loadStringClass(Class_t class) {
  loadClass(class);

  class->name = "StringClass";

}

void stringClassLoad() {
  loadString(String);
  loadStringClass(StringClass);
}
