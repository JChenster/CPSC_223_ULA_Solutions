#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "strHashmap.h"

/* 
Hash fxn stuff from Prof Aspnes notes
*/
#define FNV_PRIME_64 ((1ULL<<40)+(1<<8)+0xb3)
#define FNV_OFFSET_BASIS_64 (14695981039346656037ULL)

uint64_t
hash_function(const char *bytes)
{
    uint64_t h = FNV_OFFSET_BASIS_64;

    for(size_t i = 0; bytes[i] != '\0'; i++) {
        h = h ^ bytes[i];
        h *= FNV_PRIME_64;
    }

    return h;
}

// END HASH STUFF

Hashmap strHashmapCreate(){
    Hashmap h = malloc(sizeof(hashmap));
    h->capacity = INITIAL_CAPACITY;
    h->size = 0;
    h->table = calloc(h->capacity, sizeof(elt*));
    return h;
}

void strHashmapDestroy(Hashmap h){
    elt* curr;
    elt* next;
    for (size_t i = 0; i < h->capacity; i++){
        curr = (h->table)[i];
        while (curr){
            next = curr->next;
            // Free each elt
            free(curr->key);
            free(curr->value);
            free(curr);
            curr = next;    
        }
    }
    free(h->table);
    free(h);
}

// Returns associated value for key
// or NULL if none exists
char* strHashmapLookup(Hashmap h, char* key){
    size_t table_index = hash_function(key) % h->capacity;
    elt* curr = (h->table)[table_index];
    while(curr){
        if (strcmp(curr->key, key) == 0) {
            return curr->value;
        }
        curr = curr->next;
    }
    return NULL;
}

// Add a key, value pair
// If the key exists already, replace the value with new value
void strHashmapAdd(Hashmap h, char* key, char* value){
    size_t table_index = hash_function(key) % h->capacity;
    elt* curr = (h->table)[table_index];
    // Add new element to chain
    if (strHashmapLookup(h, key) == NULL){
        elt* new_elt = malloc(sizeof(elt));
        new_elt->key = key;
        new_elt->value = value;
        new_elt->next = curr;
        (h->table)[table_index] = new_elt;
    }
    else {    
        while(curr){
            if (strcmp(curr->key, key) == 0) {
                free(curr->value);
                curr->value = value;
                return;
            }
            curr = curr->next;
        }
    }

    (h->size)++;
    // Do resizing stuff
}
