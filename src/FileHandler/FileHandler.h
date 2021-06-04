//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>

FILE* writeTextfile(char* filename);
FILE* readTextfile(char* filename);
FILE* writeBinaryFile(char* filename);
FILE* readBinaryFile(char* filename);

#endif //FILE_HANDLER_H
