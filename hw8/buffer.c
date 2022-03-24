#include <stdlib.h>
#include "buffer.h"

Buffer bufferCreate(){
    Buffer b = malloc(sizeof(buffer));
    b->capacity = BUFFER_INITIAL_CAPACITY;
    b->size = 0;
    b->contents = malloc(sizeof(char) * b->capacity);
    return b;
}

void bufferDestroy(Buffer b){
    free(b->contents);
    free(b);
}

void bufferAdd(Buffer b, char c){
    if (b->size > b->capacity - 1){
        (b->capacity) *= 2;
        b->contents = realloc(b->contents, b->capacity);
    }
    (b->contents)[(b->size)++] = c;
}

char* bufferGetContents(Buffer b){
    return b->contents;
}
