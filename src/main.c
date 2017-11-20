#include <stdio.h>

#include <JFF.h>
#include <Object.h>
#include <String.h>
#include <Integer.h>

#include <Debug.h>
#define INFO_DEBUG 

void output(Object_t obj) {

  String_t str = send(obj, toString);
  printf("%s\n", send(str, toCharArray));
}

int main() {
  INFO("Init\n");
  JFF_init();

  char *s = "Hello World!";
  char *s1 = "Hello World!";

  String_t str = send(String, new, s);
  String_t str1 = send(String, new, s1);

  output(str);
  printf("%d\n", send(str, equals, str1));
  printf("%d\n", send(str, length));

  output(send(str, getClass));
  output(send(send(str, getClass), getClass));

  Integer_t i = send(Integer, new, 10);
  output(i);


}

