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
    char header[5];
    int readBytes, offset = 0;
    Message msg;

    while (true) {
        // leggi l'intestazione
        // (1 byte del tipo, e 4 byte per unsigned int di lunghezza messaggio)
        readBytes = read(clientSocket, header + offset, sizeof(header) - offset);
        if (readBytes == 0) {
            printf("Client disconnesso.\n");
            free(msg.data);
            break;
        }
        if (readBytes < 0) {
            perror("Errore in ricezione messaggio dal client.\n");
            free(msg.data);
            break;
        }
        offset += readBytes;
    }
    if (offset < sizeof(header))
        continue; // aspetta di ricevere l'header completo

    // processa l'header
    msg.type = header[0];
    memcpy(&msg.length, header + 1, sizeof(unsigned int));
    msg.length = ntohl(msg.length); // converti da network byte order a quello dell'host

    // alloca memoria per il contenuto del messaggio
    msg.data = malloc(msg.size + 1);
    if (msg.data == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // leggi il contenuto del messaggio
    offset = 0;
    while (offset < msg.length) {
        readBytes = read(clientSocket, msg.data + offset, msg.length - offset);
        if (readBytes == 0) {
            printf("Client disconnesso.\n");
            free(msg.data);
            break;
        }
        if (readBytes < 0) {
            perror("Errore in ricezione messaggio dal client.\n");
            free(msg.data);
            break;
        }
        offset += readBytes;
    }
    if (offset < msg.length) {
        free(msg.data);
        break; // messaggio incompleto
    }

    // termina la stringa
    msg.data[msg.length] = '\0';

    // processa il messaggio
    pthread_mutex_lock(&state_mutex);
    // controlla se il server e' in shutdown
    if (serverState == SHUTDOWN) {
        pthread_mutex_unlock(&state_mutex);
        free(msg.data);
        close(clientSocket);
        return;
    }
    // controlla che il server non stia andando in pausa
    while (serverState == PAUSING)
        pthread_cond_wait(&state_cond, &state_mutex);
    Message response;
    switch (msg.type) {
    }
    free(msg.data);
    }
    // close(clientSocket); ???
}