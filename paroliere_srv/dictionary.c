#include "includes.h"

// controlla se una parola e' gia' presente nel dizionario
bool isWordInDictionary(const char *word, Dictionary *d) {
    for (size_t i = 0; i < d->size; i++)
        if (strcmp(word, d->words[i]) == 0)
            return true;
    return false;
}

// converti una stringa in maiuscolo e codifica 'QU come 'Q'
void toUpperCaseAndReplaceQU(char *str) {
    char *src = str;
    char *dest = str;

    // converti lettera per lettera in maiuscolo
    while (*src) {
        if (toupper((unsigned char)*src) == 'Q' && toupper((unsigned char)*(src + 1)) == 'U') {
            *dest++ = 'Q';
            src += 2;  // salta la 'U' dopo 'Q'
        }
        else
            *dest++ = toupper((unsigned char)*src++);
    }
    // termina la stringa
    *dest = '\0';
}

// rimuovi i caratteri whitespace prima e dopo la stringa
char* trimWhitespace(char *str) {
    char *end;

    // rimuovi il whitespace prima della stringa
    while (isspace((unsigned char) *str))
        str++;
    // se sono tutti spazi, restituisco stringa vuota
    if (*str == '\0')
        return str;
    // rimuovi il whitespace dopo la stringa
    end = str + strlen(str) - 1;
    // spostati a ritroso col puntatore, finche' trovi un carattere valido
    while (end > str && isspace((unsigned char) *end))
        end--;
    // termina la stringa
    *(end + 1) = '\0';

    return str;
}

// conta numero parole e lunghezza massima parola all'interno del file
void countWordsAndMaxLength(FILE *file, size_t *wordCount, size_t *maxLength) {
    *wordCount = 0;
    *maxLength = 0;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        // prepara la parola
        char *trimmedLine = trimWhitespace(line);
        size_t length = strlen(trimmedLine);
        if (length > 0) {
            (*wordCount)++; // conta parola valida
            if (length > *maxLength) // trovato nuovo max lunghezza parola
                *maxLength = length; // aggiorno max
        }
    }
    free(line); // libera memoria usata da getline()
    fseek(file, 0, SEEK_SET);  // riporta il puntatore *file a inizio file
}

// carica il file dizionario
void loadDictionary(char *filename, TrieNode *dizionario) {
    // apri il file in lettura
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Apertura del file dizionario non riuscita.\n");
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }

    // conta numero parole e lunghezza massima parola nel file dizionario
    // utile per una allocazione efficiente di memoria
    size_t wordCount, maxLength;
    countWordsAndMaxLength(file, &wordCount, &maxLength);

    size_t index = 0, len = 0;
    char *line = NULL;
    // inserisci le parole dal file al dizionario in memoria
    while (getline(&line, &len, file) != -1 && index < wordCount) {
        char *trimmedLine = trimWhitespace(line);
        if (strlen(trimmedLine) > 0) {
            toUpperCaseAndReplaceQU(trimmedLine);
            insertWord(dizionario, trimmedLine); // inserisci parola nella trie
            //dictionary->words[index] = strdup(trimmedLine);
            index++;
        }
    }
    free(line); // libera memoria usata da getline()
    fclose(file);
}

// controlla se una parola e' presente nel dizionario
bool foundInDictionary(Dictionary *dictionary, const char *word) {
    // N.B. +1 per il carattere '\0'
    char *temp = malloc((dictionary->maxWordLength + 1) * sizeof(char));
    // copia nella variabile temporanea di appoggio
    strncpy(temp, word, dictionary->maxWordLength);
    // aggiusta la stringa
    temp[dictionary->maxWordLength] = '\0';
    toUpperCaseAndReplaceQU(temp);
    // effettua binary search, dato che dictionary e' ordinato
    char **result = bsearch(&temp, dictionary->words, dictionary->size, sizeof(char *), (int (*)(const void *, const void *)) strcmp);
    free(temp); // libera memoria
    return result != NULL;
}

// libera la memoria allocata dinamicamente per il dizionario
void freeDictionary(Dictionary *dictionary) {
    // libera prima le parole
    for (size_t i = 0; i < dictionary->size; i++) {
        free(dictionary->words[i]);
    }
    // libera successivamente l'array delle parole
    free(dictionary->words);
}