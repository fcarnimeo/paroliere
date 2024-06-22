#ifndef GLOBAL_H
#define GLOBAL_H

#include "serverState.h"

// crea le mutex
pthread_mutex_t currentWord_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t currentState_mtx = PTHREAD_MUTEX_INITIALIZER;
// inizializza le variabili globali
// TODO - extern?
char currentWord[10] = "         ";
volatile ServerState currentState = INIT;

#endif // GLOBAL_H