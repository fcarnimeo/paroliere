#include "includes.h"

void initServer(int port, char *filename) {
    printf("Inizio avvio server.\n");
    loadMatrices(filename);
    //initSocket(port);
}

// TODO - implementare per bene. Dopo che il socket e' partito,
// come accetto le connessioni dei client?
void initSocket(int port) {
    // crea il socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    // controlla errori in fase di creazione del socket
    if (server == -1) {
        perror("Errore nella creazione del socket.");
        exit(EXIT_FAILURE);
    }
    // imposta i parametri di rete per il server
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // accoppia il socket con indirizzo e porta
    if (bind(server, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Errore in fase di accoppiamento del socket.");
        exit(EXIT_FAILURE);
    }
    // mette il server in ascolto
    if (listen(server, 10) == -1) {
        perror("Errore in fase di ascolto del server.");
        exit(EXIT_FAILURE);
    }
    printf("Server in ascolto sulla porta %d.\n", port);
}

void loadMatrices(char *filename) {
    ssize_t bytesRead;
    const int expectedTokens = 16; // numero di token per ogni linea (matrice)
    size_t len = 0;
    char *line = NULL;
    int linesCounter = 0;
    const int maxTokenLength = 3; // include il caso 'Qu' e lo \0 a fine stringa

    // apri il file descriptor
    int fd = open(filename, O_RDONLY);
    // controlla errori
    if (fd == -1) {
        fprintf(stderr, "Apertura del file matrici non riuscita.\n"
        "Genero parole casuali.\n");
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        fprintf(stderr, "Reperimento proprieta' file matrici non riuscito.\n"
        "Genero parole casuali.\n");
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }

    // apri il file in lettura
    FILE *file = fdopen(fd, "r");
    // controlla che il file e' aperto correttamente
    if (file == NULL) {
        fprintf(stderr, "Apertura del file matrici non riuscita.\n"
        "Genero parole casuali.\n");
        close(fd);
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }
    // alloca memoria per contenere tutte le strutture dati
    Matrix *m_ptr = (Matrix *)malloc(sb.st_size);
    // controlla che la malloc() abbia avuto successo
    if (m_ptr == NULL) {
        fprintf(stderr, "Errore in allocazione di memoria.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    // leggi riga per riga con getline()
    while ((bytesRead = getline(&line, &len, file)) != -1) {
        // linesCounter tiene traccia del numero di matrice da salvare
        linesCounter += processLine(line, &m_ptr[linesCounter], expectedTokens);
    }
    free(line); // libera memoria automaticamente allocata da getline()
    fclose(file);
    printf("\nMatrici caricate.\n");
}

static int processLine(char *line, Matrix *m, int expectedTokens) {
    const char *delim = " \n";
    char *token;
    int tokenCounter = 0; // contatore token processati per linea

    // processa il primo token
    token = strtok(line, delim);
    printf("Prima linea: %s\nPrimo token: %s\n", line, token);
    // scorri tutti i token
    while (token != NULL) {
        // int c serve come variabile di appoggio per il carattere papabile
        int c = toupper(token[0]);
        // caso carattere singolo valido
        if (token[1] == '\0' && c >= 'A' && c <= 'Z' || token[2] == '\0' && token[1] == 'U' || token[2] == '\0' && token[1] == 'u') {
            tokenCounter++;
        }
        else {
            fprintf(stderr, "File matrici malformato.\n" 
            "Ammessi solo caratteri dalla A alla Z e la combinazione 'QU'.\n");
            // TODO - genera invece parole casuali
            exit(EXIT_FAILURE);
        }
        // individua il token successivo
        token = strtok(NULL, delim);
    }
    // controlla che la linea processata abbia 16 caratteri
    if (tokenCounter != expectedTokens) {
        fprintf(stderr, "File matrici malformato.\n"
        "Non contiene esattamente %d caratteri.\n", expectedTokens);
        // TODO - genera invece parole casuali
        exit(EXIT_FAILURE);
    }
    // restituisci 1 se ha processato la linea, altrimenti 0
    return tokenCounter ? 1 : 0;
}