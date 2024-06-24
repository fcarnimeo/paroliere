#ifndef MATRIX_H
#define MATRIX_H

int findWord(Matrix *m, char *word);
bool foundChr(Matrix *m, char *word, int row, int col, int chrCount, bool visited[MATRIX_SIZE][MATRIX_SIZE]);

#endif // MATRIX_H