INC_PATH=include/

TARGET=JFF.out
D=lib/libd.a

all: $(TARGET)

$(TARGET): $(D)
	gcc src/*.c -Llib/ -ld -I$(INC_PATH) -Ilib/D/include -o $(TARGET)

$(D):
	cd lib/D; make all
	mv lib/D/out/libd.a lib/.


clean:
	rm -f $(D)
	rm -f $(TARGET)
	cd lib/D; make clean
	rm -f *.o