#define INTIAL_SIZE (128)

struct buffer{
    size_t index;
    size_t capacity;
    char* contents;
    int has_null;
};

typedef struct buffer* Buffer;

Buffer bufferCreate();

void bufferAdd(Buffer b, int c);

void bufferPrint(Buffer b);

void bufferDestroy(Buffer b);

int bufferHasNull(Buffer b);

char* bufferGetContents(Buffer b);
