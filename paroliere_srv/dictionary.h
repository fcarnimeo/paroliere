#ifndef DICTIONARY_H
#define DICTIONARY_H

void countWordsAndMaxLength(FILE *file, size_t *wordCount, size_t *maxLength);
bool foundInDictionary(Dictionary *dictionary, const char *word);
void freeDictionary(Dictionary *dictionary);
void loadDictionary(char *filename, Dictionary *dictionary);
void toUpperAndReplaceQU(char *str);
char* trimWhitespace(char *str);

#endif // DICTIONARY_H