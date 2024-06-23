#ifndef INIT_H
#define INIT_H

#define MATRIX_SIZE 4

typedef struct {
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
} Matrix;

void initServer(int port, char *filename);
void initSocket(int port);
void loadMatrices(char *filename);
int processLine(char *line, Matrix *m, int expectedTokens);

#endif // INIT_H