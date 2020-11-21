//This is the C file for the arraylist contract.
#include "array_list.h"

#define GROWTH_FACTOR 2

// This function initializes a arraylist
ArrayList *alist_initialize(int maxSize, int itemSize, char *dataType) {

    ArrayList *list = malloc(sizeof(*list));

    if (list == NULL) {
        return NULL;
    }

    if (dataType == NULL) {
        return NULL;
    }

    list->type = malloc(strlen(dataType) + 1);
    strcpy(list->type, dataType);

    list->maxSize = maxSize;
    list->arr = malloc(sizeof(*(list->arr)) * maxSize);

    list->itemSize = itemSize;
    list->size = 0;

    return list;
}

// This function adds an element to the end of the list.
bool alist_add(ArrayList *list, void *pointer) {

    //printf("FIRST ADD\n");
    if (list == NULL || pointer == NULL) {
        printf("ERROR(add):: NULL ARGS\n");
        return false;
    }

    return alist_add_at(list, (list->size), pointer);
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
        list->arr[i] = list->arr[i - 1];
    }

    list->arr[index] = malloc(list->itemSize);
    memcpy((list->arr[index]), pointer, (list->itemSize));

    list->size++;

    return true;
}

// This function deallocates all array list elements and sets current size to 0.
void alist_clear(ArrayList *list) {

    if (list == NULL || list->arr == NULL) {
        printf("ERROR:: while clearing arraylist\n");
        return;
    }

    for (int i = 0; i < (list->maxSize); i++) {
        free(list->arr[i]);
        list->arr[i] = NULL;
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
//        printf("ERROR(get):: INVALID INDEX\n");
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

    for (int i = 0; i < (list->size); i++) {
        if (memcmp(list->arr[i], pointer, (list->itemSize)) == 0) {
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
        printf("ERROR:: INVALID INDEX in remove\n");
        return NULL;
    }

    void *toReturn = list->arr[index];

    for (int i = index; i < (list->size - 1); i++) {

        list->arr[i] = list->arr[i + 1];
    }

    list->arr[list->size - 1] = NULL;
    list->size--;

    return toReturn;
}

// This method destroys the arraylist.
bool alist_destroy(ArrayList *list) {

    if (list == NULL || list->arr == NULL) {
        printf("ERROR:: Pointer is NULL in alist-destroy\n");
        return false;
    }

    alist_clear(list);

    free(list->type);

    free(list);

    return true;
}

// This method resizes the arraylist to a new size.
bool _alist_resize(ArrayList *list) {

    if (list == NULL || list->arr == NULL)
        return false;


    list->maxSize *= GROWTH_FACTOR;

    list->arr = realloc((list->arr), (list->maxSize * sizeof(*(list->arr))));

    if (list->arr == NULL) {
        printf("ERROR(resize):: COULD NOT ALLOCATE MEMORY\n");
        return false;
    }

    return true;
}

// This method helps to swap positions of values on the list.
bool alist_swap(ArrayList *list, int a, int b) {

    if (list == NULL || list->arr == NULL) {
        printf("ERROR(swap)::: NULL ARGS\n");
        return false;
    }

    if ((a < 0 || a >= list->size) || (b < 0 || b >= list->size)) {
        printf("ERROR(swap):: Invalid Indexes\n");
        return false;
    }

    void *temp = list->arr[a];

    list->arr[a] = list->arr[b];
    list->arr[b] = temp;

    return true;
}
