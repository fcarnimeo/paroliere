#include "includes.h"

// funzione ricorsiva DFS per trovare corrispondenze tra caratteri
bool foundChr(char matrix[MATRIX_SIZE][MATRIX_SIZE], char *word, int row, int col, int chrCount, bool visited[MATRIX_SIZE][MATRIX_SIZE]) {
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

int findWordInMatrix(char matrix[MATRIX_SIZE][MATRIX_SIZE], char *word) {
    // lunghezza minima 4 lettere
    if (strlen(word) < 4)
        return 0;

    // inizializza matrice lettere visitate
    bool visited[MATRIX_SIZE][MATRIX_SIZE] = {false};

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (foundChr(matrix, word, i, j, 0, visited)) {
                return strlen(word); // Return the length of the word as the score
            }
        }
    }
    return 0; // parola non trovata
}

int main() {
    char matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'},
        {'B', 'C', 'D', 'F'}
    };

    char *words[] = {"ABCCED", "SEE", "ABCB", "FADE", "BAD"};
    int totalScore = 0;

    for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++) {
        int score = findWordInMatrix(matrix, words[i]);
        if (score > 0) {
            printf("Word '%s' found in the matrix, Score: %d\n", words[i], score);
            totalScore += score;
        } else {
            printf("Word '%s' not found in the matrix\n", words[i]);
        }
    }

    printf("Total Score: %d\n", totalScore);

    return 0;
}