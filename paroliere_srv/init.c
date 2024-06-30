#include "includes.h"

void initServer(char *nomeServer, int portaServer, char *dataFilename, int durata, unsigned int rndSeed, char *dizionarioFilename, int disconnettiMinuti) {
    printf("Inizio avvio server.\n");
    initMatrices();
    // avvia il thread che gestisce lo stato del server
    pthread_create(&serverStateManager_thread, NULL, serverStateManager, NULL);
    // avvia la parte di rete
    initSocket(nomeServer, portaServer);
}

void initMatrices(void) {
    TrieNode *dizionario = createNode();
    TrieNode *paroleValide = createNode();
    currentMatrix = (Matrix *)malloc(sizeof(Matrix));
    if (currentMatrix == NULL) {
        perror("currentMatrix");
        exit(EXIT_FAILURE);
    }
    // carica matrici da file, se presente
    if (dataFilename != NULL) {
        loadMatrices(dataFilename);
        currentMatrix = loadedMatrices->firstMatrix;
    }
    // altrimenti inizializza il seed e alloca memoria per le matrici casuali
    else {
        rndSeed = (unsigned int)time(NULL);
        srand(rndSeed);
    }
    // carica il dizionario parole valide
    if (dizionarioFilename != NULL)
        loadDictionary(dizionarioFilename, dizionario);
    // altrimenti carica dizionario di default
    else
        loadDictionary("dict.txt", dizionario);
}

void initSocket(char *nomeServer, int portaServer) {
    // crea il socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    // crea il fd per i nuovi socket,
    // dopo connessione riuscita da parte di un client
    int newSocket;
    struct sockaddr_in serverAddress;
    // variabile per lunghezza indirizzo
    int addrLen = sizeof(serverAddress);
    // controlla errori in fase di creazione del socket
    if (server == -1) {
        perror("Errore nella creazione del socket.");
        exit(EXIT_FAILURE);
    }
    // imposta i parametri di rete per il server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portaServer);
    serverAddress.sin_addr.s_addr = inet_addr(nomeServer);
    // accoppia il socket con indirizzo e porta
    if (bind(server, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Errore in fase di accoppiamento del socket.");
        exit(EXIT_FAILURE);
    }
    // metti il server in ascolto
    if (listen(server, 16) == -1) {
        perror("Errore in fase di ascolto del server.");
        exit(EXIT_FAILURE);
    }
    printf("Fin qui ci siamo arrivati.\n");
    // crea i worker thread
    pthread_t threads[CLIENT_THREADS];
    int threadSockets[CLIENT_THREADS];
    for (int i = 0; i < CLIENT_THREADS; i++) {
        if ((newSocket = accept(server,
                                (struct sockaddr *)&serverAddress,
                                (socklen_t *)&addrLen)) == -1) {
            perror("Errore in accettazione connessione da client.");
            close(server);
            exit(EXIT_FAILURE);
        }
        threadSockets[i] = newSocket;
        if (pthread_create(&threads[i], NULL, clientHandler, &threadSockets[i]) != 0) {
            perror("Error creazione thread per client handler.");
            close(newSocket);
            exit(EXIT_FAILURE);
        }
    }

    // aspetta che tutti i thread finiscano
    for (int i = 0; i < CLIENT_THREADS; i++) {
        if (pthread_detach(threads[i]) != 0) {
            perror("Errore nella detach del client handler thread.");
        }
    }

    close(server);
    printf("Tutti i thread sono stati terminati.\nAvvio spegnimento del server.\n");
    atomic_store(&serverState, SHUTDOWN);
}