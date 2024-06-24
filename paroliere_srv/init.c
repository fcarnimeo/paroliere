#include "includes.h"

#define EXPECTED_TOKENS 16

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
    size_t len = 0;
    char *line = NULL;
    int linesCounter = 0;

    // apri il file descriptor
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Apertura del file matrici non riuscita.\n"
        "Genero parole casuali.\n");
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }
    // ottieni proprieta' file
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        fprintf(stderr, "Reperimento proprieta' file matrici non riuscito.\n"
        "Genero parole casuali.\n");
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }
    // apri il file in lettura
    FILE *file = fdopen(fd, "r");
    if (file == NULL) {
        fprintf(stderr, "Apertura del file matrici non riuscita.\n"
        "Genero parole casuali.\n");
        close(fd);
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }
    // alloca memoria per contenere tutte le strutture dati
    Matrix *m_ptr = (Matrix *)malloc(sb.st_size * sizeof(int));
    // controlla che la malloc() abbia avuto successo
    if (m_ptr == NULL) {
        fprintf(stderr, "Errore in allocazione di memoria.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    // leggi riga per riga con getline()
    while ((bytesRead = getline(&line, &len, file)) != -1) {
        // linesCounter tiene traccia del numero di matrice da salvare
        linesCounter += processLine(line, &m_ptr[linesCounter], EXPECTED_TOKENS);
    }
    free(line); // libera memoria automaticamente allocata da getline()
    fclose(file);
    printf("\nMatrici caricate.\n");
}

int processLine(char *line, Matrix *m, int expectedTokens) {
    const char *delim = " \n";
    char *token;
    int col = 0, row = 0, tokenCounter = 0;

    printf("%p\n", &m->matrix[0][0]);
    // processa il primo token
    token = strtok(line, delim);
    // scorri tutti i token
    while (token != NULL) {
        // converti il carattere in lettera maiuscola
        int c = toupper(token[0]);
        // caso carattere singolo valido
        if ((token[1] == '\0' && c >= 'A' && c <= 'Z') || 
            (token[2] == '\0' && toupper(token[1]) == 'U')) {
            m->matrix[row][col++] = c;
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
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%c ", m->matrix[i][j]);
        }
        printf("\n");
    }
    // TODO - test
    char *w = "YQTDUDT";
    printf("%s: %d\n", w, findWord(m, w));
    // gestisci i valori di ritorno
    switch (tokenCounter) {
        case EXPECTED_TOKENS:
            return 1;
        case 0:
            return 0;
        default:
            fprintf(stderr, "File matrici malformato.\n"
            "Non contiene esattamente %d caratteri.\n", expectedTokens);
            // TODO - genera invece parole casuali
            exit(EXIT_FAILURE);
    }
}