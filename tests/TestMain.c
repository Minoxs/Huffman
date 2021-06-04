//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "../src/DataStructs//AVL/AvlTree.h"
#include "../src/FileHandler/FileHandler.h"
#include "../src/Text/TextCounter.h"
#include "../src/DataStructs/Huffman/HuffmanTree.h"
#include "../src/Text/HuffmanEncoding.h"

void Tree_AVL_Test() {
    AVL *tree = initializeAVL();

    char keys[] = {'i', 'g', 'e', 'k', 'z', 'h', 'j', 'm', 'n'};
    for (int i = 0; i < sizeof(keys)/sizeof(char); ++i) {
        insertNode(&tree, keys[i], 1);
    }

    printTree(tree);
}

void DictionaryTest() {
    Dictionary test = initializeDictionary();
    addElement(&test, 'c', "peste");
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

void File_Test() {
    FILE *text = readTextfile("../tests/Test.txt");
    if (text != NULL) {
        CountedLetters* table = parseText(text);
        if (table == NULL) return;

        for (int i = 0; i < table->arrSize; ++i) {
            LetterCount letter = table->letters[i];
            printf("%d %c %d\n", i, letter.key, letter.count);
        }

        HuffmanTree* tree = createEncodingTree(table);
        FILE* output = writeBinaryFile("../tests/Encoded.huf");
        encodeText(text, tree, output);
        fclose(output);
        FILE* treeFile = writeBinaryFile("../tests/EncodedTree.huftree");
        saveTreeToFile(tree, treeFile);
        fclose(treeFile);

        Dictionary dictBefore = getEncodeDictionary(tree);
        printDictionary(&dictBefore);
    }
    fclose(text);
    FILE* openTree = readBinaryFile("../tests/EncodedTree.huftree");
    HuffmanTree* tree = loadTreeFromFile(openTree);
    Dictionary dictAfter = getEncodeDictionary(tree);
    printDictionary(&dictAfter);
    fclose(openTree);
}

void Read_Write_Test() {
    FILE* treeFile = readBinaryFile("../tests/EncodedTree.huftree");
    HuffmanTree* tree = loadTreeFromFile(treeFile);
    fclose(treeFile);

    FILE* textFile = readBinaryFile("../tests/Encoded.huf");
    FILE* outputFile = writeTextfile("../tests/Decoded.txt");
    decodeText(textFile, tree, outputFile);
    fclose(textFile);
    fclose(outputFile);
}

int main() {
    Tree_AVL_Test();
    DictionaryTest();
    File_Test();
    Read_Write_Test();
    return 0;
}