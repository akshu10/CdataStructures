
// This is the C file for the Stack Contract
#include "stack.h"

// This method initializes a Stack Struct
Stack *stack_initialize(int itemSize, char *dataType) {
    Stack *stack = malloc(sizeof(*stack));

    if (stack == NULL) {
        printf("ERROR(init):: CANNOT ALLOC MEM\n");
        return NULL;
    }

    stack->list = malloc(sizeof *(stack->list));

    stack->list = llist_initialize(itemSize, dataType);

    if (stack->list == NULL) {
        printf("COULD NOT INITIALIZE LIST IN STACK\n");
        return NULL;
    }

    return stack;
}

// This method adds a elements to the front of the list
bool stack_push(Stack *stack, void *pointer) {

    if (stack == NULL || stack->list == NULL || pointer == NULL) {
        printf("ERROR(push):: NULL ARGS\n");
        return false;
    }

    bool inserted = llist_add_first((stack->list), pointer);

    if (!inserted) {
        printf("ERROR(push):: WHILE INSERTING\n");
    }

    return inserted;

}

// This method removes an elements to the front of the list
void *stack_pop(Stack *stack) {

    if (stack == NULL || stack->list == NULL) {
        printf("ERROR(pop):: NULL ARGS\n");
        return NULL;
    }

    void *toReturn = llist_remove_first(stack->list);

    if (toReturn == NULL) {
        printf("ERROR(pop):: WHILE REMOVING\n");
    }

    return toReturn;
}

// This method returns a pointer to the element at the top of the stack.
void *stack_peek(Stack *stack) {

    if (stack == NULL || stack->list == NULL) {
        printf("ERROR(peek):: NULL ARGS\n");
        return NULL;
    }

    void *toReturn = llist_get((stack->list), 0);

    return toReturn;
}


int stack_size(Stack *stack) {

    if (stack == NULL || stack->list == NULL) {
        printf("ERROR(size):: NULL ARGS\n");
        return -1;
    }

    return stack->list->size;
}

bool stack_contains(Stack *stack, void *pointer) {

    if (stack == NULL || stack->list == NULL || pointer == NULL) {
        printf("ERROR(contains):: NULL ARGS\n");
        return NULL;
    }

    return (llist_index_of((stack->list), pointer) < 0 ? false : true);
}

bool stack_destroy(Stack *stack) {
    if (stack == NULL || stack->list == NULL) {
        printf("ERROR(destroy):: NULL ARGS\n");
        return false;
    }

    if (!llist_destroy(stack->list)) {
        printf("ERROR(destroy):: COULD NOT DESTROY LIST\n");
        return false;
    }

    free(stack);
    return true;
}
