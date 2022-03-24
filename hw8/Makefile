CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

all: expand

expand: expand.o buffer.o strHashmap.o
	$(CC) $(CFLAGS) -o $@ $^

expand.o: expand.c buffer.h strHashmap.h

buffer.o: buffer.c buffer.h

strHashmap.o: strHashmap.c strHashmap.h

run:
	./expand

clean:
	rm *.o ./expand