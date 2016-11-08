

#include <JFF.h>
#include <extend/Object.h>

extern const int classLoadersQty;

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


void jff_loadClasses() {
  int i;
  for(i = 0 ; i < classLoadersQty ; i++) {
    classLoaders[i]();
  }
}
