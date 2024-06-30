#include "includes.h"

void *clientHandler(void* args) {
    printf("Connessione accettata dal client.\n");

    while (true) {
        int clientSocket;

        pthread_mutex_lock(&clientQueue_mutex);
        while (clientQueue_size == 0 && serverState != SHUTDOWN) {
            pthread_cond_wait(&clientQueue_cond, &clientQueue_mutex);
        }
        if (serverState == SHUTDOWN) {
            pthread_mutex_unlock(&clientQueue_mutex);
            break;
        }
        clientSocket = clientQueue[--clientQueue_size];
        pthread_mutex_unlock(&clientQueue_mutex);

        handleClientMessage(clientSocket);
    }
}

void handleClientMessage(int clientSocket) {

}