//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

#include "../DataStructs/Huffman/HuffmanTree.h"
#include "../DataStructs/Dictionary/Dictionary.h"

HuffmanTree* createEncodingTree(CountedLetters* letters);
Dictionary getEncodeDictionary(HuffmanTree* tree);

void encodeText(FILE* text, HuffmanTree* tree, FILE* output);
void decodeText(FILE* encodedText, HuffmanTree* tree, FILE* output);

void saveTreeToFile(HuffmanTree* tree, FILE* ptr);
HuffmanTree* loadTreeFromFile(FILE* ptr);

#endif //HUFFMAN_ENCODING_H
