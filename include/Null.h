#ifndef _NULL_H_
#define _NULL_H_
#include <JFF.h>

void ClassLoader_Null();

typedef struct Null_c* Null_t;

/**
## Null — Singleton null object

  There is exactly one Null instance in the system, exposed as `Null`.
  Use it to represent the absence of a value.

  Object_t obj = Null;

## Object Methods

### isNull (void) -> int

  Returns true. All other objects return false for this method.

  int result = send(Null, isNull); // 1
  int result = send(anyOther, isNull); // 0

### toString (void) -> String_t

  Returns the string "null".

  String_t s = send(Null, toString);

**/

extern const Object_t Null;

#endif