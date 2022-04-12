#include <stdlib.h>
#include <stdio.h>
#include "inventory.h"

#define HEAP_INITIAL_SIZE (16)
#define LEFT (0)
#define RIGHT (1)

struct item{
    long price;
    long weight;
    char* name;
};

struct inventory{
    unsigned long weight_limit;
    struct item** item_heap;
    int heap_size;
    int heap_capacity;
    int weight;
};

Inventory inventoryCreate(int weight_limit){
    Inventory inv = malloc(sizeof(*inv));
    inv->weight_limit = weight_limit;
    inv->heap_size = 0;
    inv->heap_capacity = HEAP_INITIAL_SIZE;
    inv->item_heap = malloc(HEAP_INITIAL_SIZE * sizeof(struct item*));
    inv->weight = 0;
    return inv;
}

void inventoryDestroy(Inventory inv){
    for (int i = 0; i < inv->heap_size; i++){
        free(inv->item_heap[i]->name);
        free(inv->item_heap[i]);
    }
    free(inv->item_heap);
    free(inv);
}

// Returns a-b
// p1 / w1 > p2 / w2
// implies p1w2 > p2w1
static int item_cmp(struct item* a, struct item* b){
    unsigned long a_val = a->price * b->weight;
    unsigned long b_val = b->price * a->weight;
    if (a_val > b_val){
        return 1;
    } else if (a_val == b_val){
        return 0;
    } else {
        return -1;
    }
}

// Following 5 functions are from heapsort.c, 04-12-2021 lecture
static void
swap(struct item** x, struct item** y)
{
    struct item* temp = *x;
    *x = *y;
    *y = temp;
}

static size_t
parent(size_t i)
{
    return (i-1)/2;
}

static size_t
child(size_t i, int side)
{
    return 2*i + 1 + side;
}

// We build a min heap so we want to float down if the current element is 
// bigger than its children
static void
floatDown(size_t i, size_t heap_size, struct item** item_heap)
{
    size_t left_child = child(i, LEFT);
    size_t right_child = child(i, RIGHT);
    size_t smaller = left_child;

    if (left_child >= heap_size){
        return;
    }
    if (right_child < heap_size && item_cmp(item_heap[right_child], item_heap[left_child]) == -1){
        smaller = right_child;
    }
    if (item_cmp(item_heap[smaller], item_heap[i]) == -1){
        swap(&item_heap[smaller], &item_heap[i]);
        floatDown(smaller, heap_size, item_heap);
    }
}

// We want to float up if the parent is greater than our child
static void
floatUp(size_t i, struct item** item_heap)
{
    size_t p = parent(i);
    if (i != 0 && item_cmp(item_heap[p], item_heap[i]) == 1) {
        swap(&item_heap[p], &item_heap[i]);
        floatUp(p, item_heap);
    }
}

void inventoryAdd(Inventory inv, long price, long weight, char* item_name){
    // Insert item into heap
    struct item* new_item = malloc(sizeof(*new_item));
    new_item->price = price;
    new_item->weight = weight;
    new_item->name = item_name;
    if (inv->heap_size >= inv->heap_capacity - 1){
        inv->heap_capacity *= 2;
        inv->item_heap = realloc(inv->item_heap, inv->heap_capacity * sizeof(struct item*));
    }
    inv->item_heap[inv->heap_size++] = new_item;
    floatUp(inv->heap_size - 1, inv->item_heap);

    // Take items out if we are overweight
    (inv->weight) += weight;

    while (inv->weight > inv->weight_limit){
        struct item* popped = inv->item_heap[0];
        inv->heap_size--;
        inv->item_heap[0] = inv->item_heap[inv->heap_size];
        inv->item_heap[inv->heap_size] = NULL;
        floatDown(0, inv->heap_size, inv->item_heap);
        inv->weight -= popped->weight;

        printf("%ld %ld %s\n", popped->price, popped->weight, popped->name);

        free(popped->name);
        free(popped);
    }

    /*
    for (int i = 0; i < inv->heap_size; i++){
        printf("(%d) %ld %ld %s\n", i, inv->item_heap[i]->price, inv->item_heap[i]->weight, inv->item_heap[i]->name);
    }
    printf("---------------\n");
    */
}

