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

typedef enum {
    INIT,
    PLAYING,
    PAUSED,
    ERROR,
    EXIT   
} ServerState;

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

#endif // STRUCT_H