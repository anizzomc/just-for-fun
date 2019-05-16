#ifndef _EXTEND_OBJCT_H_
#define _EXTEND_OBJCT_H_

#include <stdint.h>
#include <stdlib.h>

#include <JFF.h>
#include <extend/JFF.h>
#include <Object.h>


extern const Class_t Class;

void loadObject(Class_t class);

void loadClass(Class_t class);

#endif