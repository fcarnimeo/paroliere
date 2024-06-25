#ifndef STRUCT_H
#define STRUCT_H

#define MATRIX_SIZE 4

typedef struct {
    char **words;
    size_t size;
    size_t maxWordLength;
} Dictionary;

typedef struct {
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
} Matrix;

typedef enum {
    INIT,
    PLAY,
    PAUSE,
    ERROR,
    EXIT   
} ServerState;

#endif // STRUCT_H