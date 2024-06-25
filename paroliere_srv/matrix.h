#ifndef MATRIX_H
#define MATRIX_H

void dfs(Matrix *m, bool visited[MATRIX_SIZE][MATRIX_SIZE], char *word, int row, int col, int charCount, Dictionary *d, Dictionary *validWords); {//, int *wordCount) {
int findWord(Matrix *m, char *word);
bool foundChr(Matrix *m, char *word, int row, int col, int chrCount, bool visited[MATRIX_SIZE][MATRIX_SIZE]);
void generateRandomMatrix(Matrix *m);
void generateValidWords(Matrix *m, Dictionary *d, Dictionary *validWords);

#endif // MATRIX_H