CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

all: expand

expand: expand.o buffer.o
	$(CC) $(CFLAGS) -o $@ $^

expand.o: expand.c buffer.h

buffer.o: buffer.c buffer.h

run:
	./expand

clean:
	rm *.o ./expand
