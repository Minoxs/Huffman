import huffman_c

if __name__ == "__main__":
    print("\n")
    err = huffman_c.EncodeText("Test.txt", "EncodePy.huf", "EncodeTreePy.huftree")
    if err:
        print(err)
    else:
        print("Encoded successfully!")
    err = huffman_c.DecodeText("EncodePy.huf", "EncodeTreePy.huftree", "TestDecoded.txt")
    if err:
        print(err)
    else:
        print("Decoded successfully!")

