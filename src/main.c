#include <stdio.h>

#define INFO_DEBUG

#include <Debug.h>


#include <JFF.h>
#include <Object.h>
#include <String.h>
#include <Integer.h>
#include <A.h>
#include <B.h>

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

  A_t a = send(A, new, 1);
  output(a);
  printf("%d\n", send(a, test));

  B_t b = send(B, new, 2);
  output(b);
  printf("%d\n", send(b, test));


}

