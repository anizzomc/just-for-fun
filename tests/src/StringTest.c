#include <JFF.h>
#include <String.h>
#include <Object.h>
#include <CuTest.h>

void TestString_new(CuTest* tc) {
    String_t str = (String_t) send(String, new, "hello");
    CuAssertPtrNotNull(tc, str);
    CuAssertTrue(tc, (Class_t) send((Object_t) str, getClass) == String);
}

void TestString_length(CuTest* tc) {
    String_t str = (String_t) send(String, new, "hello");
    CuAssertIntEquals(tc, 5, (int) send((Object_t) str, length));
}

void TestString_equals_same(CuTest* tc) {
    String_t str1 = (String_t) send(String, new, "hello");
    String_t str2 = (String_t) send(String, new, "hello");
    CuAssertTrue(tc, send((Object_t) str1, equals, str2));
}

void TestString_equals_different(CuTest* tc) {
    String_t str1 = (String_t) send(String, new, "hello");
    String_t str2 = (String_t) send(String, new, "world");
    CuAssertTrue(tc, !send((Object_t) str1, equals, str2));
}
