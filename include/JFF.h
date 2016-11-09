#ifndef _JFF_H_
#define _JFF_H_

#include <stdint.h>
#include <stdarg.h>

#include <JFFConfig.h>

#define false 0
#define true !false

//Base Object Definition
typedef struct Object_c* Object_t;
typedef struct Class_c* Class_t;

typedef uint64_t mword_t;

// Method invocation
mword_t send(Object_t obj, Invoke_t method, ...);

// Super method invocation, should be used only in clases.
mword_t super(Object_t obj, Invoke_t method, ...);

//Class Loader
// TODO: Should be replaced by "init"?
void jff_loadClasses();


#endif