//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "ArrayList.h"

#include "ArrayList.h"
#include "stdlib.h"

/**
 * Initializes ArrayList
 * @return
 */
ArrayList initializeList() {
    ArrayInfo** infoArray = calloc(LIST_STEP_SIZE, sizeof(ArrayInfo*));
    return (ArrayList) {0, LIST_STEP_SIZE, infoArray};
}

/**
 * Increases array list size
 * @param list
 */
void increaseListMaxSize(ArrayList* list) {
    // Add more memory for the new elements
    ArrayInfo** newInfoArray = calloc(list->maxSize+LIST_STEP_SIZE, sizeof(ArrayInfo*));
    // Copy over the elements
    for (int i = 0; i < list->size; ++i) {
        newInfoArray[i] = list->infoArray[i];
    }
    // Free previous array
    free(list->infoArray);
    // Mark Increased size
    list->maxSize += LIST_STEP_SIZE;
    // Adds the new array to the ArrayList
    list->infoArray = newInfoArray;
}

/**
 * Adds new element to the list
 * @param list
 * @param info
 */
void listAppend(ArrayList* list, ArrayInfo* info) {
    if (list->size == list->maxSize)
        increaseListMaxSize(list);

    list->infoArray[list->size] = info;
    list->size += 1;
}

/**
 * Gets the element at a specific index
 * @param list
 * @param index
 * @return NULL | struct ArrayInfo_st
 */
ArrayInfo* listGet(ArrayList* list, int index) {
    return (index >= list->maxSize) ? NULL : list->infoArray[index];
}
