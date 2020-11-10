#include "heap.h"


Heap *heap_initialize(int dataSize, char *dataType, int(*compare)(void *, void *), void(*print)(void *)) {

    Heap *heap = malloc(sizeof(*heap));

    if (heap == NULL) {
        printf("ERROR(init):: OS COULD NOT ALLOC MEM TO HEAP\n");
        return NULL;
    }

    heap->list = alist_initialize(MAXSIZE, dataSize, dataType);

    if (heap->list == NULL) {
        printf("ERROR(init):: heap->list == NULL\n");
        return NULL;
    }

    heap->print = malloc(sizeof(*heap->print));
    heap->compare = malloc(sizeof(*heap->compare));

    if (heap->compare == NULL || heap->print == NULL) {
        printf("ERROR(init):: heap->compare/print == NULL\n");
        return NULL;
    }

    heap->print = print;
    heap->compare = compare;

    return heap;
}

bool heap_insert(Heap *heap, void *pointer) {

    if (heap == NULL || heap->list == NULL || pointer == NULL) {
        printf("ERROR(insert):: NULL ARGS\n");
        return NULL;
    }


    bool insert = alist_add((heap->list), pointer);

    if (!insert) {
        printf("ERROR(insert):: UNSUCCESSFUL INSERT\n");
        return false;
    }
    int index = heap_size(heap) - 1;

    return _heapify_up((heap), index);
}

bool _heapify_up(Heap *heap, int index) {

    if (index > heap_size(heap)) {
        printf("ERROR(heapify_up):: Invalid Args\n");
        return false;
    }

    int parentIndex = (index - 1) / 2;

    void *parentValue = alist_get((heap->list), parentIndex);
    void *childValue = alist_get((heap->list), index);

    int c = heap->compare(parentValue, childValue);

    if (c < 0) {
        //swap
        alist_add_at((heap->list), parentIndex, childValue);
        alist_add_at((heap->list), index, parentValue);

        return _heapify_up(heap, parentIndex);

    } else {
        return true;
    }
}

void *heap_remove(Heap *heap) {

    if (heap == NULL || heap->list == NULL) {
        printf("ERROR(remove)::: NULL ARGS\n");
        return NULL;
    }

    int lastIndex = heap_size(heap) - 1;
    void *rootNode = alist_get((heap->list), 0);
    void *lastNode = alist_get((heap->list), lastIndex);

    //Swap
    alist_add_at((heap->list), 0, lastNode);
    alist_add_at((heap->list), lastIndex, rootNode);

    void *temp = alist_remove((heap->list), lastIndex);

    if (temp == NULL) {
        printf("ERROR(remove):: REMOVE NOT SUCCESSFUL\n");
        return NULL;
    }

    _heapify(heap, 0);

    return rootNode;
}

bool _heapify(Heap *heap, int index) {

    if (index > heap_size(heap)) {
        printf("ERROR(heapify):: Invalid Args\n");
        return false;
    }

    int leftChildIndex = (2 * index) + 1;
    int rightChildIndex = 2 * (index + 1);

    int top = index;
    void *parent = alist_get((heap->list), index);
    void *leftChild = alist_get((heap->list), leftChildIndex);
    void *rightChild = alist_get((heap->list), rightChildIndex);

    if (heap->compare(parent, leftChild) < 0) {
        top = leftChildIndex;
    }else if (heap->compare())

}


void *heap_peek(Heap *);

int heap_size(Heap *heap) {

    if (heap == NULL || heap->list == NULL) {
        printf("ERROR(size):: NULL ARGS\n");
        return -1;
    }

    return heap->list->size;
}

bool heap_contains(Heap *);






