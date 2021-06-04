//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "FileHandler.h"
#include "../Text/TextCounter.h"
#include "../DataStructs/Huffman/HuffmanTree.h"
#include "../Text/HuffmanEncoding.h"

FILE* writeTextfile(char* filename) {
    return fopen(filename, "w");
}

FILE* readTextfile(char* filename) {
    return fopen(filename, "r");
}

FILE* writeBinaryFile(char* filename) {
    return fopen(filename, "wb");
}

FILE* readBinaryFile(char* filename) {
    return fopen(filename, "rb");
}

/**
 * Takes in all required files and does everything needed to encode the text
 * @param text File in "r" mode
 * @param encodedTextOutput File in "wb" mode
 * @param encodedTreeOutput File in "wb" mode
 * @return
 */
int RunEncodeText(FILE* text, FILE* encodedTextOutput, FILE* encodedTreeOutput) {
    CountedLetters* table = parseText(text);
    if (table == NULL)
        return NULL_TABLE_ERROR;

    HuffmanTree* tree = createEncodingTree(table);
    saveTreeToFile(tree, encodedTreeOutput);
    encodeText(text, tree, encodedTextOutput);

    return 0;
}

/**
 * Takes in all required files and does everything needed to decode the text
 * @param encodedText File in "rb"
 * @param encodedTree File in "rb"
 * @param output File in "w" or NULL (will print to console)
 */
int RunDecodeText(FILE* encodedText, FILE* encodedTree, FILE* output) {
    HuffmanTree* tree = loadTreeFromFile(encodedTree);
    if (tree == NULL)
        return NULL_TREE_ERROR;

    decodeText(encodedText, tree, output);

    return 0;
}