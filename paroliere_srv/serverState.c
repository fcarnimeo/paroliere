#include "includes.h"

void *serverStateManager(void *arg) {
    while (true) {
        // entra nello stato PLAYING
        pthread_mutex_lock(&state_mutex);
        serverState = PLAYING;
        printf("Stato server: PLAYING\n");
        pthread_cond_broadcast(&state_cond);
        pthread_mutex_unlock(&state_mutex);
        sleep(durata * 60); // rimani in attesa che PLAYING finisca

        // entra nello stato PAUSED
        pthread_mutex_lock(&state_mutex);
        serverState = PAUSED;
        printf("Stato server: PLAYING\n");
        pthread_cond_broadcast(&state_cond);
        pthread_mutex_unlock(&state_mutex);
        sleep(60); // rimani in attesa che PAUSED finisca
    }
}