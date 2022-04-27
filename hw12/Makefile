CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

all: majority

majority: majority.o graph.o
	$(CC) $(CFLAGS) -o $@ $^

majority.o: majority.c graph.h

graph.o: graph.c graph.h

run:
	./majority

clean:
	rm *.o ./majority