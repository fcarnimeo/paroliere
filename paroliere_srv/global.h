#ifndef GLOBAL_H
#define GLOBAL_H

typedef enum {
    INIT,
    PLAY,
    PAUSE,
    ERROR,
    EXIT   
} ServerState;

// dichiara le variabili globali
extern char *currentWord;
extern volatile ServerState currentState;

#endif // GLOBAL_H