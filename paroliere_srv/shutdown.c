#include "includes.h"

void shutdownServer(void) {
    //close(serverSocket);
    // sveglia thread in attesa
    pthread_mutex_lock(&state_mutex);
    pthread_cond_broadcast(&state_cond);
    pthread_mutex_unlock(&state_mutex);

    // chiudi i vari thread
    pthread_join(serverStateManager_thread, NULL);

    printf("Server spento correttamente.\n");
}
