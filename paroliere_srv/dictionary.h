#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "struct.h"

void countWordsAndMaxLength(FILE *file, size_t *wordCount, size_t *maxLength);
bool foundInDictionary(Dictionary *dictionary, const char *word);
void freeDictionary(Dictionary *dictionary);
bool isWordInDictionary(const char *word, Dictionary *d);
void loadDictionary(char *filename);
void toUpperCaseAndReplaceQU(char *str);
char* trimWhitespace(char *str);

#endif // DICTIONARY_H