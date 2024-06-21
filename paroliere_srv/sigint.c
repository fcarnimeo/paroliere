#include "includes.h"

void sigintHandler() {
    printf("Ricevuto SIGINT (CTRL-C). Inizio spegnimento del server.\n");
    currentState = EXIT;
}