#include "includes.h"

void *serverStateManager(void *args) {
    struct timespec timeToWait;
    struct timeval now;

    // ottieni la mutex di stato, primissima iterazione
    pthread_mutex_lock(&state_mutex);
    while (true) {
        // entra nello stato PLAYING
        // sezione critica
        serverState = PLAYING;
        printf("Stato server: PLAYING\n");
        pthread_cond_broadcast(&state_cond);
        // imposta la durata dello stato PLAYING
        clock_gettime(CLOCK_REALTIME, &timeToWait);
        timeToWait.tv_sec += durata * 2; // <durata> di attesa per lo stato PLAYING
        // imposta la pausa
        pthread_cond_timedwait(&state_cond, &state_mutex, &timeToWait); // mutex libera nel frattempo
        if (serverState == SHUTDOWN)
            break;

        // entra nello stato PAUSING
        // sezione critica
        serverState = PAUSING;
        pthread_mutex_unlock(&state_mutex);

        // entra nello stato PAUSED
        // sezione critica
        pthread_mutex_lock(&state_mutex);
        serverState = PAUSED;
        generateRandomMatrix(currentMatrix);
        printf("Stato server: PAUSED\n");
        printf("Nuova matrice: %p\n", (void *)currentMatrix);
        pthread_cond_broadcast(&state_cond);
        // imposta la durata dello stato PAUSED
        clock_gettime(CLOCK_REALTIME, &timeToWait);
        timeToWait.tv_sec += 2; // 1 minuto di attesa per lo stato PAUSED
        // imposta la pausa
        pthread_cond_timedwait(&state_cond, &state_mutex, &timeToWait); // mutex libera nel frattempo
        if (serverState == SHUTDOWN)
            break;
    }
    // rilascia la mutex di stato
    pthread_mutex_unlock(&state_mutex);

    printf("serverStateManager_thread terminato.\n");
}