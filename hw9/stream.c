#include <stdlib.h>
#include <string.h>
#include "stream.h"

// Infinite streams of characters.
//
// Stream objects can yield character using streamNext,
// or can be used to construct other streams.
//
// When constructing a composite stream, each stream
// should be used only once. This avoids oddities where
// characters from some stream are consumed in multiple
// places, and allows all streams used in the construction
// to be freed using a single call to streamDestroy.
#define LEFT (0)
#define RIGHT (1)

struct stream {
    int is_leaf;
    char* string;
    int str_len;
    int str_index;
    int child_index;
    struct stream** children;
};

// Return the next character in stream
int streamNext(Stream *stream){
    if (stream->is_leaf){
        // Empty string
        if (stream->string[0] == '\0') {
            return '\0';
        }
        int ret = stream->string[stream->str_index];
        stream->str_index = (stream->str_index + 1) % stream->str_len;
        return ret;
    } else {
        int ret = streamNext(stream->children[stream->child_index]);
        stream->child_index = 1 - stream->child_index;
        return ret;
    }
}

// Return a stream that repeats the contents of s
// over and over.
// For empty string, returns infinite stream of '\0'
// This should copy s in case s is changed or freed.
//
// streamFromString("abc") -> "abcabcabcabcabcabc..."
Stream *streamFromString(const char *s){
    Stream* our_stream = malloc(sizeof(*our_stream));
    our_stream->is_leaf = 1;
    our_stream->str_len = strlen(s);
    our_stream->string = malloc(sizeof(char) * (our_stream->str_len + 1));
    strcpy(our_stream->string, s);
    our_stream->str_index = 0;
    our_stream->child_index = -1;
    our_stream->children = NULL;
    return our_stream;
}

// Return contents of even interleaved with contents of odd.
//
// streamInterleave(streamFromString("a"), streamFromString("bc"))
//  -> "abacabacabac..."
Stream *streamInterleave(Stream *even, Stream *odd){
    Stream* our_stream = malloc(sizeof(*our_stream));
    our_stream->is_leaf = 0;
    our_stream->string = NULL;
    our_stream->str_len = 0;
    our_stream->str_index = 0;
    our_stream->child_index = 0;
    our_stream->children = malloc(sizeof(Stream*) * 2);
    our_stream->children[LEFT] = even;
    our_stream->children[RIGHT] = odd;
    return our_stream;
}

// Return stream where each character c is replaced
// by f(c). Both c and f(c) should be in the range 0..255.
Stream *streamMap(int (*f)(int), Stream *stream){
    if (stream->is_leaf){
        char* mapped_string = malloc(sizeof(char) * (stream->str_len + 1));
        for (int i = 0; i < stream->str_len; i++){
            mapped_string[i] = f(stream->string[i]) % 256;
        }
        mapped_string[stream->str_len] = '\0';
        Stream* ret = streamFromString(mapped_string);
        free(mapped_string);
        free(stream->string);
        free(stream->children);
        free(stream);
        return ret;
    } else {
        Stream* ret = streamInterleave(streamMap(f, stream->children[LEFT]), streamMap(f, stream->children[RIGHT]));
        free(stream->string);
        free(stream->children);
        free(stream);
        return ret;
    }
}

// Free stream and any streams used to construct stream.
void streamDestroy(Stream *stream){
    if (!stream->is_leaf) {
        streamDestroy(stream->children[LEFT]);
        streamDestroy(stream->children[RIGHT]);
    }
    //streamDestroy(stream->original);
    free(stream->string);
    free(stream->children);
    free(stream);
}
