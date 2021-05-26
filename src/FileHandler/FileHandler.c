//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "FileHandler.h"

FILE* getTextFile(char* filename) {
    return fopen(filename, "r");
}

// TODO 'Create HuffmanTree Encoded File & HuffmanTree Encoding Table File' (EncodedText, EncodingTree) -> (EncodedFile, EncodingFile)

// TODO 'Get Encoded Text' (EncodedFile, EncodingFile) -> (EncodedText, EncodingTree)
