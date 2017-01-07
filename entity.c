#include <stdio.h>

#include <JFF.h>
#include <Entity.h>

void print(Object_t obj) {
  printf("%s\n", send(send(obj, toString), toCharArray));
}

int main() {
  JFF_init();

  Entity_t e1 = send(Entity, new);
  print(e1);
  Entity_t e2 = send(Entity, new);
  print(e2);
  printf("Entity Id: %d\n", send(e2, getId));
  printf("Next Id: %d\n", send(Entity, nextID));

}

