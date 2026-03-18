#include <JFF.h>
#include <LinkedList.h>
#include <LinkedListIterator.h>
#include <String.h>
#include <Object.h>
#include <CuTest.h>

void TestLinkedListIterator_emptyList(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    LinkedListIterator_t it = (LinkedListIterator_t) send((Object_t) list, iterator);

    CuAssertTrue(tc, !send((Object_t) it, hasNext));
}

void TestLinkedListIterator_traversesInOrder(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    String_t s1 = (String_t) send(String, new, "first");
    String_t s2 = (String_t) send(String, new, "second");
    String_t s3 = (String_t) send(String, new, "third");

    send((Object_t) list, add, s1);
    send((Object_t) list, add, s2);
    send((Object_t) list, add, s3);

    LinkedListIterator_t it = (LinkedListIterator_t) send((Object_t) list, iterator);

    CuAssertTrue(tc, send((Object_t) it, hasNext));
    CuAssertPtrEquals(tc, s1, (Object_t) send((Object_t) it, next));

    CuAssertTrue(tc, send((Object_t) it, hasNext));
    CuAssertPtrEquals(tc, s2, (Object_t) send((Object_t) it, next));

    CuAssertTrue(tc, send((Object_t) it, hasNext));
    CuAssertPtrEquals(tc, s3, (Object_t) send((Object_t) it, next));

    CuAssertTrue(tc, !send((Object_t) it, hasNext));
}

void TestLinkedListIterator_hasNextFalseWhenExhausted(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    String_t s = (String_t) send(String, new, "only");

    send((Object_t) list, add, s);

    LinkedListIterator_t it = (LinkedListIterator_t) send((Object_t) list, iterator);

    send((Object_t) it, next);

    CuAssertTrue(tc, !send((Object_t) it, hasNext));
}