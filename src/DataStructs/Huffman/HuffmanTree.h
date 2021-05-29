//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "../../Text/TextCounter.h"
#define NULL_CHAR '\0'

typedef struct HuffmanTree_St {
    char key;
    int sum;
    struct HuffmanTree_St *left, *right;
} HuffmanTree;

typedef struct HuffmanList_st {
    HuffmanTree* elem;
    struct HuffmanList_st *next;
} HuffmanList;

HuffmanTree* createHuffmanElement(LetterCount letter, HuffmanTree* left, HuffmanTree* right);
HuffmanList* countedLettersToHuffmanList(CountedLetters* letters);
HuffmanTree* appendTwoElements(HuffmanTree* elem1, HuffmanTree* elem2);

HuffmanTree* popFromStart(HuffmanList** list);
void insertHList(HuffmanList** list, HuffmanTree* tree);

int isLeaf(HuffmanTree* node);
int getHufHeight(HuffmanTree* tree);

#endif //HUFFMAN_TREE_H
