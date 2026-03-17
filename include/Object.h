#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <JFF.h>

void ClassLoader_Object();

/**
## Object — Root class of the class hierarchy

  Every class extends Object. It provides the base set of methods
  available to all objects in the framework.

## Class Methods

### new (void) -> Object_t

  Allocates and initializes a new instance of the receiving class.

  Object_t obj = send(Object, new);

- Volatile Retention: The object must be retained if it must be long lived.

  send(obj, retain);

## Object Methods

### init (void) -> void

  Called automatically by new after allocation. Override in subclasses
  to initialize instance fields. The base implementation does nothing.

### dealloc (void) -> void

  Called when the object is released and its reference count reaches zero.
  Override in subclasses to free any manually managed resources.

### retain (void) -> void

  Increments the reference count, preventing the object from being deallocated.

  send(obj, retain);

### release (void) -> void

  Decrements the reference count. When it reaches zero the object is deallocated.

  send(obj, release);

### getClass (void) -> Class_t

  Returns the Class object this instance belongs to.

  Class_t clazz = send(obj, getClass);

### toString (void) -> String_t

  Returns a human-readable String representation of the object.
  The default format is "ClassName@address".

  String_t s = send(obj, toString);

### equals (Object_t other) -> int

  Returns true if this object and other are the same instance.
  Subclasses should override this for value-based comparison.

  int eq = send(obj, equals, other);

### isNull (void) -> int

  Returns false for all objects. Only the Null singleton returns true.

  int result = send(obj, isNull); // 0

### respondsTo (Invoke_t method) -> int

  Returns true if the class has defined the given method, false if it has not
  been overridden from the base undefined sentinel.

  int defined = send(obj, respondsTo, toString); // 1
  int defined = send(obj, respondsTo, nextID);   // 0

**/

extern const Class_t Object;

#endif
