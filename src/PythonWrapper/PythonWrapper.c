//
// Author: Mino
// Github: https://github.com/minoxs
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include "../FileHandler/FileHandler.h"
#define DLLEXPORT __declspec(dllexport)

static PyObject* EncodeText(PyObject* self, PyObject* args) {
    char *textInput = NULL, *encodedTextOutput = NULL, *encodedTreeOutput = NULL;

    if (!PyArg_ParseTuple(args, "sss", &textInput, &encodedTextOutput, &encodedTreeOutput)) {
        return PyTuple_Pack(2, PyLong_FromLong(FAILED_TO_PARSE_ARGS), PyLong_FromLong(0));
    }

    FILE* inputFile = readTextfile(textInput);
    if (inputFile == NULL) {
        return PyTuple_Pack(2, PyLong_FromLong(FAILED_TO_READ_FILE_ERROR), PyLong_FromLong(0));
    }
    FILE* textOutputFile = writeBinaryFile(encodedTextOutput);
    if (textOutputFile == NULL) {
        fclose(inputFile);
        return PyTuple_Pack(2, PyLong_FromLong(FAILED_TO_WRITE_FILE_ERROR), PyLong_FromLong(1));
    }
    FILE* treeOutputFile = writeBinaryFile(encodedTreeOutput);
    if (treeOutputFile == NULL) {
        fclose(inputFile);
        fclose(textOutputFile);
        return PyTuple_Pack(2, PyLong_FromLong(FAILED_TO_WRITE_FILE_ERROR), PyLong_FromLong(2));
    }

    int returnCode = RunEncodeText(inputFile, textOutputFile, treeOutputFile);

    fclose(inputFile);
    fclose(textOutputFile);
    fclose(treeOutputFile);

    return PyLong_FromLong(returnCode);
}

static PyObject* DecodeText(PyObject* self, PyObject* args) {
    char *output = NULL, *encodedTextInput = NULL, *encodedTreeInput = NULL;

    if (!PyArg_ParseTuple(args, "sss", &encodedTextInput, &encodedTreeInput, &output)) {
        return PyTuple_Pack(2, PyLong_FromLong(FAILED_TO_PARSE_ARGS), PyLong_FromLong(0));
    }

    FILE* encodedTextFile = readBinaryFile(encodedTextInput);
    if (encodedTextFile == NULL) {
        return PyTuple_Pack(2, PyLong_FromLong(FAILED_TO_READ_FILE_ERROR), PyLong_FromLong(0));
    }
    FILE* encodedTreeFile = readBinaryFile(encodedTreeInput);
    if (encodedTreeFile == NULL) {
        fclose(encodedTextFile);
        return PyTuple_Pack(2, PyLong_FromLong(FAILED_TO_READ_FILE_ERROR), PyLong_FromLong(1));
    }
    FILE* outputFile = writeTextfile(output);
    if (outputFile == NULL) {
        fclose(encodedTextFile);
        fclose(encodedTreeFile);
        return PyTuple_Pack(2, PyLong_FromLong(FAILED_TO_WRITE_FILE_ERROR), PyLong_FromLong(2));
    }

    int returnCode = RunDecodeText(encodedTextFile, encodedTreeFile, outputFile);

    fclose(encodedTextFile);
    fclose(encodedTreeFile);
    fclose(outputFile);

    return PyLong_FromLong(returnCode);
}

static PyMethodDef HuffmanMethods[] = {
        {"EncodeText", EncodeText, METH_VARARGS, "Encode text file"},
        {"DecodeText", DecodeText, METH_VARARGS, "Decode text file"},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef HuffmanModule = {
        PyModuleDef_HEAD_INIT,
        "HuffmanEncoding",
        "Wrapper for the Huffman text encoding made in C",
        -1,
        HuffmanMethods
};

DLLEXPORT PyMODINIT_FUNC PyInit_huffman_c(void) {
    return PyModule_Create(&HuffmanModule);
}