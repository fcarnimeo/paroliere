#include "includes.h"

// dichiara le mutex
pthread_mutex_t currentWord_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t currentState_mtx = PTHREAD_MUTEX_INITIALIZER;
extern char *currentWord = "         ";
extern volatile ServerState currentState = INIT;