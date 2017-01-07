#ifndef _EXTEND_ENTITY_H_
#define _EXTEND_ENTITY_H_

#include <extend/Object.h>
#include <Entity.h>

/**
 The intention of this class is to give an
 idea of how class methods and instance 
 methods would work together
*/

extern const Class_t EntityClass;

void loadEntityClass(Class_t class);

void loadEntity(Class_t class);

#endif