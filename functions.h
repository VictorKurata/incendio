#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define TAM 30

// Declaração da matriz como global
extern char matriz[TAM][TAM];

void* sensor(void* arg);
void* geradorIncendio(void* arg);
void printMatrix(char matrix[TAM][TAM]);

#endif
