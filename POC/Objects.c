#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
#include "hash.h"
#include "xprintf.h"

typedef struct Object* Object_t;
typedef struct Class* Class_t;
typedef struct Method *Method_t;

typedef void* (*Method_p)(Object_t, ...);

struct Method {
	char *name;
	size_t arguments;
	Method_p ptr;
};

struct Object {
	Class_t class;
};

struct Class {
	Class_t class;
	Class_t superclass;
	d_hash_t methods;
	size_t instanceSize;
	char *name;
	char data[1];
};

struct String {
	Class_t class;
	char *str;
};
typedef struct String* String_t;

struct Class MetaClass = { &MetaClass, NULL, NULL, sizeof(struct Class), "Metaclass"};
struct Class StringMetaClass = { &StringMetaClass, &MetaClass, NULL, sizeof(struct Class), "StringMetaClass"};

struct Class ObjectClass = { &MetaClass, NULL, NULL, sizeof(struct Object), "Object"};
struct Class StringClass = { &StringMetaClass, &ObjectClass, NULL, sizeof(struct String), "String"};





static void loadClasses();
static void loadMethod(Class_t clazz, char *method, Method_t m);
static unsigned strHash(char *str);
static unsigned str_eq(char* str1, char* str2);

uint32_t _resolv(Object_t obj, char *method, int super, ...);

Method_t _find(Class_t class, char* method);

uint32_t _invoke(Method_p m, Object_t obj, size_t argc, uint32_t *arguments);

Object_t MetaClass_new(Class_t class, ...) {
	uint32_t elements[128];
	int i;

	Object_t obj = malloc(class->instanceSize);

	obj->class = class; 

	Method_t m = _find(class, "initialize");

	if(m == NULL) {
		printf("Method \"%s\" not found\n", "initialize");
		abort();
	}

	va_list arg_list;
	va_start(arg_list, class);  
	for (i = 0 ; i < m->arguments ; i++){
		elements[i] = va_arg(arg_list, uint32_t);
	}
	va_end(arg_list);

	_invoke(m->ptr, obj, m->arguments, elements);

	return obj;
}

char *MetaClass_name(Class_t class) {
	return class->name;
}

void Object_initialize(Object_t this) {

}

char *Object_toString(Object_t this) {
	char *msg = malloc(100);
	xsprintf(msg,"%s@%x", this->class->name, this);
	return msg;
}

int Object_equals(Object_t this, Object_t other){
	return this == other;
}

Class_t Object_class(Object_t this) {
	return this->class;
}

int String_length(String_t this) {
	return strlen(this->str);
}

int String_equals(String_t this, String_t other) {
	return !strcmp(this->str, other->str);
}

char *String_toString(String_t this) {
	return this->str;
}

int main() {
	loadClasses();

	Object_t obj = (Object_t) _resolv(&ObjectClass, "new", 0);

 	printf("toString: %s\n", _resolv((Object_t) obj, "toString", 0));	
 	printf("class: %s\n", _resolv(_resolv((Object_t) obj, "class", 0), "name", 0));

	// String_t str1 = StringClass_new("Hello World");
	// String_t str2 = StringClass_new("Hello World");
	// String_t str3 = StringClass_new("Hello");


	// printf("length: %d\n", _resolv((Object_t) str1, "length", 0));
	// printf("toString: %s\n", (char*) _resolv((Object_t) str1, "toString", 0));
	// printf("equals: %d\n", _resolv((Object_t) str1, "equals", 0, str2));
	// printf("-----\n");
	// printf("Result: %s\n", (char*) _resolv(obj, "toString", 0));

}

Method_t _find(Class_t class, char* method){
	Method_t m; 
	m = (Method_t) d_hash_fetch(class->methods, method);
	return m;
}

Method_t _method(Class_t class, char* method){
	Method_t m = _find(class, method);

	if(m != NULL) {
		return m;
	}

	if(class->superclass != NULL) {
		return _method(class->superclass, method);
	}

	return NULL;
}

uint32_t _resolv(Object_t obj, char *method, int super, ...) {
	int i;
	uint32_t elements[128];
	va_list arg_list;

	Class_t class = obj->class;

	Method_t m = _method((super)? class->superclass : class, method);

	if(m == NULL) {
		printf("Method \"%s\" not found\n", method);
		abort();
	}

	va_start(arg_list, super);  
	for (i = 0 ; i < m->arguments ; i++){
		elements[i] = va_arg(arg_list, uint32_t);
	}
	va_end(arg_list);

	return _invoke(m->ptr, obj, m->arguments, elements);
}


//Methods:
struct Method MetaClass_new_m = {"new", 0, MetaClass_new};
struct Method MetaClass_name_m = {"name", 0, MetaClass_name};

struct Method Object_initialize_m = {"initialize", 0, Object_initialize};
struct Method Object_toString_m = {"toString", 0, Object_toString};
struct Method Object_equals_m = {"equals", 1, Object_equals};
struct Method Object_class_m = {"class", 0, Object_class};


struct Method String_lenght_m = {"lenght", 0, String_length};
struct Method String_toString_m = {"toString", 0, String_toString};
struct Method String_equals_m = {"equals", 1, String_equals};


static void loadClasses() {
	MetaClass.methods = d_hash_new((d_hash_fnc_t)&strHash, (d_hash_eqfnc_t) &str_eq);
	loadMethod(&MetaClass, "new", &MetaClass_new_m);
	loadMethod(&MetaClass, "name", &MetaClass_name_m);
	

	//Load Object
	ObjectClass.methods = d_hash_new((d_hash_fnc_t)&strHash, (d_hash_eqfnc_t) &str_eq);
	loadMethod(&ObjectClass, "initialize", &Object_initialize_m);
	loadMethod(&ObjectClass, "toString", &Object_toString_m);
	loadMethod(&ObjectClass, "equals", &Object_equals_m);
	loadMethod(&ObjectClass, "class", &Object_class_m);
	

	//Load String
	StringClass.methods = d_hash_new((d_hash_fnc_t)&strHash, (d_hash_eqfnc_t) &str_eq);
	loadMethod(&StringClass, "length", &String_length);
	loadMethod(&StringClass, "toString", &String_toString_m);
	loadMethod(&StringClass, "equals", &String_equals_m);

}

static void loadMethod(Class_t clazz, char *method, Method_t m){
	d_hash_insert(clazz->methods, method, m);
}


static unsigned strHash(char *str) {
	unsigned i = 0;
	while(*str) {
		i ^= (*str)*-13;
		str++;
	}
	return i;
}

static unsigned str_eq(char* str1, char* str2) {
	return !strcmp(str1, str2);
}



