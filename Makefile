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

clean:
	rm -rf build/

