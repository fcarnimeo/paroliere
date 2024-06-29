#ifndef INCLUDES_H
#define INCLUDES_H

#define  _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdatomic.h>
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
#include "serverState.h"
#include "shutdown.h"
#include "struct.h"
#include "trie.h"

#define EXPECTED_TOKENS 16
#define MATRIX_SIZE 4

extern Matrix *currentMatrix;
extern char *dataFilename;
extern Dictionary *dictionary;
extern TrieNode *dizionario;
extern int durata;
extern Matrices *loadedMatrices;
extern pthread_cond_t matrix_cond;
extern pthread_mutex_t matrix_mutex;
extern TrieNode *paroleValide;
extern unsigned int rndSeed;
extern volatile _Atomic ServerState serverState;
extern pthread_t serverStateManager_thread;
extern volatile sig_atomic_t shuttingDown;
extern pthread_cond_t state_cond;
extern pthread_mutex_t state_mutex;

#endif // INCLUDES_H
