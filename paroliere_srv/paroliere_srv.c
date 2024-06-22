#include "includes.h"

int main(void) {
    // catturo il segnale SIGINT generato da CTRL-D
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        perror("Errore fatale nello spegnimento del server. Interruzione immediata.\n");
        exit(EXIT_FAILURE);
    }

    // TODO - controllare il while (true) e initServer()
    while (true) {
        // TODO - numero porta da CLI
        initServer(12345, NULL);
    }
}