#include "includes.h"

// ricerca dfs nella matrice
void dfs(Matrix *m, bool visited[MATRIX_SIZE][MATRIX_SIZE], char *word, int row, int col, int length, TrieNode *dizionario, TrieNode *paroleValide) {//, int *wordCount) {
    // caso base: parola non valida
    if (length < MATRIX_SIZE || !searchWord(dizionario, word))
        return;

    // se la parola non e' gia' stata trovata
    if (!searchWord(paroleValide, word))
        // aggiungi la parola in coda
        insertWord(paroleValide, word);

    // direzioni di movimento consentite
    int rowDir[] = {0, 1, 0, -1};
    int colDir[] = {1, 0, -1, 0};
    // visita le celle adiacenti
    for (int dir = 0; dir < 4; dir++) {
        int newRow = row + rowDir[dir];
        int newCol = col + colDir[dir];

        // controlla se sono dentro la matrice e non ho visitato la cella
        if (newRow >= 0 && newRow < MATRIX_SIZE && newCol >= 0 && newCol < MATRIX_SIZE && !visited[newRow][newCol]) {
            // marca la cella come visitata
            visited[newRow][newCol] = true;
            // aggiungi carattere alla parola costruita
            word[length] = m->matrix[newRow][newCol];
            word[length + 1] = '\0';
            // chiamata ricorsiva
            dfs(m, visited, word, newRow, newCol, length + 1, dizionario, paroleValide);
            // togli la spunta di visitata
            visited[newRow][newCol] = false;
        }
    }
}

void generateRandomMatrix(Matrix *m) {
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            m->matrix[i][j] = 'A' + (rand() % 26); // valore tra 'A' e 'Z'
}

// funzione ausiliaria: genera parole valide dalla matrice
void generateValidWords(Matrix *m, TrieNode *dizionario, TrieNode *paroleValide) {
    char word[MATRIX_SIZE + 1];
    bool visited[MATRIX_SIZE][MATRIX_SIZE] = {false};

    // avvia la generazione a partire da ogni cella
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            visited[row][col] = true;
            word[0] = m->matrix[row][col];
            word[1] = '\0';
            dfs(m, visited, word, row, col, 1, dizionario, paroleValide);
            visited[row][col] = false;
        }
    }
}

void loadMatrices(char *filename) {
    size_t len = 0;
    char *line = NULL;

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
        fprintf(stderr, "Lettura proprieta' file matrici non riuscita.\n"
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
    loadedMatrices = (Matrices *)malloc(sizeof(Matrices));
    loadedMatrices->firstMatrix = (Matrix *)malloc(sb.st_size * sizeof(int));
    loadedMatrices->size = 0;
    // controlla che la malloc() abbia avuto successo
    if (loadedMatrices->firstMatrix == NULL) {
        fprintf(stderr, "Errore in allocazione di memoria.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    // leggi riga per riga con getline()
    while (getline(&line, &len, file) != -1) {
        // linesCounter tiene traccia del numero di matrice da salvare
        //loadedMatrices->size += processLine(line, &loadedMatrices[loadedMatrices->size], EXPECTED_TOKENS);
        processLine(line, loadedMatrices, EXPECTED_TOKENS);
    }
    free(line); // libera memoria automaticamente allocata da getline()
    fclose(file);
    printf("\nMatrici caricate.\n");
}

void loadNewMatrix(Matrix *m, char *dataFilename) {
    // stato interno della funzione
    static int curr = 0;
    if (dataFilename == NULL)
        generateRandomMatrix(currentMatrix);
    else if (curr < loadedMatrices->size)
        currentMatrix = loadedMatrices->firstMatrix + curr++;
    else { // ricomincia dalla prima matrice
        currentMatrix = loadedMatrices->firstMatrix;
        curr = 1; // spostati gia' sulla prossima matrice
    }
}

void printMatrix(Matrix *m) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++)
            printf("%c ", m->matrix[i][j]);
        printf("\n");
    }
}

void processLine(char *line, Matrices *loadedMatrices, int expectedTokens) {
    const char *delim = " \n";
    char *token;
    int col = 0, row = 0, tokenCounter = 0;
    Matrix *m = loadedMatrices->firstMatrix + loadedMatrices->size;

    printf("%p\n", (void *)&m->matrix[0][0]);
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
    printMatrix(m);
    // TODO - test
    //char *w = "YQTDUDT";
    //printf("%s: %d\n", w, findWord(m, w));
    // gestisci i valori di ritorno
    switch (tokenCounter) {
        case EXPECTED_TOKENS:
            ++loadedMatrices->size;
        case 0:
            return;
        default:
            fprintf(stderr, "File matrici malformato.\n"
            "Non contiene esattamente %d caratteri.\n", expectedTokens);
            // TODO - genera invece parole casuali
            exit(EXIT_FAILURE);
    }
}