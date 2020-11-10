

// This is the Header file for the Stack Contract
#ifndef STACK_STACK_H
#define STACK_STACK_H

#include "linked_list.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct _Stack {

    LinkedList *list;

} Stack;


Stack *stack_initialize(int, char *);

bool stack_push(Stack *, void *);

void *stack_pop(Stack *);

void *stack_peek(Stack *);

int stack_size(Stack *);

bool stack_contains(Stack *, void *);

bool stack_destroy(Stack *);

#endif
