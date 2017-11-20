#include <JFF.h>
#include <Object.h>
#include <String.h>
#include <extend/Object.h>

#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

#include <mm.h>
#include <mm_pool.h>

static struct Class_c object = {};
static struct Class_c class = {};

const Class_t Object = &object;
const Class_t Class = &class;

static void _dealloc_handler(Object_t);

static Object_t _new(Class_t class, va_list* list) {

  Object_t obj = D_mm_pool_add(D_mm_alloc(class->instanceSize, _dealloc_handler));
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

static void _dealloc(Object_t this) {
  // Do a release of it parts
  return;
}

static int _equals(Object_t this, va_list* list) {
  Object_t other = va_arg(*list, Object_t);
  return other == this;
}

static char* _toString(Object_t this, va_list* list) {
  char buffer[60];

  sprintf(buffer, "%s@%p", this->class->name, this);

  return send(String, new, buffer);
}

static void _retain(Object_t this, va_list* list) {
  D_mm_retain(this);
}

static void _release(Object_t this, va_list* list) {
  D_mm_release(this);
}

static char* _classToString(Class_t this, va_list* list) {
  return send(String, new, this->name);
}

void loadObject(Class_t class) {

  // Basic Properties
  class->class = Class;
  class->superclass = NULL;
  class->name = "Object";
  class->instanceSize = sizeof(struct Object_c);

  // Custom Properties


  // Instance Methods
  class->methods = malloc(sizeof(Method_t)*_dummyMethod);
  class->methods[init] = (Method_t) &_init;
  class->methods[dealloc] = (Method_t) &_dealloc;
  class->methods[retain] = (Method_t) &_retain;
  class->methods[release] = (Method_t) &_release;
  class->methods[getClass] = (Method_t) &_getClass;
  class->methods[toString] = (Method_t) &_toString;
  class->methods[equals] = (Method_t) &_equals;
}

void loadClass(Class_t class) {
  loadObject(class);

  class->class = Class;
  class->superclass = Object;
  class->name = "Class";

  // Instance Methods
  class->methods[new] = (Method_t)&_new;
  class->methods[toString] = (Method_t)&_classToString;
}


void ClassLoader_Object() {
  loadObject(Object);
  loadClass(Class);
}


static void _dealloc_handler(Object_t obj) {
  send(obj, dealloc);
}

