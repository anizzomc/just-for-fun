#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <JFF.h> 

void entityClassLoad();

/**
 The intention of this class is to give an
 idea of how class methods and instance 
 methods would work together
*/

typedef struct Entity_c* Entity_t;

extern const Class_t Entity;

#endif