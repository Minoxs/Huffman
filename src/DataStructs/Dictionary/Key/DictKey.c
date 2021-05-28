//
// Author: Mino
// Github: https://github.com/minoxs
//

#include <stdlib.h>
#include "DictKey.h"

// Definition of what ArrayList is holding
struct ArrayInfo_st {
    char key;
};

/**
 * Initializes DictKey
 * @return
 */
DictKey initializeDictKey() {
    return (DictKey) {initializeList()};
}

/**
 * Adds key to DictKey
 * @param dictKey
 * @param key
 */
void addKey(DictKey* dictKey, char key) {
    struct ArrayInfo_st* info = malloc(sizeof(struct ArrayInfo_st));
    info->key = key;

    listAppend(&dictKey->keyList, info);
}

/**
 * Returns index of given key
 * @param dictKey
 * @param key
 * @return
 */
int getIndexOfKey(DictKey* dictKey, char key) {
    ArrayList* list = &dictKey->keyList;
    for (int i = 0; i < list->size; ++i) {
        if (listGet(list, i)->key == key) {
            return i;
        }
    }
    return -1;
}