#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <JFF.h>

void ClassLoader_ArrayList();

typedef struct ArrayList_c* ArrayList_t;

/**
## ArrayList — Dynamic array backed collection

  Stores object pointers in a contiguous array. An initial capacity is set
  at construction. When the array is full, it automatically doubles in size.

## Class Methods

### new (int initialCapacity) -> ArrayList_t

  Creates a new ArrayList with the given initial capacity.
  If initialCapacity is <= 0, a default capacity of 16 is used.

  ArrayList_t list = (ArrayList_t) send(ArrayList, new, 8);

- Volatile Retention: The object must be retained if it must be long lived.

  send((Object_t) list, retain);

## Object Methods

### add (Object_t obj) -> void

  Appends obj at the end of the list. Retains the object.
  Resizes the underlying array (doubling capacity) if needed.

  send((Object_t) list, add, obj);

### get (int index) -> Object_t

  Returns the object at position index, or NULL if out of bounds.

  Object_t obj = (Object_t) send((Object_t) list, get, 0);

### delete (int index) -> Object_t

  Removes and returns the object at position index, shifting subsequent
  elements down. Returns NULL if out of bounds. Ownership is transferred
  to the caller — the caller is responsible for releasing it.

  Object_t obj = (Object_t) send((Object_t) list, delete, 0);

### length (void) -> int

  Returns the number of elements currently in the list.

  int n = (int) send((Object_t) list, length);

### toString (void) -> String_t

  Returns a string of the form "ArrayList[size=N,capacity=M]".

  String_t s = send((Object_t) list, toString);

**/

extern const Class_t ArrayList;

#endif
