#include <stdlib.h>
#include "rooms.h"

typedef struct _queue_node{
    struct room* r;
    struct _queue_node* next;
} queue_node;

// Free every struct room that is either start,
// or can be reached from start 
// by following any sequence of north
// and south pointers.
// Also free descriptions.
// Returns number of rooms freed.
size_t freeRooms(struct room *start){
    // We build up a queue of rooms to visit and add to our free queue
    queue_node* visit_queue = malloc(sizeof(queue_node));
    visit_queue->r = start;
    visit_queue->next = NULL;

    queue_node* free_queue = NULL;

    while (visit_queue != NULL) {
        // A NULL description means that the room has already been visited
        if (visit_queue->r->description){
            if (visit_queue->r->north){
                queue_node* old_next = visit_queue->next;
                queue_node* new_node = malloc(sizeof(queue_node));
                new_node->r = visit_queue->r->north;
                new_node->next = old_next;
                visit_queue->next = new_node;
            }
            if (visit_queue->r->south){
                queue_node* old_next = visit_queue->next;
                queue_node* new_node = malloc(sizeof(queue_node));
                new_node->r = visit_queue->r->south;
                new_node->next = old_next;
                visit_queue->next = new_node;
            }
            // Add the room to free list
            queue_node* new_node = malloc(sizeof(queue_node));
            new_node->r = visit_queue->r;
            new_node->next = free_queue;
            free_queue = new_node;
            // Mark the node as visited
            free(visit_queue->r->description);
            visit_queue->r->description = NULL;
        }
        // Update the queue
        queue_node* new_head = visit_queue->next;
        free(visit_queue);
        visit_queue = new_head;
    }

    // When our free queue is empty, we free our free queue
    size_t freed_rooms = 0;
    while (free_queue){
        queue_node* next_free = free_queue->next;
        free(free_queue->r);
        free(free_queue);
        free_queue = next_free;
        freed_rooms++;
    }
    return freed_rooms;
}
