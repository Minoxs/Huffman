//
// Author: Mino
// Github: https://github.com/minoxs
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TextCounter.h"
#include "../DataStructs/AVL/AvlTree.h"

#define BUFFER_SIZE 256
/**
 * Finds smallest element of the tree and its father
 * @param tree
 * @param node -- returned by parameter
 * @param nodeFather -- returned by parameter
 */
void findSmallest(AVL *tree, AVL **node, AVL **nodeFather) {
    if (tree != NULL) {
        AVL *returnNode = tree, *returnFatherNode = *nodeFather;
        AVL *nodeAux1 = NULL, *nodeFatherAux1 = tree, *nodeAux2 = NULL, *nodeFatherAux2 = tree;
        findSmallest(tree->left,  &nodeAux1, &nodeFatherAux1);
        findSmallest(tree->right, &nodeAux2, &nodeFatherAux2);

        if (nodeAux1 != NULL || nodeAux2 != NULL) {
            if (nodeAux2 == NULL || (nodeAux1 != NULL && nodeAux1->count < nodeAux2->count)) {
                returnNode = nodeAux1;
                returnFatherNode = nodeFatherAux1;
            }
            else {
                returnNode = nodeAux2;
                returnFatherNode = nodeFatherAux2;
            }

            if (returnNode->count > tree->count) {
                returnNode = tree;
                returnFatherNode = *nodeFather;
            }
        }

        *node = returnNode;
        *nodeFather = returnFatherNode;
    }
}

/**
 * Returns element with smallest count from tree in CLT element form
 * @param tree
 * @return CLT
 */
CLT popSmallestFromTree(AVL **tree) {
    AVL *smallest, *father = NULL;
    findSmallest(*tree, &smallest, &father);

    CLT toReturn = {smallest->key, smallest->count};
    if (smallest == *tree && smallest->left == NULL && smallest->right == NULL) *tree = NULL;
    removeNode(&smallest, father);
    return toReturn;
}

/**
 * Given a tree of counted letters, returns a CLT array in ascending order of those counted letters
 * @param countTree will be NULL at the end
 * @return
 */
CLT* flattenTree(AVL **countTree) {
    int size = countNodes(*countTree);
    CLT *table = calloc(size+1, sizeof(char));
    CLT tableInfo = {'\0', size};
    table[0] = tableInfo;
    for (int i = 1; i < size; ++i) {
        table[i] = popSmallestFromTree(countTree);
    }
    return table;
}

/**
 * Given a text file, counts how many of each letter there are
 * @param text
 * @return CLT array in ascending order of letter count
 */
CLT* parseText(FILE* text) {
    if (text == NULL) return NULL;
    AVL *countTree = initializeAVL();
    char toCount[BUFFER_SIZE];
    while (fgets(toCount, BUFFER_SIZE, text)) {
        for (int i = 0; i < strlen(toCount); ++i) {
            insertNode(&countTree, toCount[i], 1);
        }
    }
    return flattenTree(&countTree);
}