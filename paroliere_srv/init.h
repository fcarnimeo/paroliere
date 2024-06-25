#ifndef INIT_H
#define INIT_H

#include "struct.h"

void initServer(char *nomeServer, int portaServer, char *dataFilename, int durata, unsigned int rndSeed, char *dizionarioFilaname, int disconnettiMinuti);
void initSocket(int port);

#endif // INIT_H