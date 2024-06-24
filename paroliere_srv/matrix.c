#include "includes.h"

// funzione ricorsiva DFS per trovare corrispondenze tra caratteri
bool foundChr(int matrix[MATRIX_SIZE][MATRIX_SIZE], char *word, int row, int col, int chrCount, bool visited[MATRIX_SIZE][MATRIX_SIZE]) {
    // caso base: processati correttamente tutti i caratteri
    if (chrCount == strlen(word))
        return true;
    // controlla se sono uscito dai bordi della matrice, o se sono gia' passato
    // dalla casella, o se la lettera processata non corrisponde
    if (row < 0 || col < 0 || row >= MATRIX_SIZE || col >= MATRIX_SIZE || visited[row][col] || matrix[row][col] != word[chrCount])
        return false;
    // spunta la casella come visitata
    visited[row][col] = true;
    // visita le caselle adiacenti verticalmente e orizzontalmente
    bool found = foundChr(matrix, word, row + 1, col, chrCount + 1, visited) ||
                 foundChr(matrix, word, row - 1, col, chrCount + 1, visited) ||
                 foundChr(matrix, word, row, col + 1, chrCount + 1, visited) ||
                 foundChr(matrix, word, row, col - 1, chrCount + 1, visited);

    // rimuovi la spunta di visitata dalla casella
    visited[row][col] = false;

    return found;
}

// il valore di ritorno e' il punteggio della parola
int findWord(int matrix[MATRIX_SIZE][MATRIX_SIZE], char *word) {
    // lunghezza minima 4 lettere
    if (strlen(word) < 4)
        return 0;
    // inizializza matrice lettere visitate
    bool visited[MATRIX_SIZE][MATRIX_SIZE] = {false};
    // cerca parola a partire da ogni casella
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (foundChr(matrix, word, i, j, 0, visited)) {
                return strlen(word); // punteggio parola
            }
        }
    }
    return 0; // parola non trovata
}