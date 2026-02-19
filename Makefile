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


clean:
	rm -rf build/

