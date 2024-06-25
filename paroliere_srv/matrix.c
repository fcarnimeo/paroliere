#include "includes.h"

// ricerca dfs nella matrice
void dfs(Matrix *m, bool visited[MATRIX_SIZE][MATRIX_SIZE], char *word, int row, int col, int length, TrieNode *dizionario, TrieNode *paroleValide) {//, int *wordCount) {
    if (length >= MATRIX_SIZE && searchWord(dizionario, word)) {
        // se la parola non e' gia' stata trovata
        if (!searchWord(paroleValide, word)) {
            // aggiungi la parola in coda
            insertWord(paroleValide, word);
            //strcpy(validWords->words[validWords->size], word);
            // aumenta dimensione dizionario parole valide
            //(validWords->size)++;
        }
    }

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
    currentMatrix = (Matrix *)malloc(sb.st_size * sizeof(int));
    // controlla che la malloc() abbia avuto successo
    if (currentMatrix == NULL) {
        fprintf(stderr, "Errore in allocazione di memoria.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    // leggi riga per riga con getline()
    while (getline(&line, &len, file) != -1) {
        // linesCounter tiene traccia del numero di matrice da salvare
        linesCounter += processLine(line, &currentMatrix[linesCounter], EXPECTED_TOKENS);
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
    //char *w = "YQTDUDT";
    //printf("%s: %d\n", w, findWord(m, w));
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

/*
// il valore di ritorno e' il punteggio della parola
int findWord(Matrix *m, char *word) {
    // lunghezza minima 4 lettere
    if (strlen(word) < 4)
        return 0;
    // inizializza matrice lettere visitate
    bool visited[MATRIX_SIZE][MATRIX_SIZE] = {false};
    // cerca parola a partire da ogni casella
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (foundChr(m, word, i, j, 0, visited)) {
                return strlen(word); // punteggio parola
            }
        }
    }
    return 0; // parola non trovata
}
*/

/*
// funzione ricorsiva DFS per trovare corrispondenze tra caratteri
bool foundChr(Matrix *m, char *word, int row, int col, int chrCount, bool visited[MATRIX_SIZE][MATRIX_SIZE]) {
    // caso base: processati correttamente tutti i caratteri
    if (chrCount == strlen(word))
        return true;
    // controlla se sono uscito dai bordi della matrice, o se sono gia' passato
    // dalla casella, o se la lettera processata non corrisponde
    if (row < 0 || col < 0 || row >= MATRIX_SIZE || col >= MATRIX_SIZE || visited[row][col] || m->matrix[row][col] != word[chrCount])
        return false;
    // spunta la casella come visitata
    visited[row][col] = true;
    // visita le caselle adiacenti verticalmente e orizzontalmente
    bool found = foundChr(m, word, row + 1, col, chrCount + 1, visited) ||
                 foundChr(m, word, row - 1, col, chrCount + 1, visited) ||
                 foundChr(m, word, row, col + 1, chrCount + 1, visited) ||
                 foundChr(m, word, row, col - 1, chrCount + 1, visited);

    // rimuovi la spunta di visitata dalla casella
    visited[row][col] = false;

    return found;
}
*/
