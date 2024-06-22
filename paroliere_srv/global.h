#ifndef GLOBAL_H
#define GLOBAL_H

#include "includes.h"

typedef enum {
    INIT,
    PLAY,
    PAUSE,
    ERROR,
    EXIT   
} ServerState;

// dichiara le variabili globali
extern char currentWord[10];
extern volatile ServerState currentState;

#endif // GLOBAL_H