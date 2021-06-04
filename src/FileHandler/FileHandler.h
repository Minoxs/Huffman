//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include "../ErrorCodes.h"

FILE* writeTextfile(char* filename);
FILE* readTextfile(char* filename);
FILE* writeBinaryFile(char* filename);
FILE* readBinaryFile(char* filename);

int RunEncodeText(FILE* text, FILE* encodedTextOutput, FILE* encodedTreeOutput);
int RunDecodeText(FILE* encodedText, FILE* encodedTree, FILE* output);

#endif //FILE_HANDLER_H
