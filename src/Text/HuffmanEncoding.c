//
// Author: Mino
// Github: https://github.com/minoxs
//

#include <stdlib.h>
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

#define BUFFER_SIZE 128

// This will take the huffman tree and spit out a dictionary that is easier to deal with -- useful for encoding text
void Internal_GetEncodeValues(HuffmanTree* node, Dictionary* dict, char* POS_BUFFER, int pos) {
    // If the node is null, just stop recursion
    if (node == NULL)
        return;

    // If isLeaf (there is a valid key here), add to dictionary
    if (isLeaf(node)) {
        // Create Encoded String
        char* encodedKey = calloc(pos+1, sizeof(char));
        // Pass value from buffer into string
        for (int i = 0; i < pos; ++i) {
            encodedKey[i] = POS_BUFFER[i];
        }
        encodedKey[pos] = '\0'; // Add EOS element just to be sure
        // Adds to dictionary
        addElement(dict, node->key, encodedKey);
    }
    // Else move left/right
    else {
        POS_BUFFER[pos] = '0';
        Internal_GetEncodeValues(node->left, dict, POS_BUFFER, pos + 1);
        POS_BUFFER[pos] = '1';
        Internal_GetEncodeValues(node->right, dict, POS_BUFFER, pos + 1);
    }
}

/**
 * Transforms HuffmanTree into a Dictionary, which is easier to read from -- useful for encoding
 * @param tree
 * @return
 */
Dictionary getEncodeDictionary(HuffmanTree* tree) {
    Dictionary encode = initializeDictionary();

    char POS_BUFFER[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        POS_BUFFER[i] = '\0';
    }

    Internal_GetEncodeValues(tree, &encode, POS_BUFFER, 0);

    return encode;
}

// TODO 'Encode Text' (Text, EncodingTree) -> (EncodedText)

// TODO 'Decode Text' (EncodedText, EncodingTree) -> Text