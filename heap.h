//
// Created by akshu on 11/9/2020.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include "stdbool.h"
#include "stdlib.h"
#include "array_list.h"

#define MAXSIZE 10


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

bool heap_contains(Heap *);

bool _heapify(Heap *, int);

bool _heapify_up(Heap *, int);

#endif //HEAP_HEAP_H
