#ifndef _LINKED_LIST_ITERATOR_H_
#define _LINKED_LIST_ITERATOR_H_

#include <JFF.h>

void ClassLoader_LinkedListIterator();

typedef struct LinkedListIterator_c* LinkedListIterator_t;

/**
## LinkedListIterator — Forward iterator for LinkedList

  Obtained by calling iterator on a LinkedList instance. Keeps a reference
  to the current node and advances on each call to next.

  LinkedListIterator_t it = (LinkedListIterator_t) send((Object_t) list, iterator);
  while (send((Object_t) it, hasNext)) {
      Object_t obj = (Object_t) send((Object_t) it, next);
  }

## Object Methods

### hasNext (void) -> int

  Returns true if there are more elements to iterate over.

  int more = send((Object_t) it, hasNext);

### next (void) -> Object_t

  Returns the current element and advances the iterator to the next node.

  Object_t obj = (Object_t) send((Object_t) it, next);

**/

extern const Class_t LinkedListIterator;

#endif