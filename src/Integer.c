
#include <extend/Integer.h>
#include <String.h>

struct Integer_c {
  struct Class_c* class;
  int value;
};

struct IntegerClass_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct IntegerClass_c integer = {};
static struct Class_c integerMeta = {};

const Class_t Integer = &integer;
const Class_t IntegerClass = &integerMeta;

static void _init(Integer_t this, va_list* list) {
  int value = va_arg(*list, int);
  this->value = value;
}

static String_t _toString(Integer_t this, va_list* list) {
  char ret[64];
  sprintf(ret, "%d", this->value);
  return send(String, new, ret);
}

static int _equals(Integer_t this, va_list* list) {
  Integer_t other = va_arg(*list, Integer_t);
  if(other == NULL) {
    return false;
  }

  if(this->class != other->class) {
    return false;
  }

  return this->value == other->value;
}


void loadInteger(Class_t class) {
  loadObject(class);

  struct IntegerClass_c *clazz = class;

  clazz->class = IntegerClass;
  clazz->superclass = Object;
  clazz->name = "Integer";
  clazz->instanceSize = sizeof(struct Integer_c);


  clazz->methods[init] = (Method_t) &_init;
  clazz->methods[toString] = (Method_t) &_toString;
  clazz->methods[equals] = (Method_t) &_equals;
 
}


void loadIntegerClass(Class_t class) {
  loadClass(class);

  class->name = "IntegerClass";
}


void integerClassLoad() {
  loadInteger(Integer);
  loadIntegerClass(IntegerClass);
}


