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
static struct Class_c class_c = {};

const Class_t Object = &object;
const Class_t Class = &class_c;

static const Class_t clazz = &object;

static void _dealloc_handler(Object_t);

static Object_t _new(Class_t clazz, va_list* list) {

  Object_t obj = D_mm_pool_add(D_mm_alloc(clazz->instanceSize, _dealloc_handler));
  obj->clazz = clazz;

  clazz->methods[init](obj, list);

  return obj;
}


static Class_t _getClass(Object_t thiz, va_list* list) {
  return thiz->clazz;
}

static void _init(Object_t thiz, va_list* list) {
  return;
}

static void _dealloc(Object_t thiz) {
  // Do a release of it parts
  return;
}

static int _equals(Object_t thiz, va_list* list) {
  Object_t other = va_arg(*list, Object_t);
  return other == thiz;
}

static char* _toString(Object_t thiz, va_list* list) {
  char buffer[60];

  sprintf(buffer, "%s@%p", thiz->clazz->name, thiz);

  return send(String, new, buffer);
}

static void _retain(Object_t thiz, va_list* list) {
  D_mm_retain(thiz);
}

static void _release(Object_t thiz, va_list* list) {
  D_mm_release(thiz);
}

static char* _classToString(Class_t thiz, va_list* list) {
  return send(String, new, thiz->name);
}

void loadObject(Class_t clazz) {

  // Basic Properties
  clazz->clazz = Class;
  clazz->superclazz = NULL;
  clazz->name = "Object";
  clazz->instanceSize = sizeof(struct Object_c);

  // Custom Properties


  // Instance Methods
  clazz->methods = malloc(sizeof(Method_t)*_dummyMethod);
  clazz->methods[init] = (Method_t) &_init;
  clazz->methods[dealloc] = (Method_t) &_dealloc;
  clazz->methods[retain] = (Method_t) &_retain;
  clazz->methods[release] = (Method_t) &_release;
  clazz->methods[getClass] = (Method_t) &_getClass;
  clazz->methods[toString] = (Method_t) &_toString;
  clazz->methods[equals] = (Method_t) &_equals;
}

void loadClass(Class_t clazz) {
  loadObject(clazz);

  clazz->clazz = Class;
  clazz->superclazz = Object;
  clazz->name = "Class";

  // Instance Methods
  clazz->methods[new] = (Method_t)&_new;
  clazz->methods[toString] = (Method_t)&_classToString;
}


void ClassLoader_Object() {
  loadObject(Object);
  loadClass(Class);
}


static void _dealloc_handler(Object_t obj) {
  send(obj, dealloc);
}

