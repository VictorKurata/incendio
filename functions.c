#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "functions.h"

// Matriz global
char matriz[TAM][TAM];

// Mutex e variáveis de condição
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* sensor(void* arg) {
    int pos = *(int*)arg;
    int pos_x = pos / TAM;
    int pos_y = pos % TAM;

    free(arg); // Libera a memória alocada para 'arg'

    while (1) {
        pthread_mutex_lock(&mutex);
        
        if (matriz[pos_x][pos_y] == '@') {
            printf("Sensor em (%d, %d) detectou fogo!\n", pos_x, pos_y);
            matriz[pos_x][pos_y] = '/'; // Célula queimada
        }

        pthread_mutex_unlock(&mutex);
        sleep(1); // Verifica a cada segundo
    }
    return NULL;
}

void* geradorIncendio(void* arg) {
    while (1) {
        sleep(3); // Gera incêndios a cada 3 segundos
        int pos_x = rand() % TAM;
        int pos_y = rand() % TAM;

        pthread_mutex_lock(&mutex);
        if (matriz[pos_x][pos_y] == '-') {
            matriz[pos_x][pos_y] = '@'; // Inicia incêndio
            printf("Incêndio iniciado em (%d, %d)\n", pos_x, pos_y);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void printMatrix(char matrix[TAM][TAM]) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    pthread_mutex_unlock(&mutex);
}
