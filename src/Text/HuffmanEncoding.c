//
// Author: Mino
// Github: https://github.com/minoxs
//

#include <stdlib.h>
#include <string.h>
#include "HuffmanEncoding.h"

#define BUFFER_SIZE 256

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
    int size = getHufHeight(tree)+2;

    char* POS_BUFFER = calloc(size, sizeof(char));
    for (int i = 0; i < size; ++i) {
        POS_BUFFER[i] = '\0';
    }

    Internal_GetEncodeValues(tree, &encode, POS_BUFFER, 0);

    free(POS_BUFFER);

    return encode;
}

/**
 * Encodes the text with the given tree and saves to the output file
 * @param text   (FILE* in r  mode)
 * @param tree   (HuffmanTree*)
 * @param output (FILE* in wb mode)
 */
void encodeText(FILE* text, HuffmanTree* tree, FILE* output) {
    char ENCODE_BUFFER[BUFFER_SIZE];
    Dictionary encode = getEncodeDictionary(tree);
    fputc(0x00, output); // The first byte tells how many bits to ignore from the last byte

    // Must batch the bits into batches of 8 (byte) before writing to file
    int size = 0;
    char byte = (char) 0x00;
    while (fgets(ENCODE_BUFFER, BUFFER_SIZE, text)) {
        for (int i = 0; i < BUFFER_SIZE && ENCODE_BUFFER[i] != '\0'; ++i) {
            char* toEncode = getElementByKey(&encode, ENCODE_BUFFER[i]);
            size_t strSize = strlen(toEncode);

            for (int j = 0; j < strSize; ++j) {
                byte = (char) (byte << 1);
                if (toEncode[j] == '1')
                    byte += 1;
                size += 1;
                if (size == 8) {
                    fputc(byte, output);
                    size = 0;
                }
            }
        }
    }

    // Writes the last byte if it wasn't batched with extra 0s needed
    if (size > 0) {
        byte = (char) (byte << (8-size));
        fputc(byte, output);
        byte = (char) (8-size);
    }
    else {
        byte = (char) 0x00;
    }

    // Needs to write down how many bits to ignore from the last character
    fseek(output, 0, SEEK_SET);
    fputc(byte, output);
    fseek(output, 0, SEEK_END);
}

// Internal recursive method to save tree to file
void Internal_saveTreeToFile(HuffmanTree* node, FILE* ptr)
{
    if (node != NULL) {
        fputc(node->key, ptr);
        if (node->key == NULL_CHAR) {
            Internal_saveTreeToFile(node->left, ptr);
            Internal_saveTreeToFile(node->right, ptr);
        }
    }
    else {
        fputc(NULL_CHAR, ptr);
    }
}

// Internal recursive method to load tree from file
HuffmanTree* Internal_loadTreeFromFile(FILE* ptr) {
    char byte = (char) fgetc(ptr);
    HuffmanTree* newNode = createHuffmanElement((LetterCount) {byte, 0}, NULL, NULL);
    if (byte == NULL_CHAR) {
        newNode->left = Internal_loadTreeFromFile(ptr);
        newNode->right = Internal_loadTreeFromFile(ptr);
    }
    return newNode;
}

/**
 * Loads the from the file given
 * @param ptr
 * @return
 */
HuffmanTree* loadTreeFromFile(FILE* ptr) {
    return Internal_loadTreeFromFile(ptr);
}

/**
 * Salva a árvore no arquivo apontado
 * @param tree
 * @param ptr FILE* em modo "wb"
 */
void saveTreeToFile(HuffmanTree* tree, FILE* ptr) {
    Internal_saveTreeToFile(tree, ptr);
}

// TODO 'Decode Text' (EncodedText, EncodingTree) -> Text