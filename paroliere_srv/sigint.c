#include "includes.h"

void sigintHandler(int sig) {
    printf("Ricevuto segnale %d - SIGINT - (CTRL-C)." 
    "Inizio spegnimento del server.\n", sig);
    currentState = EXIT;
}