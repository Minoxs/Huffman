//
// Author: Mino
// Github: https://github.com/minoxs
//

#ifndef TEXT_COUNTER_H
#define TEXT_COUNTER_H

/**
 * Counted Letter struct
 */
typedef struct LetterCount_st {
    char key;
    int count;
} LetterCount;

/**
 * Counted letter table
 */
typedef struct CountedLetters_st {
    int arrSize;
    LetterCount* letters; // Array of arrSize
} CountedLetters;

CountedLetters* parseText(FILE *text);

#endif //TEXT_COUNTER_H
