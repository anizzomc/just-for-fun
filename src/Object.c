#include <JFF.h>
#include <Object.h>
#include <extend/Object.h>

#include <stdlib.h>
#include <stdio.h>

static struct Class_c object = {NULL, NULL, "Object", sizeof(struct Object_c)};
static struct Class_c objectMeta = {NULL, NULL, "ObjectMeta", sizeof(struct Class_c)};

const Class_t Object = &object;
const Class_t MetaClass = &objectMeta;


static Object_t _new(Class_t class, va_list* list) {

  Object_t obj = malloc(class->instanceSize);
  obj->class = class;

  class->methods[init](obj, list);
  
  return obj;
}

static Class_t _getClass(Object_t this, va_list* list) {
  return this->class;
}

static void _init(Object_t this, va_list* list) {
  return;
}

static int _equals(Object_t this, va_list* list) {
  Object_t other = va_arg(*list, Object_t);
  return other == this;
}

static char* _toString(Object_t this, va_list* list) {
  char *ret = malloc(60); //TODO: Collect memory

  sprintf(ret, "%s@%p", this->class->name, this);

  return ret;
}

static char* _classToString(Class_t this, va_list* list) {
  char *ret = malloc(strlen(this->name)+1); //TODO: Collect memory
  strcpy(ret, this->name);
  return ret;
}

void loadObject(Class_t class) {

  class->class = MetaClass;
  class->superclass = NULL;
  class->methods = malloc(sizeof(Method_t)*_dummyMethod);
  class->methods[init] = (Method_t) &_init;
  class->methods[getClass] = (Method_t) &_getClass;
  class->methods[toString] = (Method_t) &_toString;
  class->methods[equals] = (Method_t) &_equals;
}

void loadObjectClass(Class_t class) {
  loadObject(class);

  class->methods[new] = (Method_t)&_new;
  class->methods[toString] = (Method_t)&_classToString;
  class->superclass = Object;
}


void objectClassLoad() {
  loadObject(Object);
  loadObjectClass(MetaClass);
}

