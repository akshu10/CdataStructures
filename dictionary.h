
// This is the header file for the Dictionary contract

#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H


#define MAX_SIZE 10

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "bintree.h"
#include "array_list.h"

typedef struct _Pair {

    void *first;
    void *second;

} Pair;


typedef struct _Dictionary {

    BinaryTree *tree;

} Dictionary;


Dictionary *dict_initialize(int (*)(void *, void *), void (*)(void *));


bool dict_insert(Dictionary *, void *, void *);

void *_dict_get_recursive(BinaryTree *, BinaryTreeNode *, void *);

void *dict_get(Dictionary *, void *);

ArrayList *dict_key_list(Dictionary *, int);

void in_order_recursive(ArrayList *, BinaryTree *, BinaryTreeNode *);

bool dict_contains(Dictionary *, void *);

bool recursive_dict_contains(BinaryTree *, BinaryTreeNode *, void *);

#endif //DICTIONARY_DICTIONARY_H
