#include <JFF.h>



struct Application_c {
  struct Class_c* class;
  char *str;
};

struct ApplicationClass_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};