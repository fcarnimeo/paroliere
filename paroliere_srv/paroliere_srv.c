#include "includes.h"

void printUsage(const char *programName);

int main(int argc, char **argv) {
    const char *nomeServer = argv[1];
    const int portaServer = atoi(argv[2]);
    char *dataFilename = NULL; // nome del file dal quale caricare le matrici
    int durataInMinuti = 3; // durata del gioco in minuti
    int rndSeed = 0; // seed da usare per la generazione numeri pseudocasuali
    char *dizionarioFilename = NULL; // dizionario per controllare parole

    // controlla che il comando sia stato lanciato correttamente
    if (argc < 3) {
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
    // cattura il segnale SIGINT generato da CTRL-D
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        perror("Errore fatale nello spegnimento del server.\ 
        Interruzione immediata.\n");
        exit(EXIT_FAILURE);
    }

    // TODO - controllare il while (true) e initServer()
    while (true) {
        // TODO - numero porta da CLI
        initServer(12345, NULL);
    }
}

void printUsage(const char *programName) {
    printf("Comando: %s nome_server porta_server [--matrici data_filename]\ [--durata durata_in_minuti] [--seed rnd_seed] [--diz dizionario]\ [--disconnetti-dopo tempo in minuti]\n", programName);
}