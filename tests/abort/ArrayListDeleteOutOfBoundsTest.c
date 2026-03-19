#include <stdlib.h>
#include <JFF.h>
#include <ArrayList.h>

int main() {
  JFF_init();

  ArrayList_t list = (ArrayList_t) send(ArrayList, new, 4);

  // delete on an empty list — should abort with exit(1)
  send((Object_t) list, delete, 0);

  // Should never be reached
  exit(2);
}
