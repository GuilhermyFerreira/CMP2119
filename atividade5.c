#include <stdio.h>
#include <stdlib.h>
// Classificação (Ciclo, Completo ou Roda)

// Função auxiliar para ordenar o vetor de graus (Bubble Sort)
void ordenarGraus(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j+1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = temp;
            }
        }
    }
}

int main() {
    int v1, v2;

    printf("Vertices do Grafo 1: "); scanf("%d", &v1);
    printf("Vertices do Grafo 2: "); scanf("%d", &v2);

    // Condição 1: Número de vértices deve ser igual
    if (v1 != v2) {
        printf("\nNao podem ser isomorfos (numero de vertices diferente).\n");
        return 0;
    }

    int v = v1;
    int *grausG1 = calloc(v, sizeof(int));
    int *grausG2 = calloc(v, sizeof(int));
    int arestasG1 = 0, arestasG2 = 0;
    int temp;

    // Lendo Grafo 1 (Adjacência) e somando graus
    printf("\nDigite a matriz de adjacencia do Grafo 1:\n");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &temp);
            if (temp == 1) {
                grausG1[i]++;
                arestasG1++;
            }
        }
    }

    // Lendo Grafo 2 e somando graus
    printf("\nDigite a matriz de adjacencia do Grafo 2:\n");
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            scanf("%d", &temp);
            if (temp == 1) {
                grausG2[i]++;
                arestasG2++;
            }
        }
    }

    // Condição 2: Número de arestas deve ser igual
    if (arestasG1 != arestasG2) {
        printf("\nNao podem ser isomorfos (numero de arestas diferente).\n");
        free(grausG1); free(grausG2);
        return 0;
    }

    // Condição 3: Sequência de graus deve ser idêntica
    ordenarGraus(grausG1, v);
    ordenarGraus(grausG2, v);

    int podemSer = 1;
    for (int i = 0; i < v; i++) {
        if (grausG1[i] != grausG2[i]) {
            podemSer = 0;
            break;
        }
    }

    if (podemSer) {
        printf("\nOs grafos PODEM ser isomorfos (possuem a mesma sequencia de graus).\n");
    } else {
        printf("\nOs grafos NAO PODEM ser isomorfos (sequencia de graus diferente).\n");
    }

    free(grausG1); free(grausG2);
    return 0;
}