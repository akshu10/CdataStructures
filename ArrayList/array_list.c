//This is the C file for the arraylist contract.
#include "array_list.h"

#define  GROWTH_FACTOR 2


// This function initializes a arraylist
ArrayList *alist_initialize(int maxSize, int itemSize, char *dataType) {

    ArrayList *list = malloc(sizeof(*list));

    if (list == NULL) return NULL;

    if (dataType == NULL) return NULL;
    list->type = malloc(strlen(dataType) + 1);
    strcpy(list->type, dataType);


    list->arr = malloc(sizeof(void *) * maxSize);
    list->size = 0;
    list->maxSize = maxSize;
    list->itemSize = itemSize;

    return list;
}

// This function adds an element to the end of the list.
bool alist_add(ArrayList *list, void *pointer) {

    //printf("FIRST ADD\n");
    if (list == NULL || pointer == NULL) {
        printf("ERROR(add):: NULL ARGS\n");
        return false;
    }


    // CHECK FOR RESIZE
    if ((list->size) == (list->maxSize)) {

        if (!(_alist_resize(list))) {
            printf("ERROR WHILE RESIZING\n");
            return false;
        } else {
            printf("SUCCESS WHILE RESIZING\n");
        }
    }

    int index = list->size;
    list->arr[index] = malloc(list->itemSize);
    memcpy((list->arr[index]), pointer, (list->itemSize));
    list->size += 1;

    return true;
}

// This element adds an element at the provided index in the arraylist.
bool alist_add_at(ArrayList *list, int index, void *pointer) {

//    printf("SECOND ADD\n");
    // ERROR CHECKING
    if (list == NULL || pointer == NULL) {
        printf("ERROR(add_at):: NULL POINTER IN ARGS\n");
        return false;
    }

    // ERROR CHECKING
    if (index < 0 || index > (list->size)) {
        printf("ERROR(add_at):: INVALID INDEX \n");
        return false;
    }

    // CHECK FOR RESIZE
    if ((list->size) == (list->maxSize)) {

        if (!(_alist_resize(list))) {
            printf("ERROR WHILE RESIZING\n");
            return false;
        } else {
            printf("SUCCESS WHILE RESIZING\n");
        }
    }


    // Shifts all elements to the right by one.
    for (int i = (list->size); i > index; i--) {

        if ((list->arr[i]) == NULL) {

            list->arr[i] = malloc(list->itemSize);
        }

        memcpy((list->arr[i]), (list->arr[i - 1]), (list->itemSize));

    }

    memcpy((list->arr[index]), pointer, (list->itemSize));


    list->size += 1;

    return true;
}

// This function deallocates all array list elements and sets current size to 0.
void alist_clear(ArrayList *list) {

    if (list == NULL || list->arr == NULL) {
        printf("ERROR:: while clearing arraylist\n");
        return;
    }


    for (int i = 0; i < (list->size); ++i) {
        free(list->arr[i]);
    }

    list->size = 0;
}


// This function returns the void pointer stored in the given index of the array.
void *alist_get(ArrayList *list, int index) {

    //printf("IN GET FUNCT\n");
    if (list == NULL) {
        printf("ERROR(get):: Pointer to Struct is NULL in get Function\n");
        return NULL;
    }


    if (index < 0 || index > (list->size)) {
        printf("ERROR(get):: INVALID INDEX\n");
        return NULL;
    }

    return list->arr[index];
}

// This function searches the arraylist for the element and returns its index if found. Else -1
int alist_index_of(ArrayList *list, void *pointer) {

    //printf("INDEXOF FUNCT\n");
    if (list == NULL || pointer == NULL) {
        printf("ERROR(index_of):: Pointer to element or Struct is NULL\n");
        return -1;
    }

    for (int i = 0; i < (list->size); ++i) {

        if (list->arr[i] == NULL) {
            continue;
        } else if (memcmp(list->arr[i], pointer, (list->itemSize)) == 0) {
            return i;
        }
    }
    return -1;
}

// This method removes an element at the given index.
void *alist_remove(ArrayList *list, int index) {

    //printf("IN REMOVE\n");
    if (list == NULL || list->arr == NULL) {
        printf("ERROR(remove):: NULL ARGS IN REMOVE\n");
        return NULL;
    }

    if (index < 0 || index > (list->size - 1)) {
        printf("ERROR:: INVALID INDEX in add-at\n");
        return NULL;
    }

    void *toReturn = malloc(list->itemSize);
    memcpy(toReturn, (list->arr[index]), (list->itemSize));

    for (int i = index + 1; i < (list->size); ++i) {

        memcpy((list->arr[i - 1]), (list->arr[i]), (list->itemSize));
    }

    list->size -= 1;

    return toReturn;
}


// This method destroys the arraylist.
bool alist_destroy(ArrayList *list) {

    if (list == NULL || list->arr == NULL) {
        printf("ERROR:: Pointer is NULL in alist-destroy\n");
        return false;
    }

    for (int i = 0; i < (list->maxSize); ++i) {
        free(list->arr[i]);
    }

    free(list->arr);
    free(list->type);

    free(list);

    return true;
}


// This method resizes the arraylist to a new size.
bool _alist_resize(ArrayList *list) {

    // printf("INRESIZE\n");
    if (list == NULL || list->arr == NULL) return false;


    int newSize = (list->maxSize) * GROWTH_FACTOR;

    void **new = realloc(list->arr, (newSize * sizeof(void *)));

    if (new == NULL) {
        printf("ERROR(resize):: COULD NOT ALLOCATE MEMORY\n");
        return false;
    }

    list->arr = new;
    list->maxSize = newSize;

    return true;
}


