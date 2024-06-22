#include "includes.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Comando: %s nome_server porta_server [--matrici data_filename]\ [--durata durata_in_minuti] [--seed rnd_seed] [--diz dizionario]\ [--disconnetti-dopo tempo in minuti]\n", argv[0]);
    // catturo il segnale SIGINT generato da CTRL-D
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        perror("Errore fatale nello spegnimento del server. 
        Interruzione immediata.\n");
        exit(EXIT_FAILURE);
    }

    // TODO - controllare il while (true) e initServer()
    while (true) {
        // TODO - numero porta da CLI
        initServer(12345, NULL);
    }
}