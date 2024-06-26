#include "includes.h"

void initServer(char *nomeServer, int portaServer, char *dataFilename, int durata, unsigned int rndSeed, char *dizionarioFilename, int disconnettiMinuti) {
    printf("Inizio avvio server.\n");
    TrieNode *dizionario = createNode();
    TrieNode *paroleValide = createNode();
    //initSocket(port);
    // carica matrici da file, se presente
    if (dataFilename != NULL)
        loadMatrices(dataFilename);
    // altrimenti inizializza il seed
    else
        rndSeed = (unsigned int)time(NULL);
        srand(rndSeed);
        // TODO genera matrici casuali
    // carica il dizionario parole valide
    if (dizionarioFilename != NULL)
        loadDictionary(dizionarioFilename);
    // altrimenti carica dizionario di default
    // TODO
    printf("Inizio generazione parole valide.\n");
    generateValidWords(currentMatrix, dizionario, paroleValide);
}

// TODO - implementare per bene. Dopo che il socket e' partito,
// come accetto le connessioni dei client?
void initSocket(int port) {
    // crea il socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    // controlla errori in fase di creazione del socket
    if (server == -1) {
        perror("Errore nella creazione del socket.");
        exit(EXIT_FAILURE);
    }
    // imposta i parametri di rete per il server
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // accoppia il socket con indirizzo e porta
    if (bind(server, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Errore in fase di accoppiamento del socket.");
        exit(EXIT_FAILURE);
    }
    // mette il server in ascolto
    if (listen(server, 10) == -1) {
        perror("Errore in fase di ascolto del server.");
        exit(EXIT_FAILURE);
    }
    printf("Server in ascolto sulla porta %d.\n", port);
}
