//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef HUFFMAN_ARRAYLIST_H
#define HUFFMAN_ARRAYLIST_H

#define LIST_STEP_SIZE 64

// Array List holds pointers of type ArrayInfo
// This struct must be defined when used
typedef struct ArrayInfo_st ArrayInfo;

typedef struct ArrayList_st {
    int size;
    int maxSize;
    ArrayInfo** infoArray;
} ArrayList;

ArrayList initializeList();
void listAppend(ArrayList* list, ArrayInfo* info);
ArrayInfo* listGet(ArrayList* list, int index);

#endif //HUFFMAN_ARRAYLIST_H
