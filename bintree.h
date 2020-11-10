//
// Created by akshu on 11/5/2020.
//

#ifndef BINARYTREE_BINTREE_H
#define BINARYTREE_BINTREE_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"


typedef struct _BinTreeNode {

    void *data;
    struct _BinTreeNode *left;
    struct _BinTreeNode *right;

} BinaryTreeNode;

typedef struct _BinaryTree {

    BinaryTreeNode *top;
    int itemSize;

    char *type;

    int (*compare)(void *, void *);

    void (*print)(void *);
} BinaryTree;


BinaryTree *bintree_initialize(int, char *, int(*)(void *, void *), void(*)(void *));


BinaryTreeNode *bintree_create_node(int, void *);

bool bintree_insert(BinaryTree *, void *);

bool bintree_search(BinaryTree *, void *);

void bintree_print_in_order(BinaryTree *);

void bintree_print_pre_order(BinaryTree *);

void bintree_print_post_order(BinaryTree *);

void bintree_print_reverse_order(BinaryTree *);


bool _bintree_insert_recursive(BinaryTree *, BinaryTreeNode *, void *);

bool _bintree_search_recursive(BinaryTree *, BinaryTreeNode *, void *);

void _bintree_in_order_recursive(BinaryTree *, BinaryTreeNode *);

void _bintree_pre_order_recursive(BinaryTree *, BinaryTreeNode *);

void _bintree_post_order_recursive(BinaryTree *, BinaryTreeNode *);

void _bintree_reverse_order_recursive(BinaryTree *, BinaryTreeNode *);


#endif //BINARYTREE_BINTREE_H
