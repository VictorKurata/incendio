#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "functions.h"

int main() {
    pthread_t sensores[TAM * TAM];
    pthread_t gerador;

    // Inicializa a matriz
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            matriz[i][j] = '-'; // Área livre
        }
    }

    // Cria threads de sensores
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            int* pos = malloc(sizeof(int));
            *pos = i * TAM + j; // Posição única para cada sensor
            pthread_create(&sensores[i * TAM + j], NULL, sensor, pos);
            // pthread_detach(sensores[i * TAM + j]); // Use se não precisar do join
        }
    }

    // Cria thread geradora de incêndios
    pthread_create(&gerador, NULL, geradorIncendio, NULL);
    
    // Loop principal para imprimir a matriz
    while (1) {
        printMatrix(matriz);
        sleep(2); // Atualiza a matriz a cada 2 segundos
    }

    // Aguarda as threads (nunca vai chegar aqui devido ao loop infinito)
    for (int i = 0; i < TAM * TAM; i++) {
        pthread_join(sensores[i], NULL);
    }
    pthread_join(gerador, NULL);
    
    return 0;
}
