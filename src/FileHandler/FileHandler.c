//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "FileHandler.h"

FILE* getTextFile(char* filename) {
    return fopen(filename, "r");
}

FILE* openOutputFile(char* filename) {
    return fopen(filename, "wb");
}

// TODO 'Get Encoded Text' (EncodedFile, EncodingFile) -> (EncodedText, EncodingTree)
