#ifndef INCLUDES_H
#define INCLUDES_H

#include <ctype.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "dictionary.h"
#include "init.h"
#include "matrix.h"
#include "struct.h"
#include "trie.h"

#define EXPECTED_TOKENS 16
#define MATRIX_SIZE 4

extern Matrix *currentMatrix;
extern volatile ServerState currentState;
extern pthread_mutex_t currentState_mtx;
extern pthread_mutex_t currentWord_mtx;
extern Dictionary *dictionary;
extern TrieNode *dizionario;
extern TrieNode *paroleValide;
extern unsigned int rndSeed;

#endif // INCLUDES_H