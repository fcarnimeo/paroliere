#include "includes.h"

void *serverStateManager(void *args) {
    struct timespec timeToWait;
    struct timeval now;

    while (true) {
        // variabile per il valore di ritorno della pthread_cond_timedwait
        //int waitRet = 0;

        // entra nello stato PLAYING
        pthread_mutex_lock(&state_mutex);
        // sezione critica
        serverState = PLAYING;
        printf("Stato server: PLAYING\n");
        pthread_cond_broadcast(&state_cond);
        // imposta la durata dello stato PLAYING
        clock_gettime(CLOCK_REALTIME, &timeToWait);
        timeToWait.tv_sec += durata * 60; // <durata> di attesa per lo stato PLAYING
        // imposta la pausa
        pthread_cond_timedwait(&state_cond, &state_mutex, &timeToWait);
        pthread_mutex_unlock(&state_mutex);

        // entra nello stato PAUSED
        pthread_mutex_lock(&state_mutex);
        // sezione critica
        serverState = PAUSED;
        generateRandomMatrix(currentMatrix);
        printf("Stato server: PAUSED\n");
        pthread_cond_broadcast(&state_cond);
        // imposta la durata dello stato PAUSED
        clock_gettime(CLOCK_REALTIME, &timeToWait);
        timeToWait.tv_sec += 60; // 1 minuto di attesa per lo stato PAUSED
        // imposta la pausa
        pthread_cond_timedwait(&state_cond, &state_mutex, &timeToWait);
        pthread_mutex_unlock(&state_mutex);
    }
    printf("serverStateManager_thread terminato.\n");
}