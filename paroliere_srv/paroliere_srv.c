#include "includes.h"

void printUsage(const char *programName);

int main(int argc, char **argv) {
    char *dataFilename, *dizionarioFilename, *nomeServer;
    int durata, portaServer, rndSeed;

    // controlla che il comando sia stato lanciato correttamente
    if (argc < 3) {
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
        nomeServer = argv[1];
        portaServer = atoi(argv[2]);

    }

    // cattura il segnale SIGINT generato da CTRL-D
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        perror("Errore fatale nello spegnimento del server.\ 
        Interruzione immediata.\n");
        exit(EXIT_FAILURE);
    }

    // TODO - controllare il while (true) e initServer()
    while (true) {
        initServer(portaServer, NULL);
    }
}

void printUsage(const char *programName) {
    printf("Comando: %s nome_server porta_server [--matrici data_filename]\ [--durata durata_in_minuti] [--seed rnd_seed] [--diz dizionario]\ [--disconnetti-dopo tempo_in_minuti]\n", programName);
}