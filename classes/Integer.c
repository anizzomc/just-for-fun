
#include <extend/Integer.h>
#include <String.h>

struct Integer_c {
  struct Class_c* clazz;
  int value;
};

struct IntegerClass_c {
  Class_t clazz;
  Class_t superclazz;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct IntegerClass_c integer = {};
static struct Class_c integerMeta = {};

const Class_t Integer = &integer;
const Class_t IntegerClass = &integerMeta;

static const Class_t clazz = &integer;

static void _init(Integer_t thiz, va_list* list) {
  int value = va_arg(*list, int);
  thiz->value = value;
}

static String_t _toString(Integer_t thiz, va_list* list) {
  char ret[64];
  sprintf(ret, "%d", thiz->value);
  return send(String, new, ret);
}

static int _equals(Integer_t thiz, va_list* list) {
  Integer_t other = va_arg(*list, Integer_t);
  if(other == NULL) {
    return false;
  }

  if(thiz->clazz != other->clazz) {
    return false;
  }

  return thiz->value == other->value;
}


void loadInteger(Class_t clazz) {
  loadObject(clazz);

  struct IntegerClass_c *ic = clazz;

  ic->clazz = IntegerClass;
  ic->superclazz = Object;
  ic->name = "Integer";
  ic->instanceSize = sizeof(struct Integer_c);


  ic->methods[init] = (Method_t) &_init;
  ic->methods[toString] = (Method_t) &_toString;
  ic->methods[equals] = (Method_t) &_equals;

}


void loadIntegerClass(Class_t clazz) {
  loadClass(clazz);

  clazz->name = "IntegerClass";
}


void ClassLoader_Integer() {
  loadInteger(Integer);
  loadIntegerClass(IntegerClass);
}