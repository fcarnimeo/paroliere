#ifndef INIT_H
#define INIT_H

#include "struct.h"

void initServer(char *nomeServer, int portaServer, char *dataFilename, int durata, unsigned int rndSeed, char *dizionarioFilaname, int disconnettiMinuti);
void initSocket(int port);
void loadMatrices(char *filename);
int processLine(char *line, Matrix *m, int expectedTokens);

#endif // INIT_H