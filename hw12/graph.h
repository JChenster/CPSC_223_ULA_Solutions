typedef struct _graph {
    int rows;
    int cols;
    char* vertex_chars;
    int* num_neighbors;
    int** neighbors;
} graph;

graph* graphCreate(int rows, int cols, char* vertex_chars, int* num_neighbors, int** neighbors);

// Conduct majority dynamics
void graphUpdate(graph* g);

void graphDestroy(graph* g);

void graphPrint(graph* g, int is_last);
