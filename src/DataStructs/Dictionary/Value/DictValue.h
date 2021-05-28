//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef HUFFMAN_DICTVALUE_H
#define HUFFMAN_DICTVALUE_H

#include "../../ArrayList/ArrayList.h"

typedef struct DictValue_st {
    ArrayList valueList;
} DictValue;

DictValue initializeDictValue();
void addValue(DictValue* dictValue, char* value);
char* getValueByIndex(DictValue* dictValue, int index);

#endif //HUFFMAN_DICTVALUE_H
