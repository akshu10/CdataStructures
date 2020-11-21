
// This is the C file for the Heap Contract

#include "heap.h"

// This function initializes a Heap Struct
Heap *heap_initialize(int dataSize, char *dataType, int(*compare)(void *, void *), void(*print)(void *)) {

    Heap *heap = malloc(sizeof(*heap));

    if (heap == NULL) {
        printf("ERROR(init):: OS COULD NOT ALLOC MEM TO HEAP\n");
        return NULL;
    }

    heap->list = alist_initialize(INITIAL_SIZE, dataSize, dataType);

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

// This function is called to insert a value to the Heap
// Returns true if value successfully inserted
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

    int size = heap_size(heap);

    return _heapify_up(heap, size - 1);
}

// This method moves the inserted element to the correct position on the Heap.
bool _heapify_up(Heap *heap, int index) {

    if (index > heap_size(heap)) {
        printf("ERROR(heapify_up):: Invalid Args\n");
        return false;
    }

    int parentIndex = (index - 1) / 2;

    if (parentIndex < 0) {
        return true;
    }

    void *parentNode = alist_get((heap->list), parentIndex);
    void *childNode = alist_get((heap->list), index);

    int c = heap->compare(parentNode, childNode);

    if (c < 0) {
        //swap
        alist_swap((heap->list), index, parentIndex);
//        heap->list->arr[index] = parentNode;
//        heap->list->arr[parentIndex] = childNode;

        return _heapify_up(heap, parentIndex);

    }

    return true;
}

// This method is called to remove an element from the Heap
void *heap_remove(Heap *heap) {

    if (heap == NULL || heap->list == NULL) {
        printf("ERROR(remove)::: NULL ARGS\n");
        return NULL;
    }

    if (heap_size(heap) == 0) {
        printf("HEAP IS EMPTY!!\n");
        return NULL;
    }

    int lastIndex = heap_size(heap) - 1;

    void *rootNode = alist_get((heap->list), 0);

    //Swap
    bool swap = alist_swap((heap->list), 0, lastIndex);

    if (!swap) {
        printf("ERROR(remove):: Problem in Swap\n");
    }

    void *temp = alist_remove((heap->list), lastIndex);


    if (temp == NULL) {
        printf("ERROR(remove):: REMOVE NOT SUCCESSFUL\n");
        return NULL;
    }

    _heapify(heap, 0);

    return rootNode;
}

// This method is reorganizes the Heap structure after an element is successfully removed.
bool _heapify(Heap *heap, int parentIndex) {

    int leftChildIndex = (2 * parentIndex) + 1;
    int rightChildIndex = 2 * (parentIndex + 1);

    void *parent = alist_get((heap->list), parentIndex);
    void *leftChild = alist_get((heap->list), leftChildIndex);
    void *rightChild = alist_get((heap->list), rightChildIndex);
    int top = parentIndex;
    int compare;

    if (leftChild == NULL && rightChild == NULL) return true;

    if (leftChild != NULL) {

        compare = heap->compare(leftChild, parent);
        if (compare > 0) {
            top = leftChildIndex;
            parent = leftChild;
        }
    }

    if (rightChild != NULL) {

        compare = heap->compare(rightChild, parent);
        if (compare > 0) {
            top = rightChildIndex;
        }
    }

    if (top != parentIndex) {

        bool swap = alist_swap((heap->list), top, parentIndex);

        if (!swap) {
            printf("ERROR(heapify):: Problem during swap\n");
            return false;
        }

        return _heapify(heap, top);
    }

    return true;
}

// This method returns a pointer to the element on top of the Heap.
void *heap_peek(Heap *heap) {

    if (heap == NULL || heap->list == NULL) {
        printf("ERROR(peek):: NULL ARGS\n");
        return NULL;
    }

    if (heap_size(heap) == 0) {
        printf("HEAP IS EMPTY!!\n");
        return NULL;
    }

    return alist_get((heap->list), 0);
}

// This methods returns the number of elements on the Heap.
int heap_size(Heap *heap) {

    if (heap == NULL || heap->list == NULL) {
        printf("ERROR(size):: NULL ARGS\n");
        return -1;
    }

    return heap->list->size;
}

// This method checks whether the Heap contains the given element.
bool heap_contains(Heap *heap, void *pointer) {

    if (heap == NULL || heap->list == NULL || pointer == NULL) {
        printf("ERROR(contains):: NULL ARGS\n");
        return false;
    }

    if (heap_size(heap) == 0) return false;

    for (int i = 0; i < (heap->list->size); ++i) {

        if (heap->compare((heap->list->arr[i]), pointer) == 0) {
            return true;
        }
    }
    return false;
}

