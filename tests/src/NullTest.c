#include <JFF.h>
#include <Null.h>
#include <String.h>
#include <Object.h>
#include <CuTest.h>

void TestNull_isSingleton(CuTest* tc) {
    Object_t a = (Object_t) send((Class_t) Null, new);
    Object_t b = (Object_t) send((Class_t) Null, new);
    CuAssertPtrEquals(tc, a, b);
    CuAssertPtrEquals(tc, (void*) Null, (void*) a);
}

void TestNull_isNull_returnsTrue(CuTest* tc) {
    CuAssertTrue(tc, send(Null, isNull));
}

void TestNull_isNull_otherObjectsReturnFalse(CuTest* tc) {
    Object_t str = (Object_t) send(String, new, "hello");
    CuAssertTrue(tc, !send(str, isNull));
}

void TestNull_toString(CuTest* tc) {
    String_t str = (String_t) send(Null, toString);
    CuAssertStrEquals(tc, "null", (char*) send((Object_t) str, toCharArray));
}

void TestNull_getClass(CuTest* tc) {
    CuAssertPtrNotNull(tc, (void*) send(Null, getClass));
}