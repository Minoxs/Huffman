//
// Author: Mino
// Github: https://github.com/minoxs
//

/*
 * Every file path used in the test functions assume that the executable is inside cmake-build-debug or cmake-build-release
 */

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

void ManualEncodeText_And_Dictionary_Test() {
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

void Encode_Text_Test() {
    FILE* text = readTextfile("../tests/Test.txt");
    FILE* encodedTextOutput = writeBinaryFile("../tests/Encoded.huf");
    FILE* encodedTreeOutput = writeBinaryFile("../tests/EncodedTree.huftree");

    RunEncodeText(text, encodedTextOutput, encodedTreeOutput);

    fclose(text);
    fclose(encodedTextOutput);
    fclose(encodedTreeOutput);
}

void Decode_Text_Test() {
    FILE* textFile = readBinaryFile("../tests/Encoded.huf");
    FILE* treeFile = readBinaryFile("../tests/EncodedTree.huftree");
    FILE* outputFile = writeTextfile("../tests/Decoded.txt");

    RunDecodeText(textFile, treeFile, outputFile);

    fclose(textFile);
    fclose(treeFile);
    fclose(outputFile);
}

int main() {
    Tree_AVL_Test();
    DictionaryTest();
    ManualEncodeText_And_Dictionary_Test();
    Encode_Text_Test();
    Decode_Text_Test();
    return 0;
}