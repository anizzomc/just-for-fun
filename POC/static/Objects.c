#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


typedef enum {
  new = 0,
  init,
  toString,
  equals,
  lenght
  dummyMethod
} Invoke_t;

#define false 0
#define true !false

typedef struct Object_c* Object_t;
typedef struct Class_c* Class_t;
typedef struct String_c *String_t;

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


struct String_c {
  struct StringClass_c* class;
  char *str;
};

struct StringClass_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t *methods;   
};


void loadClasses();


mword_t send(Object_t obj, Invoke_t method, ...);
mword_t super(Object_t obj, Invoke_t method, ...);

static struct Class_c object = {NULL, NULL, "Object", sizeof(struct Object_c)};
static struct Class_c objectMeta = {NULL, NULL, "ObjectMeta", sizeof(struct Class_c)};

static struct StringClass_c string = {NULL, NULL, "String", sizeof(struct String_c)};
static struct StringClass_c stringMeta = {NULL, NULL, "StringMeta", sizeof(struct StringClass_c)};


const Class_t Object = &object;
const Class_t MetaClass = &objectMeta;

const Class_t String = &string;
const Class_t StringMeta = &stringMeta;

static Object_t objectMetaclass_new(Class_t class, va_list* list) {

  Object_t obj = malloc(class->instanceSize);
  obj->class = class;

  class->methods[init](obj, list);
  
  return obj;
}


static void object_init(Class_t this, va_list* list) {
  return;
}

static int object_equals(Class_t this, va_list* list) {
  Object_t other = va_arg(*list, Object_t);
  return other == this;
}

static char* object_toString(Object_t obj, va_list* list) {
  char *ret = malloc(60);

  sprintf(ret, "%s@%p", obj->class->name, obj);

  return ret;
}

static char* string_toString(String_t this, va_list* list) {
  char *ret = malloc(strlen(this->str)+1);
  strcpy(ret, this->str);
  return ret;
}

static int string_equals(String_t this, va_list* list) {
  String_t other = va_arg(*list, String_t);
  if(other == NULL) {
    return false;
  }
  if(this->class != other->class) {
    return false;
  }

  return strcmp(this->str, other->str) == 0;
}

static int string_lenght(String_t this, va_list* list) {
  return strlen(this->str);
}


static void string_init(String_t this, va_list* list) {
  char *str = va_arg(*list, char*);
  this->str = malloc(strlen(str)+1);
  strcpy(this->str, str);
}


void loadObject(Class_t class) {
  class->class = MetaClass;
  class->superclass = NULL;
  class->methods = malloc(sizeof(Method_t)*dummyMethod);
  class->methods[init] = &object_init;
  class->methods[toString] = &object_toString;
  class->methods[equals] = &object_equals;
}

void loadMetaClass(Class_t class) {
  loadObject(class);

  class->methods[new] = &objectMetaclass_new;
  class->superclass = Object;
}

void loadString(Class_t class) {
  loadObject(class);

  
  class->class = StringMeta;
  class->superclass = Object;
  class->methods[init] = &string_init;
  class->methods[toString] = &string_toString;
  class->methods[equals] = &string_equals;
  class->methods[lenght] = &string_lenght;
}

void loadStringMeta(Class_t class) {
  loadMetaClass(class);
  

  class->class = StringMeta;
  class->superclass = MetaClass;
}


void loadClasses() {
  loadObject(Object);
  loadMetaClass(MetaClass);
  loadString(String);
  loadStringMeta(StringMeta);
}


mword_t super(Object_t obj, Invoke_t method, ...) {
  va_list list;
  va_start(list, method);
  mword_t ret = obj->class->superclass->methods[method](obj, &list);
  va_end(list);
  return ret;
}


mword_t send(Object_t obj, Invoke_t method, ...) {
  va_list list;
  va_start(list, method);

  mword_t ret = obj->class->methods[method](obj, &list);

  va_end(list);
  return ret;
}



int main() {
  loadClasses();
  char *s = "Hello World!\n";
  char *s1 = "Hello World!\n";

  String_t str = send(String, new, s);
  String_t str1 = send(String, new, s1);
  printf("---------------------------\n");
  printf("%s\n", send(str, toString));
  printf("---------------------------\n");
  printf("%d\n", send(str, equals, str1));

}



