#ifndef INIT_H
#define INIT_H

#define MATRIX_SIZE 4

typedef struct {
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
} Matrix;

void initServer(int nomeServer, int portaServer, char *dataFilename, int durata, unsigned int rndSeed, char *dizionarioFilaname, int disconnettiMinuti);
void initSocket(int port);
void loadMatrices(char *filename);
int processLine(char *line, Matrix *m, int expectedTokens);

#endif // INIT_H