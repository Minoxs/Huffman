//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "../src/DataStructs//AVL/AvlTree.h"
#include "../src/FileHandler/FileHandler.h"
#include "../src/Text/TextCounter.h"
#include "../src/DataStructs/Huffman/HuffmanTree.h"
#include "../src/Text/HuffmanEncoding.h"
#include "../src/DataStructs/Dictionary/Dictionary.h"

void Tree_AVL_Test() {
    AVL *tree = initializeAVL();

    char keys[] = {'i', 'g', 'e', 'k', 'z', 'h', 'j', 'm', 'n'};
    for (int i = 0; i < sizeof(keys)/sizeof(char); ++i) {
        insertNode(&tree, keys[i], 1);
    }

    printTree(tree);
}

void File_Test() {
    FILE *text = getTextFile("../tests/Test.txt");
    if (text != NULL) {
        CountedLetters* table = parseText(text);
        if (table == NULL) return;

        for (int i = 0; i < table->arrSize; ++i) {
            LetterCount letter = table->letters[i];
            printf("%d %c %d\n", i, letter.key, letter.count);
        }

        HuffmanTree* tree = createEncodingTree(table);
    }
}

void DictionaryTest() {
    Dictionary test = initializeDictionary();
    addElement(&test, 'c', "asdsasdasdasd");
    addElement(&test, 'e', "asdasdasdsagsssg");
    addElement(&test, 'a', "0000010");
    addElement(&test, 'b', "bananaaaaaaaa");
    printf(
            "%s\n%s\n%s\n",
            getElementByKey(&test, 'c'),
            getElementByKey(&test, 'b'),
            getElementByKey(&test, 'a')
    );
}

int main() {
    Tree_AVL_Test();
    File_Test();
    DictionaryTest();
    return 0;
}