#!/usr/bin/env bash
FILES=$(find tests/src -name "*.c")

echo \
'/* This is auto-generated code. Edit at your own peril. */
#include <stdio.h>
#include <stdlib.h>
#include <JFF.h>
#include <CuTest.h>
'

for f in $FILES
do
	grep '^void Test' $f |
		sed -e 's/(.*$//' \
		    -e 's/$/(CuTest*);/' \
		    -e 's/^/extern /'
done

echo \
'
void RunAllTests(void)
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
'

for f in $FILES
do
	grep '^void Test' $f |
		sed -e 's/^void //' \
		    -e 's/(.*$//' \
		    -e 's/^/    SUITE_ADD_TEST(suite, /' \
		    -e 's/$/);/'
done

echo \
'
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
'
