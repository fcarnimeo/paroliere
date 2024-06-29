#ifndef STRUCT_H
#define STRUCT_H

#define ALPHABET_SIZE 26
#define MATRIX_SIZE 4

typedef struct {
    char **words;
    size_t size;
    size_t maxWordLength;
} Dictionary;

typedef struct {
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
} Matrix;

typedef struct {
    Matrix *firstMatrix;
    int size;
} Matrices;

typedef enum {
    INIT,
    PLAYING,
    PAUSING,
    PAUSED,
    ERROR,
    SHUTDOWN
} ServerState;

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

#endif // STRUCT_H