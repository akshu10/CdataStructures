
// This is the Header File for the Heap Contract.

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include "stdbool.h"
#include "stdlib.h"
#include "array_list.h"

#define INITIAL_SIZE 10


typedef struct _Heap {
    ArrayList *list;

    int (*compare)(void *, void *);

    void (*print)(void *);
} Heap;

Heap *heap_initialize(int, char *, int(*)(void *, void *), void(*)(void *));

bool heap_insert(Heap *, void *);

void *heap_remove(Heap *);

void *heap_peek(Heap *);

int heap_size(Heap *);

bool heap_contains(Heap *, void *);

bool _heapify(Heap *, int);

bool _heapify_up(Heap *, int);

#endif