#include "includes.h"

// crea le mutex
pthread_mutex_t currentWord_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t currentState_mtx = PTHREAD_MUTEX_INITIALIZER;
// inizializza le variabili globali
char currentWord[10] = "         ";
ServerState currentState = INIT;

int main(void) {
    // TODO - numero porta da CLI
    initServer(12345, NULL);
}