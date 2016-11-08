
#include <extend/Integer.h>

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

static struct IntegerClass_c integer = {NULL, NULL, "Integer", sizeof(struct IntegerClass_c)};
static struct IntegerClass_c integerMeta = {NULL, NULL, "IntegerMeta", sizeof(struct IntegerClass_c)};

const Class_t Integer = &integer;
const Class_t IntegerMeta = &integerMeta;

static void _init(Integer_t this, va_list* list) {
  int value = va_arg(*list, int);
  this->value = value;
}

static char* _toString(Integer_t this, va_list* list) {
  //TODO: Collect memory
  char *ret = malloc(11);
  sprintf(ret, "%d", this->value);
  return ret;
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

  clazz->class = IntegerMeta;

  clazz->superclass = Object;

  clazz->methods[init] = (Method_t) &_init;
  clazz->methods[toString] = (Method_t) &_toString;
  clazz->methods[equals] = (Method_t) &_equals;
 
}


void loadIntegerClass(Class_t class) {
  loadObjectClass(class);
  
  struct IntegerClass_c *clazz = class;

  clazz->class = IntegerMeta;
  clazz->superclass = MetaClass;
}

void integerClassLoad() {
  loadInteger(Integer);
  loadIntegerClass(IntegerMeta);
}


