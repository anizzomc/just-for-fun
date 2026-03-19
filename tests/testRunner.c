/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>
#include <JFF.h>
#include <CuTest.h>

extern void TestNull_isSingleton(CuTest*);
extern void TestNull_isNull_returnsTrue(CuTest*);
extern void TestNull_isNull_otherObjectsReturnFalse(CuTest*);
extern void TestNull_toString(CuTest*);
extern void TestNull_getClass(CuTest*);
extern void TestLinkedList_new(CuTest*);
extern void TestLinkedList_add(CuTest*);
extern void TestLinkedList_delete(CuTest*);
extern void TestLinkedList_add_retains_item(CuTest*);
extern void TestLinkedList_release_releases_items(CuTest*);
extern void TestLinkedList_delete_does_not_release_item(CuTest*);
extern void TestLinkedList_add_isO1(CuTest*);
extern void TestString_new(CuTest*);
extern void TestString_length(CuTest*);
extern void TestString_equals_same(CuTest*);
extern void TestString_equals_different(CuTest*);
extern void TestArrayList_new(CuTest*);
extern void TestArrayList_new_defaultCapacity(CuTest*);
extern void TestArrayList_add(CuTest*);
extern void TestArrayList_add_retains_item(CuTest*);
extern void TestArrayList_add_resizes_when_full(CuTest*);
extern void TestArrayList_delete(CuTest*);
extern void TestArrayList_release_releases_items(CuTest*);
extern void TestLinkedListIterator_emptyList(CuTest*);
extern void TestLinkedListIterator_traversesInOrder(CuTest*);
extern void TestLinkedListIterator_hasNextFalseWhenExhausted(CuTest*);

void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, TestNull_isSingleton);
    SUITE_ADD_TEST(suite, TestNull_isNull_returnsTrue);
    SUITE_ADD_TEST(suite, TestNull_isNull_otherObjectsReturnFalse);
    SUITE_ADD_TEST(suite, TestNull_toString);
    SUITE_ADD_TEST(suite, TestNull_getClass);
    SUITE_ADD_TEST(suite, TestLinkedList_new);
    SUITE_ADD_TEST(suite, TestLinkedList_add);
    SUITE_ADD_TEST(suite, TestLinkedList_delete);
    SUITE_ADD_TEST(suite, TestLinkedList_add_retains_item);
    SUITE_ADD_TEST(suite, TestLinkedList_release_releases_items);
    SUITE_ADD_TEST(suite, TestLinkedList_delete_does_not_release_item);
    SUITE_ADD_TEST(suite, TestLinkedList_add_isO1);
    SUITE_ADD_TEST(suite, TestString_new);
    SUITE_ADD_TEST(suite, TestString_length);
    SUITE_ADD_TEST(suite, TestString_equals_same);
    SUITE_ADD_TEST(suite, TestString_equals_different);
    SUITE_ADD_TEST(suite, TestArrayList_new);
    SUITE_ADD_TEST(suite, TestArrayList_new_defaultCapacity);
    SUITE_ADD_TEST(suite, TestArrayList_add);
    SUITE_ADD_TEST(suite, TestArrayList_add_retains_item);
    SUITE_ADD_TEST(suite, TestArrayList_add_resizes_when_full);
    SUITE_ADD_TEST(suite, TestArrayList_delete);
    SUITE_ADD_TEST(suite, TestArrayList_release_releases_items);
    SUITE_ADD_TEST(suite, TestLinkedListIterator_emptyList);
    SUITE_ADD_TEST(suite, TestLinkedListIterator_traversesInOrder);
    SUITE_ADD_TEST(suite, TestLinkedListIterator_hasNextFalseWhenExhausted);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    int failed = suite->failCount;
    CuStringDelete(output);
    CuSuiteDelete(suite);
    if (failed > 0) exit(1);
}

int main(void)
{
    JFF_init();
    RunAllTests();
    return 0;
}

