#include <stdio.h>

#define INFO_DEBUG

#include <Debug.h>


#include <JFF.h>
#include <Object.h>
#include <String.h>
#include <Integer.h>
#include <LinkedList.h>
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


  LinkedList_t list = send(LinkedList, new);
  send(list, add, str);
  send(list, add, str1);
  send(list, add, i);
  Object_t first = send(list, get, 0);
  output(first);
  Object_t removed = send(list, delete, 2);
  output(removed);
  printf("%d\n", send(list, length));

}

