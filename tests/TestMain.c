//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "../src/DataStructs//AVL/AvlTree.h"
#include "../src/FileHandler/FileHandler.h"
#include "../src/Text/TextCounter.h"

void Tree_AVL_Test() {
    AVL *tree = initializeAVL();

    char keys[] = {'i', 'g', 'e', 'k', 'z', 'h', 'j', 'm', 'n'};
    for (int i = 0; i < sizeof(keys)/sizeof(char); ++i) {
        insertNode(&tree, keys[i]);
    }

    printTree(tree);
}

void File_Test() {
    FILE *text = getTextFile("../tests/Test.txt");
    if (text != NULL) {
        CLT *table = parseText(text);
        for (int i = 1; i < table[0].count; ++i) {
            printf("%d %c %d\n", i, table[i].key, table[i].count);
        }
    }
}

int main() {
    Tree_AVL_Test();
    File_Test();
    return 0;
}