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

#endif //HUFFMAN_ENCODING_H
