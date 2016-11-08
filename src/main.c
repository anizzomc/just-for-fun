#include <stdio.h>

#include <JFF.h>
#include <Object.h>
#include <String.h>


ClassLoader_t classLoaders[] = {
  objectClassLoad,
  stringClassLoad,
};

const int classLoadersQty = sizeof(classLoaders)/sizeof(ClassLoader_t);


int main() {
  jff_loadClasses();

  char *s = "Hello World!";
  char *s1 = "Hello World!";

  String_t str = send(String, new, s);
  String_t str1 = send(String, new, s1);
  printf("%s\n", send(str, toString));
  printf("%d\n", send(str, equals, str1));
  printf("%d\n", send(str, lenght));

}

