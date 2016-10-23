#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#define false 0
#define true !false

typedef struct Object_c* Object_t;
typedef struct Class_c* Class_t;
typedef struct String_c *String_t;

typedef uint64_t mword_t;

typedef mword_t (*Method_t)(Object_t, va_list*);
typedef mword_t (*Invoke_t)(Object_t, Class_t class, va_list*);

struct Object_c {
  Class_t class;
};

struct Class_c {
  Class_t class;
  Class_t superclass;
  char *name;
  size_t instanceSize;
  Method_t New;
  Method_t init;
  Method_t toString;
  Method_t equals;
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
  Method_t New;
  Method_t init;
  Method_t toString;
  Method_t equals;
  Method_t lenght;
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

Object_t new(Class_t class, va_list* list);

void init(Object_t this, Class_t class, va_list* list) {
  class->init(this, list);
}

char *toString(Object_t this, Class_t class, va_list* list) {
  return class->toString(this, list);
}

int equlas(Object_t this, Class_t class, va_list* list) {
  return class->equals(this, list);
}

int lenght(String_t this, Class_t class, va_list* list) {
  return ((struct StringClass_c*)class)->lenght(this, list);
}

static Object_t objectMetaclass_new(Class_t class, va_list* list) {
  Object_t obj = malloc(class->instanceSize);
  obj->class = class;

  class->init(obj, list);
  
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
  char *str = va_arg((*list), char*);
  printf("init: %p\n", str);

  this->str = malloc(strlen(str)+1);
  strcpy(this->str, str);
}


void loadObject(Class_t class) {
  class->class = MetaClass;
  class->superclass = NULL;
  class->init = &object_init;
  class->toString = &object_toString;
  class->equals = &object_equals;
  class->New = objectMetaclass_new;
}

void loadMetaClass(Class_t class) {
  loadObject(class);

  class->superclass = Object;
}

void loadString(Class_t class) {
  loadObject(class);

  struct StringClass_c *clazz = class;

  clazz->class = StringMeta;
  clazz->superclass = Object;
  clazz->init = &string_init;
  clazz->toString = &string_toString;
  clazz->equals = &string_equals;
  clazz->lenght = &string_lenght;
}

void loadStringMeta(Class_t class) {
  loadMetaClass(class);
  
  struct StringClass_c *clazz = class;


  clazz->class = StringMeta;
  clazz->superclass = MetaClass;
}


void loadClasses() {
  loadObject(Object);
  loadMetaClass(MetaClass);
  loadString(String);
  loadStringMeta(StringMeta);
}

Object_t new(Class_t class, va_list* list) {
  return class->New(class, list);
}


mword_t super(Object_t obj, Invoke_t method, ...) {
  va_list list;
  va_start(list, method);
  mword_t ret = method(obj, obj->class->superclass, &list);
  va_end(list);
  return ret;
}


mword_t send(Object_t obj, Invoke_t method, ...) {
  va_list list;
  va_start(list, method);
  mword_t ret = method(obj, obj->class, &list);
  va_end(list);
  return ret;
}



int main() {
  loadClasses();
  char *s = "Hello World!\n";
  printf("String at: %p\n", s);

  String_t str = send(String, new, s);
  printf("---------------------------\n");
  printf("%s\n", send(str, toString));
  printf("---------------------------\n");
  
//  printf("%s\n", send(Object, toString));


//  String_t str = send(String, new, "Hello World!");
// printf("%s, %d\n", send(str, toString), send(str, lenght));

}



