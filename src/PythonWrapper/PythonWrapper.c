//
// Author: Mino
// Github: https://github.com/minoxs
//

// THIS WAS STOLEN FROM RealPython's WEBSITE -- THIS IS JUST AN EXAMPLE OF HOW CPython wrapper works
// Slightly modified by me so it is compiled with CMake rather than distutils
// I will use this example to create a CPython wrapper for this library im making :)

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#define DLLEXPORT __declspec(dllexport)

static PyObject *method_fputs(PyObject *self, PyObject *args) {
    char *str, *filename = NULL;

    int bytes_copied = -1;
    /* Parse arguments */
    if(!PyArg_ParseTuple(args, "ss", &str, &filename)) {
        return NULL;
    }

    FILE *fp = fopen(filename, "w");
    bytes_copied = fputs(str, fp);
    fclose(fp);
    return PyLong_FromLong(bytes_copied);
}

static PyMethodDef FputsMethods[] = {
        {"fputs", method_fputs, METH_VARARGS, "Python interface for fputs C library function"},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fputsmodule = {
        PyModuleDef_HEAD_INIT,
        "fputs_teste",
        "Python interface for the fputs C library function",
        -1,
        FputsMethods
};

DLLEXPORT PyMODINIT_FUNC PyInit_fputs_teste(void) {
    return PyModule_Create(&fputsmodule);
}