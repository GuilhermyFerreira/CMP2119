#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *vizinhos;
    int quantidade;
} ListaAdjacencia;

int main() {
    int vertices;

    printf("jDigite o numero de vertices: ");
    scanf("%d", &vertices);
    while (vertices <= 0) {
        printf("Numero invalido.\n");
        system("clear");
        printf("Digite o numero de vertices: ");
        scanf("%d", &vertices);
    }

    ListaAdjacencia *lista = malloc(vertices * sizeof(ListaAdjacencia));

    // entrada da lista
    for (int i = 0; i < vertices; i++) {
        printf("\nQuantos vertices estao ligados ao vertice %d? ", i);
        scanf("%d", &lista[i].quantidade);

        while (lista[i].quantidade < 0 || lista[i].quantidade > vertices-1){
            printf("Quantidade invalida.\n");   
            printf("Quantos vertices estao ligados ao vertice %d? ", i);
            scanf("%d", &lista[i].quantidade);
        }

        lista[i].vizinhos = malloc(lista[i].quantidade * sizeof(int));

        printf("Digite os vertices ligados ao vertice %d:\n", i);
        for (int j = 0; j < lista[i].quantidade; j++) {
            scanf("%d", &lista[i].vizinhos[j]);

            while (lista[i].vizinhos[j] < 0 || lista[i].vizinhos[j] >= vertices) {
                printf("Vertice invalido.\n");
                printf("Digite os vertices ligados ao vertice %d:\n", i);
                scanf("%d", &lista[i].vizinhos[j]);
            }
        }
    }

    // mostrar lista de adjacencia
    printf("\nLista de adjacencia:\n");
    for (int i = 0; i < vertices; i++) {
        printf("%d -> ", i);
        for (int j = 0; j < lista[i].quantidade; j++) {
            printf("%d ", lista[i].vizinhos[j]);
        }
        printf("\n");
    }

    // criar matriz
    int **matriz = malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        matriz[i] = malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            matriz[i][j] = 0;
        }
    }

    // converter lista para matriz
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < lista[i].quantidade; j++) {
            int destino = lista[i].vizinhos[j];
            matriz[i][destino] = 1;
        }
    }

    // mostrar matriz
    printf("\nMatriz de adjacencia:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // verificar na lista se e direcionado
    int simetrico = 1;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < lista[i].quantidade; j++) {
            int destino = lista[i].vizinhos[j];
            int encontrouVolta = 0;

            for (int k = 0; k < lista[destino].quantidade; k++) {
                if (lista[destino].vizinhos[k] == i) {
                    encontrouVolta = 1;
                    break;
                }
            }

            if (encontrouVolta == 0) {
                simetrico = 0;
                break;
            }
        }
        if (simetrico == 0)
            break;
    }

    if (simetrico == 1) {
        printf("\nO grafo nao e direcionado.\n");
    } else {
        printf("\nO grafo e direcionado.\n");
    }

    for (int i = 0; i < vertices; i++) {
        free(lista[i].vizinhos);
    }
    free(lista);

    for (int i = 0; i < vertices; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}