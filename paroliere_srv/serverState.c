#include "includes.h"

void *serverStateManager(void) {
    while (true) {
        // entra nello stato PLAYING
        pthread_mutex_lock(&state_mutex);
        // controlla se e' arrivato il segnale di spegnimento
        //if (serverState == SHUTDOWN) {
        if (shuttingDown) {
            pthread_mutex_unlock(&state_mutex);
            break; // esci dal ciclo, ergo dal thread
        }
        serverState = PLAYING;
        printf("Stato server: PLAYING\n");
        pthread_cond_broadcast(&state_cond);
        pthread_mutex_unlock(&state_mutex);
        sleep(durata * 60); // rimani in attesa che PLAYING finisca

        // entra nello stato PAUSED
        pthread_mutex_lock(&state_mutex);
        // controlla se e' arrivato il segnale di spegnimento
        //if (serverState == SHUTDOWN) {
        if (shuttingDown) {
            pthread_mutex_unlock(&state_mutex);
            break; // esci dal ciclo, ergo dal thread
        }
        serverState = PAUSED;
        generateRandomMatrix(currentMatrix);
        printf("Stato server: PAUSED\n");
        pthread_cond_broadcast(&state_cond);
        pthread_mutex_unlock(&state_mutex);
        sleep(60); // rimani in attesa che PAUSED finisca
    }
}