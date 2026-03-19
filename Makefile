CLASS_LOADER=build/classLoader.c


all:
	mkdir -p build/src
	mkdir -p build/inc/extend
	mkdir -p build/lib
	cp classes/*.c build/src/
	./classLoader.sh > $(CLASS_LOADER)

	cd lib/D ; make
	mv lib/D/out/*.a lib/

	cp lib/*.a build/lib
	cp src/*.c build/
	cp -r include/*.h build/inc
	cp -r include/extend/*.h build/inc/extend
	cp make_build build/Makefile
	cd build; make


test: all
	./testLoader.sh > tests/testRunner.c
	gcc tests/src/*.c tests/cutest/CuTest.c tests/testRunner.c \
		build/src/*.c build/JFF.c build/classLoader.c \
		-Ibuild/inc/ -Itests/cutest/ -Ilib/D/include \
		-Lbuild/lib/ -ld -o Test.out
	./Test.out

ABORT_FLAGS = build/src/*.c build/JFF.c build/classLoader.c \
	-Ibuild/inc/ -Ilib/D/include -Lbuild/lib/ -ld

define run_abort_test
	gcc $(1) $(ABORT_FLAGS) -o $(2).out
	./$(2).out; \
	if [ $$? -eq 1 ]; then echo "OK: [$(2)] aborted as expected"; \
	else echo "FAIL: [$(2)] did not abort"; exit 1; fi
endef

test-all: test test-abort test-abort-arraylist-get test-abort-arraylist-delete test-abort-linkedlist-get test-abort-linkedlist-delete

test-abort: all
	$(call run_abort_test,tests/abort/UndefinedMethodTest.c,UndefinedMethod)

test-abort-arraylist-get: all
	$(call run_abort_test,tests/abort/ArrayListGetOutOfBoundsTest.c,ArrayListGetOutOfBounds)

test-abort-arraylist-delete: all
	$(call run_abort_test,tests/abort/ArrayListDeleteOutOfBoundsTest.c,ArrayListDeleteOutOfBounds)

test-abort-linkedlist-get: all
	$(call run_abort_test,tests/abort/LinkedListGetOutOfBoundsTest.c,LinkedListGetOutOfBounds)

test-abort-linkedlist-delete: all
	$(call run_abort_test,tests/abort/LinkedListDeleteOutOfBoundsTest.c,LinkedListDeleteOutOfBounds)

clean:
	rm -rf build/

