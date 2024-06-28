#include "includes.h"

// variabili globali
Matrix *currentMatrix = NULL;
Dictionary *dictionary = NULL;
TrieNode *dizionario = NULL;
int durata;
pthread_cond_t matrix_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t matrix_mutex = PTHREAD_MUTEX_INITIALIZER;
TrieNode *paroleValide = NULL;
unsigned int rndSeed = 0;
volatile _Atomic ServerState serverState;
pthread_t serverStateManager_thread;
volatile sig_atomic_t shuttingDown;
pthread_cond_t state_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t state_mutex = PTHREAD_MUTEX_INITIALIZER;

// prototipi di funzioni
void printUsage(const char *programName);
void sigintHandler(int sig);
int str2portNumber(char *portaServer);

int main(int argc, char **argv) {
    shuttingDown = 0;
    serverState = INIT; // server appena avviato
    char *dataFilename = NULL;
    int disconnettiMinuti = -1;
    char *dizionarioFilename = NULL; // TODO - controllare thread zombie!!!
    durata = 3; // minuti (default)
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

    // cattura il segnale SIGINT generato da CTRL-C
    signal(SIGINT, sigintHandler);

    // disabilita i messaggi automatici di errore di getopt()
    opterr = 0;
    // scansiona i parametri opzionali
    while ((opt = getopt_long_only(argc, argv, "", long_options, NULL)) != -1) {
        switch (opt) {
            case 0:
                dataFilename = optarg;
                break;
            case 1:
                durata = atoi(optarg); // TODO - controllo valore durata!!!
                break;
            case 2:
                rndSeed = atoi(optarg); // TODO - controllo atoi()
                break;
            case 3:
                dizionarioFilename = optarg;
                break;
            case 4:
                disconnettiMinuti = atoi(optarg); // TODO - atoi crea zombie?!?
                break;
            // controlla se sono stati digitati parametri inesistenti
            case '?':
            case ':':
            default:
                printUsage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    // controlla che il comando abbia il giusto numero di parametri obbligatori
    if (argc != optind + 2) {
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }
    nomeServer = argv[optind];
    portaServer = str2portNumber(argv[++optind]);
    // esci se il numero porta non e' valido
    if (portaServer < 0) {
        fprintf(stderr, "Errore: numero porta non valido. " 
        "Inserire valure tra 1025 e 65535.\n");
        printUsage(argv[0]);
        exit(EXIT_FAILURE);
    }

    // inizializza il server
    initServer(nomeServer, portaServer, dataFilename, durata, rndSeed, dizionarioFilename, disconnettiMinuti);

    // spegni il server se arriva CTRL-C
    while (serverState != SHUTDOWN); // attendi finche' non arriva lo stato SHUTDOWN
    //while (!shuttingDown);
    // avvia lo shutdown
    shutdownServer();

    // TODO - implementare shutdown() con un migliore sistema gestione messaggi uscita
    exit(EXIT_SUCCESS);
}

// stampa la corretta invocazione di `paroliere_srv`
void printUsage(const char *programName) {
    printf("Formato comando: %s nome_server porta_server [--matrici " "data_filename --durata durata_in_minuti] [--seed rnd_seed] [--diz " "dizionario] [--disconnetti-dopo tempo_in_minuti]\n", programName);
}

// TODO - se ci sono bug strani, usa volatile sig_atomic_t shutdown_flat
void sigintHandler(int sig) {
    printf("\nRicevuto segnale %d - SIGINT - (CTRL-C).\n"
    "Inizio spegnimento del server.\n", sig);
    atomic_store(&serverState, SHUTDOWN);
    pthread_cond_broadcast(&state_cond); // sveglia tutti i thread in attesa
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