#include <stdlib.h>
#include <JFF.h>
#include <LinkedList.h>

int main() {
  JFF_init();

  LinkedList_t list = (LinkedList_t) send(LinkedList, new);

  // delete on an empty list — should abort with exit(1)
  send((Object_t) list, delete, 0);

  // Should never be reached
  exit(2);
}
