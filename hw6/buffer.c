#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

Buffer bufferCreate(){
    Buffer b = malloc(sizeof(struct buffer));
    b->capacity = INTIAL_SIZE;
    b->contents = malloc(sizeof(char) * b->capacity);
    b->index = 0;
    b->has_null = 0;
    return b;
}

void bufferAdd(Buffer b, int c){
    if (b->index >= b->capacity){
        b->capacity *= 2;
        b->contents = realloc(b->contents, b->capacity);
    }
    (b->contents)[(b->index)++] = c;
    if (c == '\0'){
        b->has_null = 1;
    }
}

void bufferPrint(Buffer b){
    for (int i = 0; i < b->index; i++){
        putchar((b->contents)[i]);
    }
}

void bufferDestroy(Buffer b){
    free(b->contents);
    free(b);
}

int bufferHasNull(Buffer b){
    return b->has_null;
}

char* bufferGetContents(Buffer b){
    char* contents = malloc(sizeof(char) * (b->index + 1));
    for (int i = 0; i < b->index; i++){
        contents[i] = (b->contents)[i];
    }
    contents[(b->index)] = '\0';
    return contents;
}
