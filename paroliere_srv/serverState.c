#include "includes.h"

void *serverStateManager(void *args) {
    struct timespec timeToWait;
    struct timeval now;

    // ottieni la mutex di stato, primissima iterazione
    pthread_mutex_lock(&state_mutex);
    while (true) {
        // entra nello stato PAUSED
        // sezione critica
        serverState = PAUSED;
        printf("Stato server: PAUSED\n");
        loadNewMatrix(currentMatrix, dataFilename);
        printf("Inizio generazione parole valide.\n");
        generateValidWords(currentMatrix, dizionario, paroleValide);
        printf("Parole valide caricate.\n");
        // imposta la durata dello stato PAUSED
        clock_gettime(CLOCK_REALTIME, &timeToWait);
        timeToWait.tv_sec += 2; // 1 minuto di attesa per lo stato PAUSED
        pthread_cond_broadcast(&state_cond);
        // imposta la pausa
        pthread_cond_timedwait(&state_cond, &state_mutex, &timeToWait); // mutex libera nel frattempo
        if (serverState == SHUTDOWN)
            break;

        // entra nello stato PLAYING
        // sezione critica
        serverState = PLAYING;
        printf("Stato server: PLAYING\n");
        printf("Matrice in gioco: %p\n", (void *)currentMatrix);
        printMatrix(currentMatrix);
        // imposta la durata dello stato PLAYING
        clock_gettime(CLOCK_REALTIME, &timeToWait);
        timeToWait.tv_sec += durata * 2; // <durata> di attesa per lo stato PLAYING
        pthread_cond_broadcast(&state_cond);
        // imposta la pausa
        pthread_cond_timedwait(&state_cond, &state_mutex, &timeToWait); // mutex libera nel frattempo
        if (serverState == SHUTDOWN)
            break;

        // entra nello stato PAUSING
        // sezione critica
        serverState = PAUSING;
        printf("Stato server: PAUSING\n");
    }
    // rilascia la mutex di stato
    pthread_mutex_unlock(&state_mutex);

    printf("serverStateManager_thread terminato.\n");
}