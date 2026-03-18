#include <JFF.h>
#include <LinkedList.h>
#include <String.h>
#include <Object.h>
#include <Null.h>
#include <CuTest.h>

void TestLinkedList_new(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    CuAssertPtrNotNull(tc, list);
    CuAssertIntEquals(tc, 0, (int) send((Object_t) list, length));
}

void TestLinkedList_add(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    String_t s1 = (String_t) send(String, new, "first");
    String_t s2 = (String_t) send(String, new, "second");

    send((Object_t) list, add, s1);
    send((Object_t) list, add, s2);

    CuAssertIntEquals(tc, 2, (int) send((Object_t) list, length));
    CuAssertTrue(tc, (Object_t) send((Object_t) list, get, 0) == (Object_t) s1);
    CuAssertTrue(tc, (Object_t) send((Object_t) list, get, 1) == (Object_t) s2);
}

void TestLinkedList_get_outOfBounds(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    String_t s = (String_t) send(String, new, "item");
    send((Object_t) list, add, s);

    CuAssertTrue(tc, (Object_t) send((Object_t) list, get, -1) == NULL);
    CuAssertTrue(tc, (Object_t) send((Object_t) list, get, 1) == NULL);
}

void TestLinkedList_delete(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    String_t s1 = (String_t) send(String, new, "first");
    String_t s2 = (String_t) send(String, new, "second");

    send((Object_t) list, add, s1);
    send((Object_t) list, add, s2);

    Object_t removed = (Object_t) send((Object_t) list, delete, 0);
    CuAssertTrue(tc, removed == (Object_t) s1);
    CuAssertIntEquals(tc, 1, (int) send((Object_t) list, length));
    CuAssertTrue(tc, (Object_t) send((Object_t) list, get, 0) == (Object_t) s2);
}

void TestLinkedList_add_retains_item(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    String_t s = (String_t) send(String, new, "hello");

    CuAssertIntEquals(tc, 1, (int) send((Object_t) s, refCount));
    send((Object_t) list, add, s);
    CuAssertIntEquals(tc, 2, (int) send((Object_t) s, refCount));
}

void TestLinkedList_release_releases_items(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    String_t s = (String_t) send(String, new, "hello");

    send((Object_t) list, add, s);
    CuAssertIntEquals(tc, 2, (int) send((Object_t) s, refCount));

    send((Object_t) list, release);
    CuAssertIntEquals(tc, 1, (int) send((Object_t) s, refCount));
}

void TestLinkedList_delete_does_not_release_item(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    String_t s = (String_t) send(String, new, "hello");

    send((Object_t) list, add, s);

    // After add, the list holds a retain on the item (refCount == 2)
    CuAssertIntEquals(tc, 2, (int) send((Object_t) s, refCount));

    send((Object_t) list, delete, 0);

    // After delete the refCount must still be 2 — the list transfers ownership
    // back to the caller without releasing. It is the receiver's responsibility
    // to call release on the returned object when it is done with it.
    CuAssertIntEquals(tc, 2, (int) send((Object_t) s, refCount));
}

void TestLinkedList_delete_outOfBounds(CuTest* tc) {
    LinkedList_t list = (LinkedList_t) send(LinkedList, new);
    String_t s = (String_t) send(String, new, "item");
    send((Object_t) list, add, s);

    CuAssertTrue(tc, (Object_t) send((Object_t) list, delete, -1) == NULL);
    CuAssertTrue(tc, (Object_t) send((Object_t) list, delete, 1) == NULL);
    CuAssertIntEquals(tc, 1, (int) send((Object_t) list, length));
}
