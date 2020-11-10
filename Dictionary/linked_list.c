// This is the C file for the linkedlist contract.

#include "linked_list.h"


// This function initializes a LinkedList Struct and returns a Pointer to the Struct.
LinkedList *llist_initialize(int itemSize, char *dataType) {

//    printf("INITIALIZE\n");
    // Allocate memory to the Struct
    LinkedList *linkedList = malloc(sizeof *linkedList);

    // Check if the OS allocated enough memory.
    if (linkedList == NULL) {
        printf("ERROR(initialize):: COULD NOT ALLOC MEM for struct\n");
        return NULL;
    }

    // Check for Null Pointers
    if (dataType == NULL) {
        printf("ERROR(initialize):: NULL ARGS\n");
        return NULL;
    }
    // Allocate memory to the datatype pointer in the struct and copy data
    linkedList->type = malloc(strlen(dataType) + 1);

    if (linkedList->type == NULL) {
        printf("ERROR(initialize):: COULD NOT ALLOC MEM for datatype\n");
        return NULL;
    }

    strcpy(linkedList->type, dataType);

    linkedList->itemSize = itemSize;
    linkedList->size = 0;


    linkedList->first = NULL;
    linkedList->last = NULL;

    return linkedList;
}

// This function adds a data value to any given index of the LinkedList.
bool llist_add_at(LinkedList *linkedList, int index, void *pointer) {

//    printf("add_at\n");
    // Check for NULL Pointers.
    if (linkedList == NULL || pointer == NULL) {
        printf("ERROR(add_at):: NULL POINTER IN ARGS\n");
        return false;
    }

    //printf("VALIDATING INDEX\n");

    // Valid Index parameter.
    if ((index < 0) || index > (linkedList->size)) {
        printf("ERROR:: CANNOT ADD TO INVALID INDEX\n");
        return false;
    }

    //printf("BEFORE TOINSERT VAR\n");
    Node *toInsert = malloc(sizeof *toInsert);


    if (toInsert == NULL) {
        printf("ERROR:: WHILE ALLOC MEM IN ADD FUNCT\n");
        return false;
    }


    toInsert->data = malloc(linkedList->itemSize);
//    printf("AFTER TOINSERT VAR\n");

    if (toInsert->data == NULL) {
        printf("ERROR(add_at):: COULD NOT ALLOCATE MEMORY TO DATA POINTER\n");
        return false;
    }

    memcpy(toInsert->data, pointer, linkedList->itemSize);
//    printf("AFTER MEMCPY FUNCT\n");


    if (index == 0 && (linkedList->size == 0)) {
        //printf("ADDING TO EMPTY LIST\n");

        toInsert->next = NULL;
        toInsert->prev = NULL;
        linkedList->first = toInsert;
        linkedList->last = toInsert;

    } else if (index == 0) {
        //        printf("INDEX == 0\n");
        toInsert->next = (linkedList->first);
        toInsert->prev = NULL;
        linkedList->first->prev = toInsert;
        linkedList->first = toInsert;
    } else if (index == ((linkedList->size) - 1)) {

        //printf("INDEX == lastIndex\n");
        toInsert->prev = linkedList->last;
        toInsert->next = NULL;
        linkedList->last->next = toInsert;
        linkedList->last = toInsert;

    } else {

        // printf("INDEX == MIDDLE INDEX\n");
        Node *current = linkedList->first;
        int counter = 0;

        while (current != NULL) {

            if (index == counter) {

                current->prev->next = toInsert;
                toInsert->prev = current->prev;
                toInsert->next = current;
                current->prev = toInsert;
                break;
            }

            current = current->next;
            ++counter;
        }
    }

    (linkedList->size) += 1;

    //printf("SIZE:    %d\n", linkedList->size);

    return true;
}

// This function adds a node at the start of the linked list.
bool llist_add_first(LinkedList *linkedList, void *pointer) {

//    printf("add_first\n");
    // Use the add_at for this functionality.
    return llist_add_at(linkedList, 0, pointer);
}

// This function adds a node at the end of the linked list.
bool llist_add_last(LinkedList *linkedList, void *pointer) {

//    printf("add_last\n");

    // Determine the last index using the size.
    int lastIndex = (linkedList->size - 1) < 0 ? 0 : (linkedList->size - 1);

    // Use the add_at for this functionality.
    return llist_add_at(linkedList, lastIndex, pointer);
}

// This function returns the data at the index passed in as an argument.
void *llist_get(LinkedList *linkedList, int index) {

    // Check for NULL Pointers.
    if (linkedList == NULL) {
        printf("ERROR(get):: NULL POINTER IN ARGS\n");
        return NULL;
    }

    // Checking if index values are accurate.
    if (index > linkedList->size) {
        printf("Invalid Index (GET)\n");
        return NULL;
    }


    int counter = 0;
    Node *current = linkedList->first;

    // Loop through the list till the desired index and return data at that Node.
    while (current != NULL) {

        if (index == counter) {
            return current->data;
        }

        current = current->next;
        ++counter;
    }

    return NULL;
}

// This function searches for an element inside the list and returns it's index if found; Else -1.
int llist_index_of(LinkedList *linkedList, void *pointer) {

    // Check for NULL Pointers.
    if (linkedList == NULL || pointer == NULL) {
        printf("ERROR(index_of):: NULL POINTER IN ARGS\n");
        return -1;
    }

    // Create some pointers as helpers.
    Node *current = linkedList->first;
    int counter = 0;

    // Loop through the list and check for the desired value.
    while (current != NULL) {


        if (memcmp(current->data, pointer, (linkedList->itemSize)) == 0) {
            return counter;
        }

        current = current->next;
        counter += 1;
    }

    return -(1);
}

// This can be called to remove any Node from the Linked List.
void *llist_remove(LinkedList *linkedList, int index) {

    // Check for NULL Pointers.
    if (linkedList == NULL) {
        printf("ERROR(remove):: NULL POINTER IN ARGS\n");
        return false;
    }

    // Check for invalid Index parameters.
    if ((index < -1) || index >= (linkedList->size)) {
        printf("ERROR:: CANNOT ADD TO INVALID INDEX\n");
        return false;
    }


    // Create some pointers as helpers.
    void *toReturn = NULL;
    Node *current = NULL;


    // printf("INDEX:  %d\n", index);

    // Checking whether the LinkedList has Nodes or not.
    if ((linkedList->size) == -1) {
        printf("ERROR:: CANNOT REMOVE FROM AN EMPTY LIST\n");
        return NULL;
    }


    // This removes a Node from the front of the Linked list

    if (index == 0) {

        current = linkedList->first;
        toReturn = malloc(linkedList->itemSize);
        memcpy(toReturn, current->data, linkedList->itemSize);

        if (linkedList->size == 1) {

            linkedList->first = NULL;

        } else {

//            printf("HERE\n");
            linkedList->first = current->next;
            linkedList->first->prev = NULL;

        }
        // Removing a Node at the end of the list
    } else if (index == ((linkedList->size) - 1)) {

        current = linkedList->last;
        toReturn = malloc(linkedList->itemSize);
        memcpy(toReturn, current->data, linkedList->itemSize);

        linkedList->last = current->prev;
        linkedList->last->next = NULL;

        // Removing a Node between two nodes
    } else {

        current = linkedList->first;
        int counter = 0;


        while (current != NULL) {

            if (index == counter) {

                toReturn = malloc(linkedList->itemSize);
                memcpy(toReturn, current->data, linkedList->itemSize);

                current->prev->next = current->next;
                current->next->prev = current->prev;

                break;
            }

            current = current->next;
            ++counter;
        }
    }

    (linkedList->size)--;

    return toReturn;
}

void *llist_remove_first(LinkedList *linkedList) {

    // Call the llist_remove as it can do this already
    return llist_remove(linkedList, 0);
}

// This Function removes the last Node from a Linked List
void *llist_remove_last(LinkedList *linkedList) {

    // Check for NULL Pointers.
    if (linkedList == NULL) {
        printf("ERROR(remove_last):: NULL POINTER IN ARGS\n");
        return false;
    }

    // Determining the Last index
    int lastIndex = linkedList->size - 1;

    // Call the llist_remove as it can do this already
    return llist_remove(linkedList, lastIndex);
}

// This Function Deallocates all the memory a LinkedList Struct holds.
bool llist_destroy(LinkedList *linkedList) {

    // Check for NULL Pointers.
    if (linkedList == NULL) {
        printf("ERROR:: NULL ARGS IN DESTROY\n");
        return false;
    }

    // Start the loop from the second Node
    Node *current = linkedList->first;
    Node *next;


    // Destroy all the individual Nodes
    while (current != NULL) {  // next!= null


        next = current->next;

        free(current->data);
        free(current);

        current = next;
    }

    // Free type pointer and LinkedList struct pointer itself.
    free(linkedList->type);
    free(linkedList);

    return true;
}
