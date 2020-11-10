

// This is the Header file for the Queue Contract
#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include "linked_list.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"


typedef struct _Queue {

    LinkedList *list;

} Queue;

Queue *queue_initialize(int, char *);

bool queue_enqueue(Queue *, void *);

void *queue_dequeue(Queue *);

void *queue_peek(Queue *);

int queue_size(Queue *);

bool queue_contains(Queue *, void *);

bool queue_destroy(Queue *);

#endif
