#ifndef _STRING_H_
#define _STRING_H_
#include <JFF.h> 
void ClassLoader_String();

typedef struct String_c* String_t;

extern const Class_t String;

/**
##  Class Methods

### new (char * str) -> String_t

  Receibes a char* pointer and creates a new object representing the same string.

  char *s1 = "Hello World!";
  String_t str = send(String, new, s);

- Volatile Retention: The object must be retained if it must be long lived.

  send(str, retain);


## Object Methods

### toCharArray (void) -> char *

  Returns a pointer to a native string with a copy of it's contents. Useful for invoking into standard output

  String_t str = send(String, new, "Hello World!");
  printf("%s\n", send(str, toCharArray));

- Volatite Retention: The object needs to be copied to a long lived place or retained.

  char *ptr = D_mm_retain(send(str, toCharArray));

### toString (void) -> String_t

  Returns the object itself.

  String_t str = send(String, new, "Hello World!");
  String_t same = send(str, toString);

### equals (String_t other) -> int

  Compares two String objects by value. Returns true if both strings have the same content, false otherwise.
  Two strings with different classes or where other is NULL are considered not equal.

  String_t str  = send(String, new, "Hello");
  String_t str2 = send(String, new, "Hello");
  int eq = send(str, equals, str2); // 1

### length (void) -> int

  Returns the number of characters in the string, not counting the null terminator.

  String_t str = send(String, new, "Hello");
  int len = send(str, length); // 5

### retain (void) -> void

  Increments the reference count of the object, preventing it from being deallocated.
  Use this when the object needs to outlive the current memory pool scope.

  String_t str = send(String, new, "Hello World!");
  send(str, retain);

### release (void) -> void

  Decrements the reference count of the object. When the count reaches zero, the object is deallocated.

  send(str, release);

### getClass (void) -> Class_t

  Returns the Class object associated with this String instance.

  String_t str = send(String, new, "Hello");
  Class_t clazz = send(str, getClass); // StringClass

**/
#endif