#include "includes.h"

// ricerca dfs nella matrice
void dfs(Matrix *m, bool visited[MATRIX_SIZE][MATRIX_SIZE], char *word, int row, int col, int length, Dictionary *d, Dictionary *validWords) {//, int *wordCount) {
    if (length >= MATRIX_SIZE && isWordInDictionary(word, d)) {
        // se la parola non e' gia' stata trovata
        if (!isWordInDictionary(word, validWords)) {
            // aggiungi la parola in coda
            strcpy(validWords->words[validWords->size], word);
            // aumenta dimensione dizionario parole valide
            (validWords->size)++;
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
            dfs(m, visited, word, newRow, newCol, length + 1, d, validWords);
            // togli la spunta di visitata
            visited[newRow][newCol] = false;
        }
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

void generateRandomMatrix(Matrix *m) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            m->matrix[i][j] = 'A' + (rand() % 26); // valore tra 'A' e 'Z'
        }
    }
}

// funzione ausiliaria: genera parole valide dalla matrice
void generateValidWords(Matrix *m, Dictionary *d, Dictionary *validWords) {
    char word[MATRIX_SIZE + 1];
    bool visited[MATRIX_SIZE][MATRIX_SIZE] = {false};

    // avvia la generazione a partire da ogni cella
    for (int row = 0; row < MATRIX_SIZE; row++) {
        for (int col = 0; col < MATRIX_SIZE; col++) {
            visited[row][col] = true;
            word[0] = m->matrix[row][col];
            word[1] = '\0';
            dfs(m, visited, word, row, col, 1, d, validWords);
            visited[row][col] = false;
        }
    }
}
