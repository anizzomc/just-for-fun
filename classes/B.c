#include <JFF.h>
#include <extend/JFF.h>
#include <A.h>
#include <B.h>
#include <extend/B.h>
#include <Object.h>

#include <String.h>

#include <strings.h>
#include <stdlib.h>


struct B_c {
  struct Class_c* class;
  int value;
};

struct BClass_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct BClass_c b = {};
static struct Class_c bClass = {};

const Class_t B = &b;
const Class_t BClass = &bClass;

static const Class_t class = &b;


static void _init(B_t this, va_list* list) {
  this->value = va_arg(*list, int);  
}

static String_t _toString(B_t this, va_list* list) {
  char buffer[20];
  sprintf(buffer, "B(%d)", this->value);
  return send(String, new, buffer);
}

static int _test(B_t this, va_list* list) {
  return super(test) + 1;
}


void loadB(Class_t class) {
  loadA(class);

  struct BClass_c *clazz = class;

  // Basic Properties
  clazz->class = BClass;
  clazz->superclass = A;
  clazz->name = "B";
  clazz->instanceSize = sizeof(struct B_c);

  // Instance Methods
  clazz->methods[init] = (Method_t) &_init;
  clazz->methods[toString] = (Method_t) &_toString;
  clazz->methods[test] = (Method_t) &_test;
}

void loadBClass(Class_t class) {
  loadClass(class);
  class->name = "BClass";
}

void ClassLoader_B() {
  loadB(B);
  loadBClass(BClass);
}

