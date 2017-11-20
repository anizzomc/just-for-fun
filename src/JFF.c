

#include <JFF.h>
#include <extend/Object.h>
#include <mm.h>
#include <mm_pool.h>

void LoadClasses(void);

D_mm_pool_conf pool_conf = {100, 100};

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
  D_mm_pool_init(pool_conf);

  LoadClasses();
 
}


