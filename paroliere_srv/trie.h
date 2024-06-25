#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 26

// struct per nodo della trie
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

// funzioni per le trie
TrieNode* createNode();
void insertWord(TrieNode *trieRoot, const char *word);
bool searchWord(TrieNode *trieRoot, const char *word);

#endif // TRIE_H