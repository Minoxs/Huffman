//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef HUFFMAN_DICTIONARY_H
#define HUFFMAN_DICTIONARY_H

#include "Key/DictKey.h"
#include "Value/DictValue.h"

typedef struct Dictionary_st {
    DictKey keys;
    DictValue values;
} Dictionary;

Dictionary initializeDictionary();

void addElement(Dictionary* dict, char key, char* value);
char* getElementByKey(Dictionary* dict, char key);

#endif //HUFFMAN_DICTIONARY_H
