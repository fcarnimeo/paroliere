#ifndef MATRIX_H
#define MATRIX_H

#include "struct.h"
#include "trie.h"

void dfs(Matrix *m, bool visited[MATRIX_SIZE][MATRIX_SIZE], char *word, int row, int col, int charCount, TrieNode *dizionario, TrieNode *paroleValide);
//int findWord(Matrix *m, char *word);
//bool foundChr(Matrix *m, char *word, int row, int col, int chrCount, bool visited[MATRIX_SIZE][MATRIX_SIZE]);
void generateRandomMatrix(Matrix *m);
void generateValidWords(Matrix *m, TrieNode *dizionario, TrieNode *paroleValide);
void loadMatrices(char *filename);
void loadNewMatrix(Matrix *m, char *dataFilename);
void printMatrix(Matrix *m);
void processLine(char *line, Matrices *matrices, int expectedTokens);

#endif // MATRIX_H