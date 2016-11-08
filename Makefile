INC_PATH=include/

TARGET=JFF.out

all:
	gcc src/*.c -I$(INC_PATH) -o $(TARGET)

clean:
	rm $(TARGET)
	rm *.o