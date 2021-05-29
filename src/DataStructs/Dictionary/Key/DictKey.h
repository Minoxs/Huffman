//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef HUFFMAN_DICTKEY_H
#define HUFFMAN_DICTKEY_H

#include "../../ArrayList/ArrayList.h"

typedef struct DictKey_st {
    ArrayList keyList;
} DictKey;

DictKey initializeDictKey();
void addKey(DictKey* dictKey, char key);
int getIndexOfKey(DictKey* dictKey, char key);
char getKeyByIndex(DictKey* dictKey, int index);

#endif //HUFFMAN_DICTKEY_H
