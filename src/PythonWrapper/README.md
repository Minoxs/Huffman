# Building
Build the huffman_c target of the cmake.   
Must set `PYHTON_INCLUDE_DIRS` and `PYTHON_LIBRARIES` environment variables.   
`PYHTON_INCLUDE_DIRS` is the `include/` directory in your python installation folder.   
`PYTHON_LIBRARIES` is the `python*.dll` files that should be inside your python installation folder.

For me, I can only get the library to build using mingw32 compiler. Don't ask me why.   
In any case, if you can't get it to build, I left a pre-compiled `huffman_c.pyd` inside the `tests` folder.

# Using
Just import the file and use the exported functions.

The exported functions are:
- `EncodeText(inputFilepath: string, outputEncodedTextFilpath: string, outputEncodedTreeFilepath: string)`
- `DecodeText(inputEncodedTextFilepath: string, inputEncodedTreeFilepath: string, outputEncodedTreeFilepath: string)`

On success, these functions will return 0.   
If there are errors, they will return tuples so you can know what went wrong.   
The first element is the error code, whose meaning can be checked in `ErrorCodes.h`.   
In case of read/write error, the second element will tell you which argument is the culprit, indexed from 0.
