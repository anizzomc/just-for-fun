#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>


typedef uint64_t (*Method_t)(void *obj, va_list* list);

uint64_t a_fnc(void *obj, va_list* list) {
  printf("%p\n", va_arg(*list, char*));
  return 0;
}

uint64_t my_method(void *obj, va_list* list) {
  return a_fnc(obj, list);
}

uint64_t send(void *obj, Method_t method, ...) {
  va_list list;
  va_start(list, method);
  uint64_t ret = method(obj, &list);
  va_end(list);
  return ret;
}


int main(void) {
  char *str = "My Str";

  printf("%p\n", str);

  send(NULL, my_method, str);


}



