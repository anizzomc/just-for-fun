

#include <JFF.h>
#include <extend/Object.h>
#include <ClassLoaders.h>
#include <mm.h>

mword_t super(Object_t obj, Invoke_t method, ...) {
  va_list list;
  va_start(list, method);
  mword_t ret = obj->class->superclass->methods[method](obj, &list);
  va_end(list);
  return ret;
}


mword_t send(Object_t obj, Invoke_t method, ...) {
  va_list list;
  va_start(list, method);

  mword_t ret = obj->class->methods[method](obj, &list);

  va_end(list);
  return ret;
}


void JFF_init() {
  D_mm_init();

  int i;
  int qty = sizeof(classLoaders)/sizeof(ClassLoader_t);

  for(i = 0 ; i < qty ; i++) {
    classLoaders[i]();
  }
}
