#include "includes.h"

void printUsage(const char *programName);
void sigintHandler(int sig);
int str2portNumber(char *portaServer);

int main(int argc, char **argv) {
    char *dataFilename = NULL;
    int disconnettiMinuti = -1;
    char *dizionarioFilename = NULL; // TODO - controllare thread zombie!!!
    int durata = 3; // minuti (default)
    // struct usata per contenere i nomi dei parametri per getopt()
    struct option long_options[] = {
        {"matrici", required_argument, NULL, 0},
        {"durata", required_argument, NULL, 1},
        {"seed", required_argument, NULL, 2},
        {"diz", required_argument, NULL, 3},
        {"disconnetti-dopo", required_argument, NULL, 4},
        {0, 0, 0, 0}
    };
    char *nomeServer = NULL;
    int opt = -1;
    int portaServer = -1;
    int rndSeed = -1;

    // disabilita i messaggi automatici di errore di getopt()
    opterr = 0;
    // scansiona i parametri opzionali
    while ((opt = getopt_long_only(argc, argv, "", long_options, NULL)) != -1) {
        switch (opt) {
            case 0:
                dataFilename = optarg;
                printf("--matrici %s\n", dataFilename);
                break;
            case 1:
                durata = atoi(optarg); // TODO - controllo valore durata!!!
                printf("--durata OK\n");
                break;
            case 2:
                printf("--seed OK\n");
                break;
            case 3:
                dizionarioFilename = optarg;
                printf("--diz OK\n");
                break;
            case 4:
                disconnettiMinuti = optarg;
                printf("--disconnetti-dopo OK\n");
                break;
            case '?':
            case ':':
            default:
                printf("qualche errore?\n");
                break;
        }
    }
    // controlla che il comando abbia i parametri obbligatori
    if (optind + 2 > argc) {
        perror("Errore: parametri obbligatori mancanti.\n");
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
    nomeServer = argv[optind];
    printf("nomeserver: %s\n", nomeServer);
    portaServer = str2portNumber(argv[++optind]);
    // esci se il numero porta non e' valido
    if (portaServer < 0) {
        perror("Errore: numero porta non valido. " 
        "Inserire valure tra 1025 e 65535.\n");
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("porta_server: %d\n", portaServer);

    // cattura il segnale SIGINT generato da CTRL-C
    if (signal(SIGINT, sigintHandler) == SIG_ERR) {
        perror("Errore fatale nello spegnimento del server." 
        "Interruzione immediata.\n");
        exit(EXIT_FAILURE);
    }

    // TODO - controllare il while (true) e initServer()
    /*
    while (true) {
        initServer(portaServer, NULL);
    }
    */
}

// stampa la corretta invocazione di `paroliere_srv`
void printUsage(const char *programName) {
    printf("Formato comando: %s nome_server porta_server [--matrici " "data_filename --durata durata_in_minuti] [--seed rnd_seed] [--diz " "dizionario] [--disconnetti-dopo tempo_in_minuti]\n", programName);
}

void sigintHandler(int sig) {
    printf("Ricevuto segnale %d - SIGINT - (CTRL-C)." 
    "Inizio spegnimento del server.\n", sig);
    currentState = EXIT;
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