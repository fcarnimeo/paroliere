#ifndef INIT_H
#define INIT_H

#include "struct.h"

void initMatrices(void);
void initServer(char *nomeServer, int portaServer, char *dataFilename, int durata, unsigned int rndSeed, char *dizionarioFilaname, int disconnettiMinuti);
void initSocket(char *nomeServer, int portaServer);

#endif // INIT_H