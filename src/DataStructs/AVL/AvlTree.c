//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "stdio.h"
#include "stdlib.h"
#include "AvlTree.h"

/**
 * Initializes an AVL
 * @return NULL
 */
AVL* initializeAVL() {
    return NULL;
}

/**
 * Use when balancing factor of p greater than 0 and p->left greater than 0
 * @param p Node
 */
void rotateRight(AVL **p) {
    AVL *aux = *p;
    AVL *u = aux->left;

    aux->left = u->right;
//    printf("R: %c - %d;%c - %d\n", aux->key, aux->balanceFactor, u->key, u->balanceFactor);
    aux->balanceFactor = 0;
    u->right = aux;
    u->balanceFactor  = 0;
//    printf("R: %c - %d;%c - %d\n", aux->key, aux->balanceFactor, u->key, u->balanceFactor);
    *p = u;
}

/**
 * Use when balancing factor of p less than 0 and p->right less than 0
 * @param p Node
 */
void rotateLeft(AVL **p) {
    AVL *aux = *p;
    AVL *z = aux->right;

    aux->right = z->left;
//    printf("L: %c - %d;%c - %d\n", aux->key, aux->balanceFactor, z->key, z->balanceFactor);
    aux->balanceFactor = 0;
    z->left = aux;
    z->balanceFactor = 0;
//    printf("L: %c - %d;%c - %d\n", aux->key, aux->balanceFactor, z->key, z->balanceFactor);
    *p = z;
}

/**
 * Use when balancing factor of p greater than 0 and p->left less than 0
 * @param p Node
 */
void rotateDoubleRight(AVL **p) {
    AVL *aux = *p;
    AVL *u = aux->left;
    AVL *v = u->right;

//    printf("RR: %c - %d;%c - %d;%c - %d\n", aux->key, aux->balanceFactor, u->key, u->balanceFactor, v->key, v->balanceFactor);
    u->right = v->left;

    if (v->balanceFactor == -1)
        u->balanceFactor = 1;
    else
        u->balanceFactor = 0;
    v->left = u;

    aux->left = v->right;

    if (v->balanceFactor == 1)
        aux->balanceFactor = -1;
    else
        aux->balanceFactor = 0;
    v->right = aux;

    v->balanceFactor = 0;
//    printf("RR: %c - %d;%c - %d;%c - %d\n", aux->key, aux->balanceFactor, u->key, u->balanceFactor, v->key, v->balanceFactor);
    *p = v;
}

/**
 * Use when balancing factor of p less than 0 and p->right greater than 0
 * @param p Node
 */
void rotateDoubleLeft(AVL **p) {
    AVL *aux = *p;
    AVL *z = aux->right;
    AVL *y = z->left;

//    printf("LL: %c - %d;%c - %d;%c - %d\n", aux->key, aux->balanceFactor, z->key, z->balanceFactor, y->key, y->balanceFactor);
    z->left = y->right;

    if (y->balanceFactor == 1)
        z->balanceFactor = -1;
    else
        z->balanceFactor = 0;
    y->right = z;

    aux->right = y->left;

    if (y->balanceFactor == -1)
        aux->balanceFactor = 1;
    else
        aux->balanceFactor = 0;
    y->left = aux;

    y->balanceFactor = 0;
//    printf("LL: %c - %d;%c - %d;%c - %d\n", aux->key, aux->balanceFactor, z->key, z->balanceFactor, y->key, y->balanceFactor);
    *p = y;
};

/**
 * Inserts node in tree
 * @param root
 * @param key
 */
int insertNode(AVL **root, char key) {
    AVL *tree = *root;
    int alterBalance = 1;

    // If node is NULL, just add it to the tree
    if (tree == NULL) {
        tree = malloc(sizeof(AVL));
        tree->key  = key;
        tree->left  = initializeAVL();
        tree->right  = initializeAVL();
        tree->balanceFactor = 0;
        tree->count = 1;
    }
    else if (key == tree->key) {
        tree->count += 1;
        return 0;
    }
    else {
        // If the key to add is lesser than this node's key, add to the left
        if (key < tree->key) {
            alterBalance = insertNode(&tree->left, key);
            // If this insert would unbalance tree, do a rotation -- but only
            if (alterBalance) {
                switch(tree->balanceFactor) {
                    case -1: tree->balanceFactor = 0; alterBalance = 0; break;
                    case  0: tree->balanceFactor = 1; break;
                    case  1:
                        if (tree->left->balanceFactor == 1)
                            rotateRight(&tree);
                        else
                            rotateDoubleRight(&tree);
                        alterBalance = 0;
                        break;
                }
            }
        }
        // Else add to the right
        else {
            alterBalance = insertNode(&tree->right, key);
            // Same as above
            if (alterBalance) {
                switch(tree->balanceFactor) {
                    case -1:
                        if (tree->right->balanceFactor == -1)
                            rotateLeft(&tree);
                        else
                            rotateDoubleLeft(&tree);
                        alterBalance = 0;
                        break;
                    case  0: tree->balanceFactor = -1; break;
                    case  1: tree->balanceFactor = 0; alterBalance = 0; break;
                }
            }
        }
    }
    *root = tree;
    return alterBalance;
}

// Internal method to print the tree
void private_printTree(AVL *node, int level) {
    if (node != NULL) {
        for (int i = 0; i < level; ++i) {
            putchar('=');
        }
        printf("%c - %d - %d\n", node->key, node->balanceFactor, node->count);
        private_printTree(node->left, level + 1);
        private_printTree(node->right, level + 1);
    }
}

/**
 * Prints the given tree
 * @param root
 */
void printTree(AVL *root) {
    // Chama o método interno que vai lidar com os níveis
    if (root != NULL)
        private_printTree(root, 1);
    else
        printf("Empty Tree!\n");
};

/**
 * Counts the amount of nodes of the given tree
 * @param root
 * @return Node Count
 */
int countNodes(AVL *root) {
    if (root != NULL) {
        return countNodes(root->left)+countNodes(root->right)+1;
    }
    else return 0;
};

// TODO fix removeNode to re-balance tree after use -- might have to change signature to include original tree.
/**
 * Removes node pointed by *removeNode. Requires *removeNodeFather to be given if it's a leaf (Always pass it as precaution).
 * @param removeNode
 * @param removeNodeFather
 */
void removeNode(AVL **removeNode, AVL *removeNodeFather) {
    AVL *aux = *removeNode;
    AVL *largestLeftRoot = NULL;
    AVL *largestLeft = aux;

    // If given node is not a leaf or tree root
    if (aux != NULL && (aux->right != NULL || aux->left != NULL)) {
        // Find largest of left tree and its father
        while (1) {
            if (largestLeft->right != NULL) {
                largestLeftRoot = largestLeft;
                largestLeft = largestLeft->right;
            }
            else if (largestLeft->left != NULL) {
                largestLeftRoot = largestLeft;
                largestLeft = largestLeft->left;
            }
            else break;
        }

        // Swap the largest of left subtree into the root
        aux->count = largestLeft->count;
        aux->key   = largestLeft->key;
        *removeNode = aux;

        // Free deleted node
        free(largestLeft);

        // Remove the pointer to the old node
        if (largestLeftRoot != NULL) {
            if (largestLeftRoot->right != NULL)
                largestLeftRoot->right = NULL;
            else
                largestLeftRoot->left = NULL;
        }
    }
    // If it's a leaf or tree's root
    else {
        if (removeNodeFather != NULL) {
            if (removeNodeFather->right == *removeNode)
                removeNodeFather->right = NULL;
            else if (removeNodeFather->left == *removeNode)
                removeNodeFather->left = NULL;
            else
                printf("removeNodeFather given is not father of removeNode\n");
        }

        free(*removeNode);
        *removeNode = NULL;
    }
}

/**
 * Gets the height of a node
 * @param node
 * @return
 */
int getHeight(AVL *node) {
    if (node == NULL)
        return 0;
    else {
        int left, right;
        left = getHeight(node->left);
        right = getHeight(node->right);
        if (left >= right)
            return 1+left;
        else
            return 1+right;
    }
}
