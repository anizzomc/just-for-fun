#include <JFF.h>
#include <extend/JFF.h>
#include <A.h>
#include <Object.h>
#include <extend/Object.h>

#include <String.h>

#include <strings.h>
#include <stdlib.h>


struct A_c {
  struct Class_c* class;
  int value;
};

struct AClass_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct AClass_c a = {};
static struct Class_c aClass = {};

const Class_t A = &a;
const Class_t AClass = &aClass;

static const Class_t class = &a;


static void _init(A_t this, va_list* list) {
  this->value = va_arg(*list, int);  
}

static int _test(A_t this, va_list* list) {
  return 1;
}

static String_t _toString(A_t this, va_list* list) {
  char buffer[20];
  sprintf(buffer, "A(%d)", this->value);
  return send(String, new, buffer);
}

void loadA(Class_t class) {
  loadObject(class);

  struct AClass_c *clazz = class;

  // Basic Properties
  clazz->class = AClass;
  clazz->superclass = Object;
  clazz->name = "A";
  clazz->instanceSize = sizeof(struct A_c);

  // Instance Methods
  clazz->methods[init] = (Method_t) &_init;
  clazz->methods[toString] = (Method_t) &_toString;
  clazz->methods[test] = (Method_t) &_test;

}

void loadAClass(Class_t class) {
  loadClass(class);
  class->name = "AClass";
}

void ClassLoader_A() {
  loadA(A);
  loadAClass(AClass);
}

