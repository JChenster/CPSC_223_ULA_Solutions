#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

void expand(FILE* f){
    int in_pipe = 0;
    int c;
    Buffer b;
    
    while ((c = fgetc(f)) != EOF){
        // Start our pipe
        if (c == '|' && in_pipe == 0){
            in_pipe = 1;
            b = bufferCreate();
        }
        else if (c == '|' && in_pipe == 1){
            // There was no null character so it is safe to try to open this file
            if (bufferHasNull(b) == 0){

                char* file_name = bufferGetContents(b);
                FILE* inner_file = fopen(file_name, "r");
                //printf("inner_file: %s\n", file_name);
                // Inner of pipe was not a file
                // So it is possible to have a file next
                if (inner_file == NULL){
                    //printf("failed to open file: %s\n", file_name);
                    putchar('|');
                    bufferPrint(b);
                } else {
                    //printf("calling expand: %s\n", file_name);
                    expand(inner_file);
                    in_pipe = 0;
                }
                free(file_name);
            } else {
                putchar('|');
                bufferPrint(b);
            }
            bufferDestroy(b);
            if (in_pipe == 1){
                b = bufferCreate();
            }
        } else {
            if (in_pipe) {
                bufferAdd(b, c);
            } else{
                putchar(c);
            }
        }
    }
    if (in_pipe){
        putchar('|');
        bufferPrint(b);
        bufferDestroy(b);
    }
}

int main(int argc, char** argv){
    // Read from standard in
    if (argc == 1){
        expand(stdin);
    }
    else { // Go through each of the  files passed in as args
        for (int i = 1; i < argc; i++){
            FILE* f = fopen(argv[i], "r");
            // Bad arg
            if (f == NULL){
                exit(1);
            }
            expand(f);
            fclose(f);
        }
    }
}
