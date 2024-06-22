#include "includes.h"

void printUsage(const char *programName);

int main(int argc, char **argv) {
    char *dataFilename, *dizionarioFilename, *nomeServer;
    int durata, opt, optIndex, portaServer, rndSeed;

    // controlla che il comando sia stato lanciato correttamente
    if (argc < 3) {
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
    else {
        // struct usata per contenere i nomi dei parametri per getopt
        struct option long_options[] = {
            {"matrici", required_argument, 0, 0},
            {"durata", required_argument, 0, 0},
            {"seed", required_argument, 0, 0},
            {"diz", required_argument, 0, 0},
            {"disconnetti-dopo", required_argument, 0, 0},
            {0, 0, 0, 0}
        };
        nomeServer = argv[1];
        portaServer = str2portNumber(argv[2]);
        // esci se il numero porta non e' valido
        if (portaServer < 0) {
            printf("Errore: numero porta non valido.\ 
            Inserire valure tra 1025 e 65535.\n");
            printUsage(argv[0]);
            exit(EXIT_FAILURE);
        }
        // scansiona i parametri opzionali
        while ((opt = getopt_long_only(argc, argv, "", long_options,
        &optIndex)) != -1) {
        }  

        
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

// converti una stringa in numero porta valido per il server [1025-65535]
// restituisci -1 in caso di insuccesso
int str2portNumber(char *portaServer) {
    // controlla se il valore inserito e' troppo lungo
    if (strlen(portaServer) > 5)
        return -1;
    // atoi() non e' al 100% sicuro, ma grazie ai controlli, sono certo che
    // il valore di ritorno e' valido
    int p = atoi(portaServer);
    // controlla se il numero porta e' nell'intervallo valido
    if (p < 1025 || p > 65535)
        return -1;
    // se sono arrivato qui, il numero porta e' corretto
    return p;
}

// stampa la corretta invocazione di `paroliere_srv`
void printUsage(const char *programName) {
    printf("Comando: %s nome_server porta_server [--matrici data_filename]\ [--durata durata_in_minuti] [--seed rnd_seed] [--diz dizionario]\ [--disconnetti-dopo tempo_in_minuti]\n", programName);
}