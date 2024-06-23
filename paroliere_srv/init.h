#ifndef INIT_H
#define INIT_H

void initServer(int port, char *filename);
void initSocket(int port);
void loadMatrices(char *filename);
static void processLine(char *line);

#endif // INIT_H