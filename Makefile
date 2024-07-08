OBJS = build/main.o build/BinFile.o build/BinHeader.o build/BinImage.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG) 


all: clean build clean

build: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o moto-bootlogo -I/usr/include/libpng16 -lpng

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) -o build/main.o src/main.cpp

build/BinFile.o: src/BinFile.cpp
	$(CC) $(CFLAGS) -o build/BinFile.o src/BinFile.cpp

build/BinHeader.o: src/BinHeader.cpp
	$(CC) $(CFLAGS) -o build/BinHeader.o src/BinHeader.cpp

build/BinImage.o: src/BinImage.cpp
	$(CC) $(CFLAGS) -o build/BinImage.o src/BinImage.cpp -I/usr/include/libpng16 -lpng

clean:
	rm -f build/*
