#ifndef _EXTEND_OBJCT_H_
#define _EXTEND_OBJCT_H_

#include <stdint.h>
#include <stdlib.h>

#include <JFF.h>
#include <extend/JFF.h>
#include <Object.h>


extern const Class_t MetaClass;

//TODO: Check if this really should be here
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

void loadObject(Class_t class);

void loadObjectClass(Class_t class);



#endif