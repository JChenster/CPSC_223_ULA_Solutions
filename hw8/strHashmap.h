#define INITIAL_CAPACITY (128)

typedef struct _elt {
    char* key;
    char* value;
    struct _elt* next;
} elt;

typedef struct _hashmap{
    size_t size;
    size_t capacity;
    elt** table;
} hashmap;

typedef hashmap* Hashmap;

Hashmap strHashmapCreate();

void strHashmapDestroy(Hashmap h);

// Returns associated value for key
// or NULL if none exists
char* strHashmapLookup(Hashmap h, char* key);

// Add a key, value pair
// If the key exists already, replace the value with new value
void strHashmapAdd(Hashmap h, char* key, char* value);
