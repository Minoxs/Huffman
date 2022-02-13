#
# Author: Mino
# Github: https://github.com/minoxs
#
cmake_minimum_required(VERSION 3.17)
project(Huffman C)
set(CMAKE_C_STANDARD 99)

SET(SOURCE_FILES
        src/DataStructs/Huffman/HuffmanTree.c
        src/DataStructs/Huffman/HuffmanTree.h
        src/Text/TextCounter.c
        src/Text/TextCounter.h
        src/DataStructs/AVL/AvlTree.c
        src/DataStructs/AVL/AvlTree.h
        src/FileHandler/FileHandler.c
        src/FileHandler/FileHandler.h
        src/Text/HuffmanEncoding.c
        src/Text/HuffmanEncoding.h
        src/DataStructs/ArrayList/ArrayList.c
        src/DataStructs/ArrayList/ArrayList.h
        src/DataStructs/Dictionary/Key/DictKey.c
        src/DataStructs/Dictionary/Key/DictKey.h
        src/DataStructs/Dictionary/Value/DictValue.c
        src/DataStructs/Dictionary/Value/DictValue.h
        src/DataStructs/Dictionary/Dictionary.c
        src/DataStructs/Dictionary/Dictionary.h
        src/ErrorCodes.h)

#Main C
add_executable(Huffman ${SOURCE_FILES} src/ConsoleApplication/ConsoleApplication.c)

#Tests executable
add_executable(Huffman_Tests ${SOURCE_FILES} tests/TestMain.c)

#Python Wrapper Stuff
#This will be left just as an example for now
set(PYTHON_WRAPPER_LIB huffman_c) # Name of Target

# Finds Python stuff
find_package(PythonInterp 3.8 REQUIRED)
find_package(PythonLibs 3.8 REQUIRED)

# Include "includes" python folder (Where Python.h is located)
include_directories($ENV{PYTHON_INCLUDE_DIRS})

# Link python libraries (Either python3x.dll or python3x.lib, where x is python version)
# Python3.dll/Python3.lib is required if building with "Release" options
# To find the correct file paths, look inside python installation folder -- usually in %appdata%/../local/programs/Python
link_libraries($ENV{PYTHON_LIBRARIES})

# Command to create Wrapper library
add_library(${PYTHON_WRAPPER_LIB} SHARED ${SOURCE_FILES} src/PythonWrapper/PythonWrapper.c)

# Sets output properties
set_target_properties(
        ${PYTHON_WRAPPER_LIB} # Target Name
        PROPERTIES
        PREFIX ""
        OUTPUT_NAME "${PYTHON_WRAPPER_LIB}" # Output file must have the same name as the init function if using .pyd
        SUFFIX ".pyd" # .dll does work, however, .pyd is much better but the latter requires using the CPython API
        LINKER_LANGUAGE C
)

# (Optional) Copies the library file to /venv/ folder
add_custom_command(TARGET ${PYTHON_WRAPPER_LIB} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
        "$<TARGET_FILE:${PYTHON_WRAPPER_LIB}>"
        "${CMAKE_SOURCE_DIR}/venv/DLLs/$<TARGET_FILE_NAME:${PYTHON_WRAPPER_LIB}>"
        COMMENT "Copying to output directory"
)
