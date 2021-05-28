//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "Dictionary.h"

/**
 * Initialize dictionary
 * @return
 */
Dictionary initializeDictionary() {
    return (Dictionary) {initializeDictKey(), initializeDictValue()};
}

/**
 * Add element to dictionary
 * @param dict
 * @param key
 * @param value
 */
void addElement(Dictionary* dict, char key, char* value) {
    addKey(&dict->keys, key);
    addValue(&dict->values, value);
}

/**
 * Get element from dictionary by key
 * Returns an empty string if not found or out of array
 * @param dict
 * @param key
 * @return
 */
char* getElementByKey(Dictionary* dict, char key) {
    int index = getIndexOfKey(&dict->keys, key);
    return (index >= 0)? getValueByIndex(&dict->values, index) : "";
}
