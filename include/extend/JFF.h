#ifndef _EXTEND_JFF_
#define _EXTEND_JFF_

typedef uint64_t mword_t;

typedef mword_t (*Method_t)(Object_t, va_list*);

struct Object_c {
  Class_t class;
};

struct Class_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;
};

#endif