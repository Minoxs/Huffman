//
// Author: Mino
// Github: https://github.com/minoxs
//

#include <stdlib.h>
#include "HuffmanTree.h"

/**
 * Creates a huffman element (node)
 * @param letter
 * @param left
 * @param right
 * @return
 */
HuffmanTree* createHuffmanElement(LetterCount letter, HuffmanTree* left, HuffmanTree* right) {
    HuffmanTree* hte = malloc(sizeof(HuffmanTree));
    hte->key = letter.key;
    hte->sum = letter.count;
    hte->left = left;
    hte->right = right;
    return hte;
}

/**
 * Creates a list element from huffman element
 * @param element
 * @return
 */
HuffmanList* createListElement(HuffmanTree* element) {
    HuffmanList* list = malloc(sizeof(HuffmanList));
    list->elem = element;
    list->next = NULL;
    return list;
}

/**
 * Takes in counted letters and returns a list with all the LetterCount as HuffmanTree elements
 * @param letters
 * @return
 */
HuffmanList* countedLettersToHuffmanList(CountedLetters* letters) {
    HuffmanList* list = createListElement(createHuffmanElement(letters->letters[0], NULL, NULL));
    HuffmanList* aux = list;
    for (int i = 1; i < letters->arrSize; ++i) {
        aux->next = createListElement(createHuffmanElement(letters->letters[i], NULL, NULL));
        aux = aux->next;
    }
    return list;
}

/**
 * Pops the first element of the tree
 * @param list
 * @return
 */
HuffmanTree* popFromStart(HuffmanList** list) {
    HuffmanTree* elem = (*list)->elem;
    HuffmanList* next = (*list)->next;
    free(*list);
    *list = next;
    return elem;
}

/**
 * Inserts in the huffman list and keeps it in ascending sum order
 * @param list
 * @param tree
 */
void insertHList(HuffmanList** list, HuffmanTree* tree) {
    HuffmanList* prevList = NULL;
    HuffmanList* auxList = *list;

    // Move pointers
    while(auxList != NULL && tree->sum > auxList->elem->sum) {
        prevList = auxList;
        auxList = auxList->next;
    }

    // Creates list element from huffman element
    HuffmanList* newElem = createListElement(tree);

    // Adds it to the list -- checking if it's at the start or not
    if (prevList == NULL) {
        newElem->next = *list;
        *list = newElem;
    }
    else {
        prevList->next = newElem;
        newElem->next = auxList;
    }
}

/**
 * Takes two HuffmanTree elements and returns one with the sum of the two
 * key is set to NULL_CHAR
 * @param elem1
 * @param elem2
 * @return
 */
HuffmanTree* appendTwoElements(HuffmanTree* elem1, HuffmanTree* elem2) {
    return createHuffmanElement(
            (LetterCount) {NULL_CHAR, elem1->sum+elem2->sum}, elem1, elem2
            );
}

/**
 * Is the given node a leaf
 * @param node
 * @return
 */
int isLeaf(HuffmanTree* node) {
    return node->left == NULL && node->right == NULL;
}