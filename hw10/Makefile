CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g3

all: inventoryManager

inventoryManager: inventoryManager.o inventory.o
	$(CC) $(CFLAGS) -o $@ $^

inventoryManager.o: inventoryManager.c inventory.h

inventory.o: inventory.c inventory.h

run:
	./inventoryManager

clean:
	rm *.o ./inventoryManager