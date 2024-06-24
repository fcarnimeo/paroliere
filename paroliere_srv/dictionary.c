
// Function to convert a string to uppercase and replace "QU" with "Q"
void toUpperCaseAndReplaceQU(char *str) {
    char *src = str;
    char *dest = str;

    while (*src) {
        if (toupper((unsigned char)*src) == 'Q' && toupper((unsigned char)*(src + 1)) == 'U') {
            *dest++ = 'Q';
            src += 2;  // Skip "U" after "Q"
        } else {
            *dest++ = toupper((unsigned char)*src++);
        }
    }
    *dest = '\0';
}

// Function to trim leading and trailing whitespace
char* trimWhitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';

    return str;
}

// Function to count the number of valid words and find the max word length in the file
void countWordsAndMaxLength(FILE *file, size_t *wordCount, size_t *maxLength) {
    *wordCount = 0;
    *maxLength = 0;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        char *trimmedLine = trimWhitespace(line);
        size_t length = strlen(trimmedLine);
        if (length > 0) {
            (*wordCount)++;
            if (length > *maxLength) {
                *maxLength = length;
            }
        }
    }

    free(line);
    fseek(file, 0, SEEK_SET);  // Reset file pointer to the beginning
}

// Function to load the dictionary from a file
void loadDictionary(char *filename, Dictionary *dictionary) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    size_t wordCount, maxLength;
    countWordsAndMaxLength(file, &wordCount, &maxLength);

    dictionary->size = wordCount;
    dictionary->maxWordLength = maxLength;
    dictionary->words = malloc(dictionary->size * sizeof(char*));
    if (!dictionary->words) {
        perror("Failed to allocate memory for words");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t index = 0;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1 && index < dictionary->size) {
        char *trimmedLine = trimWhitespace(line);

        if (strlen(trimmedLine) > 0) {
            toUpperCaseAndReplaceQU(trimmedLine);
            dictionary->words[index] = strdup(trimmedLine);
            index++;
        }
    }

    free(line);
    fclose(file);

    // Sort the words for binary search
    qsort(dictionary->words, dictionary->size, sizeof(char *), (int (*)(const void *, const void *)) strcmp);
}

// Function to check if a word is in the dictionary using binary search
bool foundInDictionary(Dictionary *dictionary, const char *word) {
    char *temp = malloc((dictionary->maxWordLength + 1) * sizeof(char));
    strncpy(temp, word, dictionary->maxWordLength);
    temp[dictionary->maxWordLength] = '\0';
    toUpperCaseAndReplaceQU(temp);
    char **result = bsearch(&temp, dictionary->words, dictionary->size, sizeof(char *),
                            (int (*)(const void *, const void *)) strcmp);
    free(temp);
    return result != NULL;
}

// Function to free the memory allocated for the dictionary
void freeDictionary(Dictionary *dictionary) {
    for (size_t i = 0; i < dictionary->size; i++) {
        free(dictionary->words[i]);
    }
    free(dictionary->words);
}

// Example usage
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dictionary_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Dictionary dictionary;
    loadDictionary(argv[1], &dictionary);

    // Example check
    char word[256];
    printf("Enter a word to search in dictionary: ");
    scanf("%255s", word);

    if (foundInDictionary(&dictionary, word)) {
        printf("The word '%s' was found in the dictionary.\n", word);
    } else {
        printf("The word '%s' was not found in the dictionary.\n", word);
    }

    // Free the allocated memory
    freeDictionary(&dictionary);

    return EXIT_SUCCESS;
}




void loadDictionary(char *filename) {
    ssize_t bytesRead;
    size_t len = 0;
    char *line = NULL;
    int linesCounter = 0;

    // apri il file descriptor
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Apertura del file dizionario non riuscita.\n");
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }
    // ottieni proprieta' file
    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        fprintf(stderr, "Lettura proprieta' file dizionario non riuscita\n");
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }
    // apri il file in lettura
    FILE *file = fdopen(fd, "r");
    if (file == NULL) {
        fprintf(stderr, "Apertura del file dizionario non riuscita.\n");
        close(fd);
        // TODO - da implementare
        exit(EXIT_FAILURE);
    }
    // alloca memoria per contenere il dizionario
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