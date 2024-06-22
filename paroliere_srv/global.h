#ifndef GLOBAL_H
#define GLOBAL_H

#include "includes.h"

static typedef enum {
    INIT,
    PLAY,
    PAUSE,
    ERROR,
    EXIT   
} ServerState;

// dichiara le variabili globali
// TODO - extern?
char currentWord[10];
volatile ServerState currentState;

#endif // GLOBAL_H