#include <stdio.h>

#include <JFF.h>
#include <Object.h>
#include <String.h>
#include <Integer.h>

ClassLoader_t classLoaders[] = {
  objectClassLoad,
  stringClassLoad,
  integerClassLoad
};

const int classLoadersQty = sizeof(classLoaders)/sizeof(ClassLoader_t);

void output(Object_t obj) {
  printf("%s\n", send(obj, toString));
}

int main() {
  jff_loadClasses();

  char *s = "Hello World!";
  char *s1 = "Hello World!";

  String_t str = send(String, new, s);
  String_t str1 = send(String, new, s1);
  output(str);
  printf("%d\n", send(str, equals, str1));
  printf("%d\n", send(str, lenght));
  output(send(str, getClass));
  output(send(send(str, getClass), getClass));

  Integer_t i = send(Integer, new, 10);
  output(i);


}

