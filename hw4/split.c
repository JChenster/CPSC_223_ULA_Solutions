#include <string.h>
#include <stdlib.h>

// Split and join operations for strings

// Given an array of pointers to strings,
// terminated by a null pointer, 
// concatenate them separated by character c,
// or no character if c is '\0'.
// Return the result as a malloc'd string.
//
// Examples:
//
// char *a[] = { "ab", "cd", "efg", 0 };
// join(a, ':') returns "ab:cd:efg"
// join(a, '\0') returns "abcdefg"
//
char *join(char **a, int c){
    int i = 0;
    int joined_len = 0;
    while (a[i] != NULL){
        joined_len += strlen(a[i]);
        if (c != '\0') {
            joined_len++;
        }
        i++;
    }
    if (c == '\0'){
        joined_len++;
    }
    
    char* joined_str = malloc(joined_len);
    int curr_index = 0;
    i = 0;
    while (a[i] != NULL){
        for (int j = 0; j < strlen(a[i]); j++){
            joined_str[curr_index++] = a[i][j];
        }
        if (c != '\0'){
            joined_str[curr_index++] = c;
        }
        i++;
    }
    if (c != '\0'){
        joined_str[curr_index - 1] = '\0';
    } else {
        joined_str[curr_index] = '\0';
    }
    
    return joined_str;
}

// Reverse of join: given a string s containing
// separators c, construct an array of pointers
// to copies of substrings of s separated by c.
//
// If c is null, a copy of the entire string will be
// returned as the only substring.
//
// Return value may include malloc'd data that can
// be freed with freeSplit if not modified.
//
// Examples:
//
// split("a:b:c", ':') returns {"a", "b", "c", 0}
// split("a::bc", ':') returns {"a", "", "bc", 0}
// split("a::bc", '\0') returns {"a::bc", 0}
//
// (The initializer syntax in the return values
// is for illustration only.)
char **split(const char *s, int c){
    int num_separators = 0;
    // Count the number of separators we have
    int i = 0;
    while (s[i] != '\0') {
        if (s[i] == c){
            num_separators += 1;
        }
        i++;
    }

    char** ptr_arr = malloc(sizeof(char*) * (num_separators + 2));

    int start = 0;
    int end;
    for (int i = 0; i < num_separators; i++){
        end = start;
        while (s[end] != c) {
            end++;
        }
        end++;
        // Create space for chunk and copy over contents
        char* chunk_copy = malloc(end - start);
        for (int j = start; j < end - 1; j++){
            chunk_copy[j - start] = s[j];
        }
        chunk_copy[end - 1 - start] = '\0';
        start = end;
        // Put our copy in array
        ptr_arr[i] = chunk_copy;
    }
    // We still have the characters after the last separator
    end = start;
    while (s[end] != '\0'){
        end++;
    }
    char* last_chunk = malloc(end - start + 1);
    for (int j = start; j < end; j++){
        last_chunk[j - start] = s[j];
    }
    last_chunk[end - start] = '\0';
    ptr_arr[num_separators] = last_chunk;
    ptr_arr[num_separators + 1] = NULL;

    return ptr_arr;
}

// Free all space used by a, assuming a
// was returned by split() and not subsequently
// modified.
void freeSplit(char **a){
    int i = 0;
    while (a[i] != NULL){
        free(a[i]);
        i++;
    }
    free(a);
}
