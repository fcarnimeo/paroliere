#ifndef TRIE_H
#define TRIE_H

// funzioni per le trie
TrieNode* createNode();
void insertWord(TrieNode *trieRoot, const char *word);
bool searchWord(TrieNode *trieRoot, const char *word);

#endif // TRIE_H