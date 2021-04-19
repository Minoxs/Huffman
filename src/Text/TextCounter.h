//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef HAMMING_TEXTCOUNTER_H
#define HAMMING_TEXTCOUNTER_H

/**
 * Counted Letter Table struct
 * When used as an array, 0th element must be key = '\0' and count = size of array
 */
typedef struct CLT_st {
    char key;
    int count;
} CLT;

CLT* parseText(FILE *text);

#endif //HAMMING_TEXTCOUNTER_H
