#define BUFFER_INITIAL_CAPACITY (32)

typedef struct _buffer{
    char* contents;
    size_t capacity;
    size_t size;
} buffer;

typedef buffer* Buffer;

Buffer bufferCreate();

void bufferDestroy(Buffer b);

void bufferAdd(Buffer b, char c);

char* bufferGetContents(Buffer b);
