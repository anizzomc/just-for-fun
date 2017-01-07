INC_PATH=include/

TARGET=JFF.out
ENTITY=Entity.out
D=lib/libd.a

all: $(TARGET) $(ENTITY)

$(TARGET): $(D)
	gcc main.c src/*.c -Llib/ -ld -I$(INC_PATH) -Ilib/D/include -o $(TARGET)

$(ENTITY): $(D)
	gcc entity.c src/*.c -Llib/ -ld -I$(INC_PATH) -Ilib/D/include -o $(ENTITY)


$(D):
	cd lib/D; make all
	mv lib/D/out/libd.a lib/.


clean:
	rm -f $(D)
	rm -f *.out
	cd lib/D; make clean
	rm -f *.o
