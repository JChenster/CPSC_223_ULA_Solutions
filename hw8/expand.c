#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "buffer.h"
#include "strHashmap.h"

typedef enum {
    plaintext,
    codeword,
    definition
} state_t;

int main(){
    Hashmap h = strHashmapCreate();

    Buffer currBuffer = bufferCreate();
    Buffer codewordBuffer;
    Buffer definitionBuffer;

    state_t state = plaintext;

    int c;
    while ((c = getchar()) != EOF){
        if (!(isspace(c))) {
            switch(state){
                case plaintext:
                    bufferAdd(currBuffer, c);
                    break;
                case codeword:
                    bufferAdd(codewordBuffer, c);
                    break;
                case definition:
                    bufferAdd(currBuffer, c);
                    break;
            } 
        } 
        // Probably need to switch states
        else {
            switch(state){
                case plaintext:
                    bufferAdd(currBuffer, '\0'); // Make string
                    if (strcmp(bufferGetContents(currBuffer), "DEFINE") == 0){
                        state = codeword;
                        codewordBuffer = bufferCreate();
                    } 
                    else{
                        char* expansion_lookup = strHashmapLookup(h, bufferGetContents(currBuffer));
                        if (expansion_lookup != NULL){
                            printf("%s ", expansion_lookup);
                        } else {
                            printf("%s ", bufferGetContents(currBuffer));
                        }
                    }
                    bufferDestroy(currBuffer);
                    currBuffer = bufferCreate();
                    break;
                case codeword:
                    bufferAdd(codewordBuffer, '\0');
                    state = definition;
                    definitionBuffer = bufferCreate();
                    break;
                case definition:
                    bufferAdd(currBuffer, '\0');
                    // Stop the definition
                    if (strcmp(bufferGetContents(currBuffer), "STOP") == 0){
                        bufferAdd(definitionBuffer, '\0');
                        // Don't free codeword or definition b/c now in hashmap
                        strHashmapAdd(h, bufferGetContents(codewordBuffer), bufferGetContents(definitionBuffer));
                        free(codewordBuffer);
                        free(definitionBuffer);
                        state = plaintext;
                    } else {
                        // Add all chars in currBuffer to definitionBuffer
                        size_t buff_len = strlen(bufferGetContents(currBuffer));
                        for (size_t i = 0; i < buff_len; i++){
                            bufferAdd(definitionBuffer, bufferGetContents(currBuffer)[i]);
                        }
                        bufferAdd(definitionBuffer, c);
                    }
                    
                    bufferDestroy(currBuffer);
                    currBuffer = bufferCreate();
                    break;
            }
        }
    }

    // I assumed he was generous with putting a whitespace to close our file
    // This might not be the case
    bufferDestroy(currBuffer);
    strHashmapDestroy(h);

    putchar('\n');
    return 0;
}
