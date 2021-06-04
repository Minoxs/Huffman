//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "FileHandler.h"

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

// TODO 'Get Encoded Text' (EncodedFile, EncodingFile) -> (EncodedText, EncodingTree)
