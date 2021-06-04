# Huffman
Implementing Huffman Trees to encode/decode (ASCII) text in pure C!<br>

This is mostly just me practicing coding various different data structures in C! :)<br>
This was really useful to learn how to think about bit operations too :D

# Goal
The main goal of this project was implementing the Huffman stuff while keeping file sizes as small as possible.<br>
The tree file (.huftree) is usually around 100 bytes and rarely bigger than 200 bytes, it mainly depends on how many unique characters are there.<br>
The encoded text file (.huf) is around 70% to 55% the initial size of the original text (it works better for bigger files).<br>

I left the tree file separate from the encoded text file because then it acts like a sort of (very unsafe) encryption key :><br>

## TIL
C doesn't support read/write to files 1 bit at a time. Because of that, bits are batched into bytes in the binary files.
This isn't really a problem for encoding the text, but decoding requires a small trick for the cases where the number of bits isn't
a multiple of 8. To deal with this, every .huf file contains a single byte at the start that indicates how many bits are supposed to be ignored in
the last byte of the file.