
// This is the C file for the Dictionary contract
#include "dictionary.h"

// This Function initializes a Dictionary Struct.
Dictionary *dict_initialize(int (*compare)(void *, void *), void (*print)(void *)) {

    Dictionary *dictionary = malloc(sizeof(*dictionary));

    if (dictionary == NULL) {
        printf("ERROR(int):: Could Not alloc mem to dictionary\n");
        return NULL;
    }

    dictionary->tree = bintree_initialize(sizeof(Pair), "Pair", compare, print);


    if (dictionary->tree == NULL) {
        printf("ERROR(init):: CANNOT ALLOC MEM TO DICT->TREE\n");
        return NULL;
    }

    return dictionary;
}

// This method inserts a Pair Struct into the dictionary as a value.
bool dict_insert(Dictionary *dictionary, void *key, void *value) {

//    printf("INSERT FUNCT\n");
    if (dictionary == NULL || key == NULL || value == NULL) {
        printf("ERROR(insert):: NULL ARGS\n");
        return false;
    }

    Pair *pair = malloc(sizeof((*pair)));

    if (pair == NULL) {
        printf("ERROR(insert):: COULD NOT ALLOC MEM TO PAIR\n");
        return false;
    }

//    printf("ASSIGNED MEM TO PAIR\n");
    pair->first = malloc(sizeof(char *));
    pair->second = malloc(sizeof(void *));

    if (pair->second == NULL || pair->first == NULL) {
        printf("ERROR(insert):: COULD NOT ALLOC MEM TO PAIR->FIRST//SECOND\n");
        return false;
    }

    pair->first = key;
    pair->second = value;

    bool inserted = bintree_insert_replace((dictionary->tree), pair);


    if (!inserted) {
        printf("ERROR(insert):: Could Not Insert Pair\n");
        return false;
    }

    return inserted;
}

// This method gets a value related to the passed in key from the dictionary
void *dict_get(Dictionary *dictionary, void *key) {

    if (dictionary == NULL || key == NULL) {
        printf("ERROR(get):: NULL ARGS\n");
        return NULL;
    }

    if (dictionary->tree->top == NULL) {
        printf("ERROR(get):: DICT->TOP IS NULL\n");
        return NULL;
    }
    return _dict_get_recursive((dictionary->tree), (dictionary->tree->top), key);
}

// This method is the recursive method that performs the actual search on the tree.
void *_dict_get_recursive(BinaryTree *binTree, BinaryTreeNode *node, void *key) {

    if (node == NULL) {
        return NULL;
    }

    Pair *pair = malloc(sizeof(*pair));
    pair->first = key;
    pair->second = NULL;

    int compare = binTree->compare((node->data), (pair));


    if (compare == 0) {

        pair = node->data;

        return pair->second;

    } else if (compare < 0) {

        return _dict_get_recursive(binTree, (node->left), key);

    } else {

        return _dict_get_recursive(binTree, (node->right), key);

    }
}

// This method retrieves a list containing all the keys in the dictionary from left to right.
ArrayList *dict_key_list(Dictionary *dictionary, int allocSize) {

    if (dictionary == NULL || allocSize < 0) {
        printf("ERROR(list):: Illegal ARGS\n");
        return NULL;
    }

    ArrayList *aList = alist_initialize(MAX_SIZE, allocSize, "Pair");

    if (aList == NULL) {
        printf("ERROR(list):: Could Not alloc memory\n");
        return NULL;
    }

    if (dictionary->tree == NULL) {
        printf("ERROR(list):: DICT->TREE is NULL\n");
        return NULL;
    }

    in_order_recursive(aList, (dictionary->tree), (dictionary->tree->top));

    return aList;
}

// This is a recursive method that performs an inorder traversal on the tree and fills the list with keys.
void in_order_recursive(ArrayList *list, BinaryTree *tree, BinaryTreeNode *node) {

    Pair *pair;

    if (node == NULL) {
        return;
    } else {

        pair = node->data;
        in_order_recursive(list, tree, (node->left));
        alist_add(list, (pair->first));
        in_order_recursive(list, tree, (node->right));
    }
}

// This method checks whether the dictionary contains a given key or not.
bool dict_contains(Dictionary *dictionary, void *key) {

    if (dictionary == NULL || dictionary->tree == NULL || key == NULL) {
        printf("ERROR(contains):: Illegal ARGS\n");
        return false;
    }

    if (dictionary->tree->top == NULL) {
        printf("ERROR(contains):: DICT->tree->top == NULL\n");
        return false;
    }

    return recursive_dict_contains((dictionary->tree), (dictionary->tree->top), key);
}

// This method is a recursive method that performs the actual search on the dictionary.
bool recursive_dict_contains(BinaryTree *tree, BinaryTreeNode *node, void *key) {

    if (node == NULL) {
        return false;
    }

    Pair *pair = malloc(sizeof(*pair));
    pair->first = key;
    pair->second = NULL;

    int compare = tree->compare((node->data), pair);

    if (compare == 0) {

        return true;

    } else if (compare < 0) {
        return recursive_dict_contains(tree, (node->left), key);
    } else {
        return recursive_dict_contains(tree, (node->right), key);
    }
}




