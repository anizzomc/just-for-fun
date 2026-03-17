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
  struct Class_c* clazz;
  int value;
};

struct BClass_c {
  Class_t clazz;
  Class_t superclazz;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct BClass_c b = {};
static struct Class_c bClass = {};

const Class_t B = &b;
const Class_t BClass = &bClass;

static const Class_t clazz = &b;


static void _init(B_t thiz, va_list* list) {
  thiz->value = va_arg(*list, int);
}

static String_t _toString(B_t thiz, va_list* list) {
  char buffer[20];
  sprintf(buffer, "B(%d)", thiz->value);
  return send(String, new, buffer);
}

static int _test(B_t thiz, va_list* list) {
  return super(test) + 1;
}


void loadB(Class_t clazz) {
  loadA(clazz);

  struct BClass_c *bc = clazz;

  // Basic Properties
  bc->clazz = BClass;
  bc->superclazz = A;
  bc->name = "B";
  bc->instanceSize = sizeof(struct B_c);

  // Instance Methods
  bc->methods[init] = (Method_t) &_init;
  bc->methods[toString] = (Method_t) &_toString;
  bc->methods[test] = (Method_t) &_test;
}

void loadBClass(Class_t clazz) {
  loadClass(clazz);
  clazz->name = "BClass";
}

void ClassLoader_B() {
  loadB(B);
  loadBClass(BClass);
}
