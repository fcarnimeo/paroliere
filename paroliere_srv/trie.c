#include "includes.h"

// funzione per creare un nodo della trie
TrieNode* createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    // controlla errori per malloc()
    if (node == NULL) {
        fprintf(stderr, "Errore creazione nodo della trie.\n");
        exit(EXIT_FAILURE);
    }
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

// funzione per inserire una parola nella trie
void insertWord(TrieNode *trieRoot, const char *word) {
    TrieNode *current = trieRoot;
    while (*word) {
        int index = *word - 'A';
        if (!current->children[index])
            current->children[index] = createNode();
        current = current->children[index];
        word++;
    }
    current->isEndOfWord = true;
}

// funzione per cercare una parola nella trie
bool searchWord(TrieNode *trieRoot, const char *word) {
    TrieNode *current = trieRoot;
    while (*word) {
        int index = *word - 'A';
        if (!current->children[index])
            return false;
        current = current->children[index];
        word++;
    }
    return current && current->isEndOfWord;
}