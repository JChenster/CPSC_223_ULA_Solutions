#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#define INITIAL_CAP (16)

static int getIndex(int rows, int cols, int row, int col){
    return row * cols + col;
}

int main(){
    int steps, rows, cols;

    scanf("%d[^\n]", &steps);
    scanf("%d %d[^\n]", &rows, &cols);

    getchar();

    char* vertex_chars = malloc(sizeof(char) * (rows * cols));
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            vertex_chars[getIndex(rows, cols, i, j)] = getchar();
        }
        getchar();
    }

    int* sizes = malloc(sizeof(int) * rows * cols);
    int* capacitities = malloc(sizeof(int) * rows * cols);
    int** neighbors = malloc(sizeof(int*) * rows * cols);
    for (int i = 0; i < rows * cols; i++){
        sizes[i] = 0;
        capacitities[i] = INITIAL_CAP;
        neighbors[i] = malloc(sizeof(int) * INITIAL_CAP);
    }

    int r1, c1, r2, c2;
    while (scanf("%d %d %d %d", &r1, &c1, &r2, &c2) == 4){
        int v1 = getIndex(rows, cols, r1, c1);
        int v2 = getIndex(rows, cols, r2, c2);

        if (sizes[v1] >= capacitities[v1] - 2){
            capacitities[v1] *= 2;
            neighbors[v1] = realloc(neighbors[v1], capacitities[v1] * sizeof(int));
        }
        if (sizes[v2] >= capacitities[v2] - 2){
            capacitities[v2] *= 2;
            neighbors[v2] = realloc(neighbors[v2], capacitities[v2] * sizeof(int));
        }

        neighbors[v1][sizes[v1]++] = v2;
        neighbors[v2][sizes[v2]++] = v1;
    }

    graph* g = graphCreate(rows, cols, vertex_chars, sizes, neighbors);
    graphPrint(g, 0);
    for (int i = 0; i < steps; i++){
        graphUpdate(g);
        if (i == steps - 1){
            graphPrint(g, 1);
        } else {
            graphPrint(g, 0);
        }
    }

    free(capacitities);
    graphDestroy(g);
}
