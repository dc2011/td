CC = g++

TARGET = soundtest

COMPILEFLAGS = -lalut -lvorbisfile

$(TARGET): sound.o record.o testSound.o
	$(CC) -o $(TARGET) sound.o record.o testSound.o $(COMPILEFLAGS)

sound.o: sound.h sound.cpp
	$(CC) -c sound.cpp -Wall

record.o: record.h record.cpp
	$(CC) -c record.cpp -Wall

testSound.o: sound.h testSound.cpp
	$(CC) -c testSound.cpp -Wall

clean:
	rm -f $(TARGET) sound.o testSound.o record.o
