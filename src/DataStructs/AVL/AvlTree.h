//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef INC_2_ESTRUTURADEDADOS_AVL_H
#define INC_2_ESTRUTURADEDADOS_AVL_H

// TODO Move AVL structure inside .c file?
typedef struct AVL_st {
    char key;
    int count;
    int balanceFactor;
    struct AVL_st *left;
    struct AVL_st *right;
} AVL;

AVL* initializeAVL();

int insertNode(AVL **root, char key, int count);
void removeNode(AVL **removeNode, AVL *removeNodeFather);
void printTree(AVL *root);

int getHeight(AVL *node);
int countNodes(AVL *root);

#endif //INC_2_ESTRUTURADEDADOS_AVL_H
