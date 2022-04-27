#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

#define COLOR1 ('.')
#define COLOR2 ('X')

graph* graphCreate(int rows, int cols, char* vertex_chars, int* num_neighbors, int** neighbors){
    graph* g = malloc(sizeof(*g));
    g->rows = rows;
    g->cols = cols;
    g->vertex_chars = vertex_chars;
    g->num_neighbors = num_neighbors;
    g->neighbors = neighbors;
    return g;
}

// Conduct majority dynamics
void graphUpdate(graph* g){
    char* new_chars = malloc(sizeof(char) * (g->rows * g->cols));
    for (int i = 0; i < g->rows * g->cols; i++){
        // Calculate majority color
        int num_color1 = 0;
        int num_color2 = 0;
        for (int j = 0; j < g->num_neighbors[i]; j++){
            int neighbor = g->neighbors[i][j];
            if (g->vertex_chars[neighbor] == COLOR1){
                num_color1++;
            } else if (g->vertex_chars[neighbor] == COLOR2) {
                num_color2++;
            }
        }
        // Update to majority color
        if (num_color1 > num_color2){
            new_chars[i] = COLOR1;
        } else if (num_color2 > num_color1){
            new_chars[i] = COLOR2;
        } else {
            new_chars[i] = g->vertex_chars[i];
        }
    }
    free(g->vertex_chars);
    g->vertex_chars = new_chars;
}

void graphDestroy(graph* g){
    // Free neighbors
    for (int i = 0; i < g->rows * g->cols; i++){
        free(g->neighbors[i]);
    }
    free(g->neighbors);
    free(g->num_neighbors);
    free(g->vertex_chars);
    free(g);
}

void graphPrint(graph* g, int is_last){
    for (int i = 0; i < g->rows; i++){
        for (int j = 0; j < g->cols; j++){
            putchar(g->vertex_chars[g->cols * i + j]);
        }
        putchar('\n');
    }
    if (!is_last){
        putchar('\n');
    }
}
