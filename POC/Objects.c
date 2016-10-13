#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
#include "hash.h"
#include "xprintf.h"

typedef struct Object* Object_t;
typedef struct Class* Class_t;
typedef struct String* String_t;

typedef void* (*Method)(Object_t, ...);

struct Object {
	Class_t class;
};

struct Class {
	Class_t class;
	Class_t superclass;
	d_hash_t methods;
	char *name;
};


struct Class MetaClass = {NULL, NULL, NULL, "Metaclass"};
struct Class ObjectClass = { &MetaClass, NULL, NULL, "Object"};
struct Class StringClass = { &MetaClass, &ObjectClass, NULL, "String"};

struct String {
	Class_t class;
	char *str;
};

static void loadClasses();
static void loadMethod(Class_t clazz, char *method, Method m);
static unsigned strHash(char *str);
static unsigned str_eq(char* str1, char* str2);

uint32_t _resolv(Object_t obj, char *method, int super, unsigned argc, ...);

uint32_t _invoke(Method m, Object_t obj, size_t argc, uint32_t *arguments);

Object_t ObjectClass_new() {
	Object_t obj = malloc(sizeof(struct Object));
	obj->class = &ObjectClass;
	return obj;
}

char *Object_toString(Object_t this) {
	char *msg = malloc(100);
	xsprintf(msg,"%s@%x", this->class->name, this);
	return msg;
}

int Object_equals(Object_t this, Object_t other){
	return this == other;
}

String_t StringClass_new(char *str) {
	String_t ret = malloc(sizeof(struct String));
	ret->class = &StringClass;
	ret->str = malloc(strlen(str) + 1);
	strcpy(ret->str, str);
	return ret;
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

	Object_t obj = ObjectClass_new();
	String_t str1 = StringClass_new("Hello World");
	String_t str2 = StringClass_new("Hello World");
	String_t str3 = StringClass_new("Hello");


	printf("length: %d\n", _resolv((Object_t) str1, "length", 0, 0));
	printf("toString: %s\n", (char*) _resolv((Object_t) str1, "toString", 0, 0));
	printf("equals: %d\n", _resolv((Object_t) str1, "equals", 0, 1, str2));
	printf("-----\n");
	printf("Result: %s\n", (char*) _resolv(obj, "toString", 0, 0));

}

Method _find(Class_t class, char* method){
	Method m; 
	m = (Method) d_hash_fetch(class->methods, method);
	return m;
}

Method _method(Class_t class, char* method){
	Method m = _find(class, method);

	if(m != NULL) {
		return m;
	}

	if(class->superclass != NULL) {
		return _method(class->superclass, method);
	}

	return NULL;
}

uint32_t _resolv(Object_t obj, char *method, int super, unsigned argc, ...) {
	int i;
	uint32_t elements[128];
	va_list arg_list;

	Class_t class = obj->class;

	Method m = _method((super)? class->superclass : class, method);

	va_start(arg_list, argc);  
	for (i = 0 ; i < argc ; i++){
		elements[i] = va_arg(arg_list, uint32_t);
	}
	va_end(arg_list);


	if(m == NULL) {
		printf("Method \"%s\" not found\n", method);
		abort();
	}

	return _invoke(m, obj, argc, elements);
}


static void loadClasses() {
	//Load Object
	ObjectClass.methods = d_hash_new((d_hash_fnc_t)&strHash, (d_hash_eqfnc_t) &str_eq);
	loadMethod(&ObjectClass, "toString", (Method) &Object_toString);
	loadMethod(&ObjectClass, "equals", (Method) &Object_equals);

	//Load String
	StringClass.methods = d_hash_new((d_hash_fnc_t)&strHash, (d_hash_eqfnc_t) &str_eq);
	loadMethod(&StringClass, "length", (Method) &String_length);
	loadMethod(&StringClass, "toString", (Method) &String_toString);
	loadMethod(&StringClass, "equals", (Method) &String_equals);

}

static void loadMethod(Class_t clazz, char *method, Method m){
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



