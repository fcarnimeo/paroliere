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
    const int maxTokenLength = 3; // include il caso 'Qu' e lo \0 a fine stringa

    // apri il file in lettura
    FILE *file = fopen(filename, "r");
    // controlla che il file e' aperto correttamente
    if (file == NULL) {
        fprintf(stderr, "Apertura del file \"%s\" non riuscita.\n"
        "Genero parole casuali.\n", filename);
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }
    // leggo riga per riga con getline()
    while ((bytesRead = getline(&line, &len, file)) != -1) {
        processLine(line, expectedTokens);
    }
    free(line); // libero memoria automaticamente allocata da getline()
    fclose(file);
    printf("\nMatrici caricate.\n");
}

static void processLine(char *line, int expectedTokens) {
    const char *delim = " \n";
    char *token;
    int tokenCounter = 0; // contatore token processati per linea

    // processa il primo token
    token = strtok(line, delim);
    // scorri tutti i token
    while (token != NULL) {
        // int c serve come variabile di appoggio per il carattere papabile
        int c = toupper(token[0]);
        // caso carattere singolo valido
        if (token[1] == '\0' && c >= 'A' && c <= 'Z' || token[2] == '\0' && token[1] == 'U' || token[2] == '\0' && token[1] == 'u') {
            // TODO - inserisci il carattere nella struttura dati
        }
        else {
            fprintf(stderr, "File matrici malformato.\n"
            "Ammessi solo caratteri dalla A alla Z e la combinazione 'QU'.\n", token);
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
}