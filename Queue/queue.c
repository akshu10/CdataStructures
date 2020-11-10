
// This is the C file for the Queue Contract
#include "queue.h"

// This method initializes a Queue Struct
Queue *queue_initialize(int itemSize, char *dataType) {

    Queue *queue = malloc(sizeof(*queue));

    if (queue == NULL) {
        printf("ERROR(init):: CANNOT ALLOC MEM\n");
        return NULL;
    }

    queue->list = malloc(sizeof(*queue->list));

    queue->list = llist_initialize(itemSize, dataType);
    if (queue->list == NULL) {
        printf("ERROR(init):: CANNOT ALLOC MEM to Queue List\n");
        return NULL;
    }

    return queue;
}

// This method adds a elements to the back of the queue
bool queue_enqueue(Queue *queue, void *pointer) {

    if (queue == NULL || queue->list == NULL || pointer == NULL) {
        printf("ERROR(enqueue):: NULL ARGS\n");
        return false;
    }

    bool inserted = llist_add_first((queue->list), pointer);


    if (!inserted) {
        printf("ERROR(enqueue):: WHILE INSERTING\n");
    }

    return inserted;
}

// This method removes an elements from the front of the queue
void *queue_dequeue(Queue *queue) {

    if (queue == NULL || queue->list == NULL) {
        printf("ERROR(dequeue):: NULL ARGS\n");
        return NULL;
    }

    void *toReturn = llist_remove_last(queue->list);

    if (toReturn == NULL) {
        printf("ERROR(dequeue):: WHILE REMOVING\n");
    }

    return toReturn;
}

// This method returns a pointer to the front element of the queue
void *queue_peek(Queue *queue) {

    if (queue == NULL || queue->list == NULL) {
        printf("ERROR(peek):: NULL ARGS\n");
        return NULL;
    }

    int frontIndex = queue->list->size - 1;

    void *toReturn = llist_get((queue->list), frontIndex);

    return toReturn;
}

// This method returns the size of the queue
int queue_size(Queue *queue) {

    if (queue == NULL || queue->list == NULL) {
        printf("ERROR(size):: NULL ARGS\n");
        return -1;
    }

    return queue->list->size;
}

// This method checks if an element is contained in the queue
bool queue_contains(Queue *queue, void *pointer) {

    if (queue == NULL || queue->list == NULL || pointer == NULL) {
        printf("ERROR(contains):: NULL ARGS\n");
        return NULL;
    }

    return (llist_index_of((queue->list), pointer) < 0 ? false : true);
}

// This method destroys the queue by deallocating memory.
bool queue_destroy(Queue *queue) {

    if (queue == NULL || queue->list == NULL) {
        printf("ERROR(destroy):: NULL ARGS\n");
        return false;
    }

    bool destroyed = llist_destroy(queue->list);

    if (!destroyed) {
        printf("ERROR(destroy):: Something went wrong\n");
        return false;
    }

    free(queue);

    return true;

}

