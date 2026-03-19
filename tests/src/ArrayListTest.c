#include <JFF.h>
#include <ArrayList.h>
#include <String.h>
#include <Object.h>
#include <CuTest.h>

void TestArrayList_new(CuTest* tc) {
    ArrayList_t list = (ArrayList_t) send(ArrayList, new, 4);
    CuAssertPtrNotNull(tc, list);
    CuAssertIntEquals(tc, 0, (int) send((Object_t) list, length));
}

void TestArrayList_new_defaultCapacity(CuTest* tc) {
    // A capacity <= 0 should fall back to the default (16)
    ArrayList_t list = (ArrayList_t) send(ArrayList, new, 0);
    CuAssertPtrNotNull(tc, list);
    CuAssertIntEquals(tc, 0, (int) send((Object_t) list, length));
}

void TestArrayList_add(CuTest* tc) {
    ArrayList_t list = (ArrayList_t) send(ArrayList, new, 4);
    String_t s1 = (String_t) send(String, new, "first");
    String_t s2 = (String_t) send(String, new, "second");

    send((Object_t) list, add, s1);
    send((Object_t) list, add, s2);

    CuAssertIntEquals(tc, 2, (int) send((Object_t) list, length));
    CuAssertPtrEquals(tc, s1, (Object_t) send((Object_t) list, get, 0));
    CuAssertPtrEquals(tc, s2, (Object_t) send((Object_t) list, get, 1));
}

void TestArrayList_add_retains_item(CuTest* tc) {
    ArrayList_t list = (ArrayList_t) send(ArrayList, new, 4);
    String_t s = (String_t) send(String, new, "hello");

    CuAssertIntEquals(tc, 1, (int) send((Object_t) s, refCount));
    send((Object_t) list, add, s);
    CuAssertIntEquals(tc, 2, (int) send((Object_t) s, refCount));
}

void TestArrayList_add_resizes_when_full(CuTest* tc) {
    // Start with capacity 2 and add 3 items — triggers a resize
    ArrayList_t list = (ArrayList_t) send(ArrayList, new, 2);
    String_t s1 = (String_t) send(String, new, "a");
    String_t s2 = (String_t) send(String, new, "b");
    String_t s3 = (String_t) send(String, new, "c");

    send((Object_t) list, add, s1);
    send((Object_t) list, add, s2);
    send((Object_t) list, add, s3);

    CuAssertIntEquals(tc, 3, (int) send((Object_t) list, length));
    CuAssertPtrEquals(tc, s1, (Object_t) send((Object_t) list, get, 0));
    CuAssertPtrEquals(tc, s2, (Object_t) send((Object_t) list, get, 1));
    CuAssertPtrEquals(tc, s3, (Object_t) send((Object_t) list, get, 2));
}


void TestArrayList_delete(CuTest* tc) {
    ArrayList_t list = (ArrayList_t) send(ArrayList, new, 4);
    String_t s1 = (String_t) send(String, new, "first");
    String_t s2 = (String_t) send(String, new, "second");

    send((Object_t) list, add, s1);
    send((Object_t) list, add, s2);

    Object_t removed = (Object_t) send((Object_t) list, delete, 0);
    CuAssertPtrEquals(tc, s1, removed);
    CuAssertIntEquals(tc, 1, (int) send((Object_t) list, length));
    CuAssertPtrEquals(tc, s2, (Object_t) send((Object_t) list, get, 0));
}


void TestArrayList_release_releases_items(CuTest* tc) {
    ArrayList_t list = (ArrayList_t) send(ArrayList, new, 4);
    String_t s = (String_t) send(String, new, "hello");

    send((Object_t) list, add, s);
    CuAssertIntEquals(tc, 2, (int) send((Object_t) s, refCount));

    send((Object_t) list, release);
    CuAssertIntEquals(tc, 1, (int) send((Object_t) s, refCount));
}
