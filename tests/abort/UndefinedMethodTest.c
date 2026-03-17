#include <stdlib.h>
#include <JFF.h>
#include <String.h>

int main() {
  JFF_init();

  String_t str = (String_t) send(String, new, "hello");

  // String does not define nextID — _methodNotDefined should fire and exit(0)
  send((Object_t) str, nextID);

  // Should never be reached
  exit(1);
}