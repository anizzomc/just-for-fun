#include <JFF.h>
#include <Object.h>
#include <extend/Object.h>
#include <extend/Null.h>
#include <Null.h>
#include <String.h>

struct Null_c {
  struct Class_c* clazz;
};

struct NullClass_c {
  Class_t clazz;
  Class_t superclazz;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

static struct NullClass_c null_c = {};
static struct Class_c nullMeta_c = {};
static struct Null_c null_instance = {};

const Class_t NullClass = &nullMeta_c;
const Object_t Null = (Object_t) &null_instance;

static int _isNull(Null_t thiz, va_list* list) {
  return true;
}

static String_t _toString(Null_t thiz, va_list* list) {
  return send(String, new, "null");
}

static Object_t _new(Class_t thiz, va_list* list) {
  return Null;
}

void loadNull(Class_t clazz) {
  loadObject(clazz);

  struct NullClass_c *nc = clazz;

  nc->clazz = NullClass;
  nc->superclazz = Object;
  nc->name = "Null";
  nc->instanceSize = sizeof(struct Null_c);

  nc->methods[isNull] = (Method_t) &_isNull;
  nc->methods[toString] = (Method_t) &_toString;
  nc->methods[new] = (Method_t) &_new;
}

void loadNullClass(Class_t clazz) {
  loadClass(clazz);
  clazz->name = "NullClass";
}

void ClassLoader_Null() {
  loadNull((Class_t) &null_c);
  loadNullClass(NullClass);
  null_instance.clazz = (struct Class_c*) &null_c;
}