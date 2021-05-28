//
// Author: Mino
// Github: https://github.com/minoxs
//

#include <stdlib.h>
#include "DictValue.h"

// Definition of what ArrayList is holding
struct ArrayInfo_st {
    char* value;
};

/**
 * Initializes DictValue
 * @return
 */
DictValue initializeDictValue() {
    return (DictValue) {initializeList()};
}

/**
 * Adds value to DictValue
 * @param dictValue
 * @param value
 */
void addValue(DictValue* dictValue, char* value) {
    struct ArrayInfo_st* info = malloc(sizeof(struct ArrayInfo_st));
    info->value = value;

    listAppend(&dictValue->valueList, info);
}

/**
 * Gets value at given index, returns empty string if not in DictValue
 * @param dictValue
 * @param index
 * @return
 */
char* getValueByIndex(DictValue* dictValue, int index) {
    struct ArrayInfo_st* info = listGet(&dictValue->valueList, index);
    return (info == NULL) ? "" : info->value;
}