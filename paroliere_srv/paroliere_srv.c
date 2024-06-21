#include "includes.h"

// crea le mutex
pthread_mutex_t currentWord_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t currentState_mtx = PTHREAD_MUTEX_INITIALIZER;
// inizializza le variabili globali
char currentWord[10] = "         ";
ServerState currentState = WAIT_INIT;



int main(void) {
    printf("Hello World!\n");
}