#include <strings.h>
#include <stdlib.h>

#include <JFF.h>
#include <Object.h>
#include <extend/Object.h>
#include <extend/String.h>
#include <String.h>

static struct Class_c string = {NULL, NULL, "String", sizeof(struct Class_c)};
static struct Class_c stringMeta = {NULL, NULL, "StringMeta", sizeof(struct Class_c)};


const Class_t String = &string;
const Class_t StringMeta = &stringMeta;

struct String_c {
  struct Class_c* class;
  char *str;
};


static char* _toString(String_t this, va_list* list) {
  //TODO: Collect memory
  char *ret = malloc(strlen(this->str)+1);
  strcpy(ret, this->str);
  return ret;
}

static int _equals(String_t this, va_list* list) {
  String_t other = va_arg(*list, String_t);
  if(other == NULL) {
    return false;
  }
  if(this->class != other->class) {
    return false;
  }

  return strcmp(this->str, other->str) == 0;
}

static int _lenght(String_t this, va_list* list) {
  return strlen(this->str);
}


static void _init(String_t this, va_list* list) {
  char *str = va_arg(*list, char*);
  this->str = malloc(strlen(str)+1); //TODO: Collect memory
  strcpy(this->str, str);
}


void loadString(Class_t class) {
  loadObject(class);

  
  class->class = StringMeta;
  class->superclass = Object;
  class->methods[init] = (Method_t) &_init;
  class->methods[toString] = (Method_t) &_toString;
  class->methods[equals] = (Method_t) &_equals;
  class->methods[lenght] = (Method_t) &_lenght;
}

void loadStringClass(Class_t class) {
  loadObjectClass(class);
  

  class->class = StringMeta;
  class->superclass = MetaClass;
}

void stringClassLoad() {
  loadString(String);
  loadStringClass(StringMeta);
}
