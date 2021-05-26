//
// Author: Mino
// Github: https://github.com/minoxs
//

#include "HuffmanEncoding.h"

/**
 * Creates the encoding tree given the counted letters in order
 * @param letters
 * @return
 */
HuffmanTree* createEncodingTree(CountedLetters* letters) {
    int size = letters->arrSize;
    HuffmanList* list = countedLettersToHuffmanList(letters);

    while (size > 1) {
        HuffmanTree* elem1 = popFromStart(&list);
        HuffmanTree* elem2 = popFromStart(&list);
        insertHList(&list, appendTwoElements(elem1, elem2));
        size -= 1;
    }

    return popFromStart(&list);
}

// TODO 'Encode Text' (Text, EncodingTree) -> (EncodedText)

// TODO 'Decode Text' (EncodedText, EncodingTree) -> Text