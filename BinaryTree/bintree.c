
// This is the C file for the Binary tree Contract.
#include "bintree.h"

#define VoidType "void"

// This function allocates memory for holding a Tree Struct.
BinaryTree *bintree_initialize(int itemSize, char *dataType,
                               int(*compare)(void *, void *), void(*print)(void *)) {

    //printf("IN INITIALIZE\n");
    BinaryTree *binTree = malloc(sizeof(*binTree));

    if (binTree == NULL) {
        printf("ERROR(init):: COULD NOT ALLO MEM\n");
        return NULL;
    }

    if (dataType == NULL || compare == NULL || print == NULL) {
        printf("ERROR(init):: NULL ARGS \n");
        return NULL;
    }


    binTree->itemSize = itemSize;
    binTree->
            type = malloc(sizeof(strlen(dataType) + 1));

    if (binTree->type == NULL) {
        printf("ERROR(init):: COULD NOT ALLO MEM FOR binTree->type\n");
        return NULL;
    }
    strcpy(binTree->
            type, dataType);
//    printf("AFTER STRCPY\n");

    binTree->compare = malloc(sizeof(compare));
//    printf("MALLOC AFTER COMPARE\n");
    binTree->print = malloc(sizeof(print));
//    printf("MALLOC AFTER PRINT\n");


    if (binTree->compare == NULL || binTree->print == NULL) {
        print("ERROR(init):: COULD NOT ALLO MEM FOR binTree->compare//print\n");
        return NULL;
    }

    binTree->compare = compare;
//    printf("SEG HERE\n");
    binTree->print = print;

    binTree->top = NULL;

    // printf("BEFORE RETURN \n");
    return binTree;


}

// This is a helper method that creates a BinaryTreeNode.
BinaryTreeNode *bintree_create_node(int dataSize, void *pointer) {

    if (dataSize < 0 || pointer == NULL) {
        printf("ERROR(create_node):: PROBLEM IN ARGS\n");
        return NULL;
    }

    BinaryTreeNode *node = malloc(sizeof(*node));

    if (node == NULL) {
        printf("ERROR(create_node):: OS CANNOT ALLOC MEM to BinaryTreeNode Struct\n");
        return NULL;
    }


    node->data = malloc(dataSize);

    if (node->data == NULL) {
        printf("ERROR(create_node):: OS CANNOT ALLOC MEM to node->data\n");
        return NULL;
    }

    memcpy((node->data), (pointer), (dataSize));
    node->right = NULL;
    node->left = NULL;


    return node;
}

// This method starts off the recursive insert method.
bool bintree_insert(BinaryTree *binTree, void *pointer) {

    //printf("IN INSERT\n");
    if (binTree == NULL || pointer == NULL) {
        printf("ERROR(insert):: NULL ARGS\n");
        return false;
    }

    if (binTree->top == NULL) {

        binTree->top = bintree_create_node((binTree->itemSize), pointer);

        return true;
    } else {

        return _bintree_insert_recursive(binTree, (binTree->top), pointer);
    }

}


// This is the recursive function for inserting an element on the tree.
bool _bintree_insert_recursive(BinaryTree *binTree, BinaryTreeNode *node, void *pointer) {

//    printf("RECUR INSERT\n");
    BinaryTreeNode *insert = bintree_create_node((binTree->itemSize), pointer);
    int c = binTree->compare((node->data), (pointer));


    if (((c > 0) || (c == 0)) && (node->right != NULL)) {

        return _bintree_insert_recursive(binTree, (node->right), pointer);

    } else if ((c < 0) && (node->left != NULL)) {

        return _bintree_insert_recursive(binTree, (node->left), pointer);

    } else {

        if (c < 0) {

            node->left = insert;
        } else {

            node->right = insert;
        }

        return true;
    }

}

// This method starts off the recursive search method
bool bintree_search(BinaryTree *binTree, void *pointer) {

    if (binTree == NULL || pointer == NULL) {
        printf("ERROR(search):: NULL ARGS\n");
        return false;
    }

    return _bintree_search_recursive(binTree, binTree->top, pointer);

}

// This method is the recursive method for searching a value on the true.
// Returns true if value is found.
bool _bintree_search_recursive(BinaryTree *binTree, BinaryTreeNode *node, void *pointer) {

    if (node == NULL) {
        return false;
    }

    int c = binTree->compare((node->data), (pointer));

    if (c == 0) {
        printf("MESSAGE(recursive_search):: SUCCESS VALUE FOUND!!\n");
        return true;

    } else if (c < 0) {

        return _bintree_search_recursive(binTree, (node->left), pointer);
    } else {
        return _bintree_search_recursive(binTree, (node->right), pointer);
    }

}

// This method starts off the recursive method for printing the in order for a given tree.
void bintree_print_in_order(BinaryTree *binTree) {

    if (binTree == NULL) {
        printf("ERROR(in_order):: NULL ARGS\n");
        return;
    }

    return _bintree_in_order_recursive(binTree, (binTree->top));
}

// This is the recursive method that prints the in-order.
void _bintree_in_order_recursive(BinaryTree *binTree, BinaryTreeNode *node) {

    if (node == NULL) {
        return;
    } else {
        _bintree_in_order_recursive(binTree, (node->left));
        binTree->print(node->data);
        _bintree_in_order_recursive(binTree, (node->right));
    }

}

// This method starts off the recursive method for printing the pre order for a given tree.
void bintree_print_pre_order(BinaryTree *binTree) {

    if (binTree == NULL) {
        printf("ERROR(pre_order):: NULL ARGS\n");
        return;
    }

    return _bintree_pre_order_recursive(binTree, (binTree->top));

}

// This is the recursive method that prints the pre-order.
void _bintree_pre_order_recursive(BinaryTree *binTree, BinaryTreeNode *node) {

    if (node == NULL) {
        return;
    } else {
        binTree->print(node->data);
        _bintree_pre_order_recursive(binTree, (node->left));
        _bintree_pre_order_recursive(binTree, (node->right));
    }

}

// This method starts off the recursive method for printing the post order for a given tree.
void bintree_print_post_order(BinaryTree *binTree) {

    if (binTree == NULL) {
        printf("ERROR(post_order):: NULL ARGS\n");
        return;
    }

    return _bintree_post_order_recursive(binTree, (binTree->top));

}

// This is the recursive method that prints the post-order.
void _bintree_post_order_recursive(BinaryTree *binTree, BinaryTreeNode *node) {

    if (node != NULL) {
        _bintree_post_order_recursive(binTree, (node->left));
        _bintree_post_order_recursive(binTree, (node->right));
        binTree->print(node->data);
    }
}

// This method starts off the recursive method for printing the reverse order for a given tree.
void bintree_print_reverse_order(BinaryTree *binTree) {

    if (binTree == NULL) {
        printf("ERROR(reverse_order):: NULL ARGS\n");
        return;
    }

    return _bintree_reverse_order_recursive(binTree, (binTree->top));

}


// This is the recursive method that prints the reverse-order.
void _bintree_reverse_order_recursive(BinaryTree *binTree, BinaryTreeNode *node) {

    if (node == NULL) {
        return;
    } else {
        _bintree_reverse_order_recursive(binTree, (node->right));
        binTree->print(node->data);
        _bintree_reverse_order_recursive(binTree, (node->left));
    }
}

// This function performs a breadth first search on a Binary Tree
void bintree_print_breadth_first(BinaryTree *binTree) {

    if (binTree == NULL) {
        printf("ERROR(breadth_first):: NULL ARGS\n");
        return;
    }

    Queue *queue = queue_initialize(sizeof(*binTree->top), VoidType);

    if (queue == NULL) {
        printf("ERROR(breadth_first):: Queue is NULL\n");
        return;
    }

    if (binTree->top == NULL) return;

    queue_enqueue(queue, (binTree->top));

    while ((queue_size(queue)) != 0) {

        BinaryTreeNode *current = queue_dequeue(queue);

        binTree->print(current->data);

        // add left
        if ((current->left) != NULL) {
            bool success = queue_enqueue(queue, (current->left));

            if (!success) {
                printf("Enqueue Left FAILED\n");
            }
        }

        // add right
        if ((current->right) != NULL) {
            bool success = queue_enqueue(queue, (current->right));

            if (!success) {
                printf("Enqueue Right FAILED\n");
            }
        }
    }

}

// This function performs a depth first search on a Binary Tree
void bintree_print_depth_first(BinaryTree *binTree) {

    if (binTree == NULL) {
        printf("ERROR(depth_first):: NULL ARGS\n");
        return;
    }

    Stack *stack = stack_initialize((sizeof(*binTree->top)), VoidType);

    if (stack == NULL) {
        printf("ERROR(depth_first):: Stack is null\n");
        return;
    }

    if (binTree->top == NULL) return;

    stack_push(stack, binTree->top);

    while ((stack_size(stack)) != 0) {

        BinaryTreeNode *current = stack_pop(stack);

        binTree->print(current->data);

        //add right
        if ((current->right) != NULL) {

            bool success = stack_push(stack, (current->right));
            if (!success) {
                printf("PUSH RIGHT FAILED\n");
            }
        }

        // add left
        if ((current->left) != NULL) {

            bool success = stack_push(stack, (current->left));
            if (!success) {
                printf("PUSH LEFT FAILED\n");
            }
        }
    }
}

// This function replaces the value in the old node to contain new data.
bool bintree_insert_replace(BinaryTree *binTree, void *pointer) {

    if (binTree == NULL || pointer == NULL) {
        printf("ERROR(insert_replace):: NULL ARGS\n");
        return false;
    }

    if (binTree->top != NULL && (binTree->top->right == NULL) && (binTree->top->left == NULL)) {

        if (binTree->compare((binTree->top->data), pointer) == 0) {
            memcpy((binTree->top->data), pointer, (binTree->itemSize));
        }
        //  binTree->top = bintree_create_node((binTree->itemSize), pointer);

        return true;
    } else {

        return _bintree_insert_replace_recursive(binTree, (binTree->top), pointer);
    }
}

// This function is the recursive replace function for the BinaryTree Contract.
bool _bintree_insert_replace_recursive(BinaryTree *binTree, BinaryTreeNode *node, void *pointer) {

    BinaryTreeNode *insert = bintree_create_node((binTree->itemSize), pointer);
    int c = binTree->compare((node->data), (pointer));


    if (((c > 0)) && (node->right != NULL)) {

        return _bintree_insert_replace_recursive(binTree, (node->right), pointer);

    } else if ((c < 0) && (node->left != NULL)) {

        return _bintree_insert_replace_recursive(binTree, (node->left), pointer);

    } else {

        if (c == 0) {

            memcpy((node->data), pointer, (binTree->itemSize));

        } else if (c < 0) {

            node->left = insert;
        } else {

            node->right = insert;
        }

        return true;
    }
}
