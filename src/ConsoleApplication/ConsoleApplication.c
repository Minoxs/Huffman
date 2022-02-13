//
// Author: Mino
// Github: https://github.com/minoxs
//

#include <stdio.h>
#include <string.h>
#include "../ErrorCodes.h"
#include "../FileHandler/FileHandler.h"

void PrintHelpHeader() {
    printf("Usage:\n"
            " Output params never require to add the output extension.\n\n");
}

void PrintEncodeHelp() {
    printf(" Encode text:\n"
           "  Encodes the (ascii) text file in Text_File_Path and saves on the other params.\n"
           "   ./Huffman encode <Text_File_Path> <Encoded_Text_Output_Name> <Encoded_Tree_Output_Name>\n\n");
}

void PrintDecodeHelp() {
    printf(" Decode Text:\n"
           "  Decodes the text file with the given tree, and outputs to given file path.\n"
           "   ./Huffman decode <Encoded_Text_Path> <Encoded_Tree_Path> <Decoded_Text_Output_Path>\n"
           "  Decodes the text file with the given tree and prints to console.\n"
           "   ./Huffman decode <Encoded_Text_Path> <Encoded_Tree_Path>\n\n");
}

void PrintFullHelp() {
    PrintHelpHeader();
    PrintEncodeHelp();
    PrintDecodeHelp();
}

#define BASIC_NUM_ARGUMENTS 1
#define MINIMUM_ENCODE_ARGUMENTS 4
#define MINIMUM_DECODE_ARGUMENTS 3

int main(int argc, char* argv[]) {

    char* ERROR_RETURN;
    char NAME_BUFFER[BUFSIZ];

    if (argc < BASIC_NUM_ARGUMENTS + 1) {
        printf("Wrong Number of Arguments!\n");
        PrintFullHelp();
        return WRONG_NUMBER_OF_ARGUMENTS_ERROR;
    }

    if (!strcmp(argv[1], "encode")) {
        if (argc < MINIMUM_ENCODE_ARGUMENTS + 1) {
            printf("Wrong Number of Arguments!\n");
            PrintHelpHeader();
            PrintEncodeHelp();
            return WRONG_NUMBER_OF_ARGUMENTS_ERROR;
        }

        FILE *inputText, *outputText, *outputTree;

        inputText = readTextfile(argv[2]);
        if (inputText == NULL) {
            ERROR_RETURN = argv[2];
            goto READ_ERROR;
        }

        strcpy(NAME_BUFFER, argv[3]);
        strcat(NAME_BUFFER, ".huf");
        outputText = writeBinaryFile(NAME_BUFFER);
        if (outputText == NULL) {
            ERROR_RETURN = NAME_BUFFER;
            goto WRITE_ERROR;
        }

        strcpy(NAME_BUFFER, argv[4]);
        strcat(NAME_BUFFER, ".huftree");
        outputTree = writeBinaryFile(NAME_BUFFER);
        if (outputTree == NULL) {
            ERROR_RETURN = NAME_BUFFER;
            goto WRITE_ERROR;
        }

        int returnCode = RunEncodeText(inputText, outputText, outputTree);
        if (returnCode)
            printf("Error %d while encoding text\n", returnCode);
        fclose(inputText);
        fclose(outputText);
        fclose(outputTree);
        return returnCode;
    }
    else if (!strcmp(argv[1], "decode")) {
        if (argc < MINIMUM_DECODE_ARGUMENTS + 1) {
            printf("Wrong Number of Arguments!\n");
            PrintHelpHeader();
            PrintDecodeHelp();
            return WRONG_NUMBER_OF_ARGUMENTS_ERROR;
        }

        FILE *inputEncodedText, *inputEncodedTree, *outputText;

        inputEncodedText = readBinaryFile(argv[2]);
        if (inputEncodedText == NULL) {
            ERROR_RETURN = argv[2];
            goto READ_ERROR;
        }

        inputEncodedTree = readBinaryFile(argv[3]);
        if (inputEncodedTree == NULL) {
            ERROR_RETURN = argv[3];
            goto READ_ERROR;
        }

        if (argc >= MINIMUM_DECODE_ARGUMENTS + 2) {
            strcpy(NAME_BUFFER, argv[4]);
            strcat(NAME_BUFFER, ".txt");
            outputText = writeTextfile(NAME_BUFFER);
            if (outputText == NULL) {
                ERROR_RETURN = NAME_BUFFER;
                goto WRITE_ERROR;
            }
        }
        else {
            outputText = NULL;
        }

        int returnCode = RunDecodeText(inputEncodedText, inputEncodedTree, outputText);
        if (returnCode)
            printf("Error %d while decoding text\n", returnCode);
        fclose(inputEncodedText);
        fclose(inputEncodedTree);
        fclose(outputText);
        return returnCode;
    }
    else {
        PrintFullHelp();
    }

    NO_ERROR:
    return 0;

    READ_ERROR:
    printf("Cannot open: %s\n", ERROR_RETURN);
    PrintFullHelp();
    return FAILED_TO_READ_FILE_ERROR;

    WRITE_ERROR:
    printf("Cannot write: %s\n", ERROR_RETURN);
    PrintFullHelp();
    return FAILED_TO_WRITE_FILE_ERROR;
}