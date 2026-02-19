#!/usr/bin/env bash
FILES=$(find build/src -name "*.c")

echo '
/* This is auto-generated code. Edit at your own peril. */
'
for f in $FILES
do
	cat $f | grep '^void ClassLoader' | 
    	sed -e 's/(.*$//' \
        	-e 's/$/();/' \
        	-e 's/^/extern /'
done

echo \
'

void LoadClasses(void) 
{
'
for f in $FILES
do
	cat $f | grep '^void ClassLoader' | 
	    sed -e 's/^void //' \
	        -e 's/(.*$//' \
	        -e 's/^/    /' \
	        -e 's/$/();/'
done

echo \
'
}
'
