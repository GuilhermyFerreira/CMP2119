#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *vizinhos;
    int quantidade;
} ListaAdj;

int main(){
    int vertices, i, j;

    printf("Digite a quantidade de vertices: ");
    scanf("%d", &vertices);
    while(vertices <= 0){
        printf("Valor invalido. Digite novamente: ");
        scanf("%d", &vertices);
    }

    ListaAdj *lista = malloc(vertices * sizeof(ListaAdj));

    for(i = 0; i < vertices; i++){
        printf("\nQuantidade de vizinhos do vertice %d: ", i);
        scanf("%d", &lista[i].quantidade);
        while(lista[i].quantidade < 0 || lista[i].quantidade > vertices){
            printf("Valor invalido. Digite novamente: ");
            scanf("%d", &lista[i].quantidade);
        }
        lista[i].vizinhos = malloc(lista[i].quantidade * sizeof(int));
        for(j = 0; j < lista[i].quantidade; j++){
            scanf("%d", &lista[i].vizinhos[j]);
            while(lista[i].vizinhos[j] < 0 || lista[i].vizinhos[j] >= vertices){
                printf("Vertice invalido. Digite novamente: ");
                scanf("%d", &lista[i].vizinhos[j]);
            }
        }
    }

    int verticeInicial;
    printf("\nDigite o vertice inicial: ");
    scanf("%d", &verticeInicial);
    while(verticeInicial < 0 || verticeInicial >= vertices){
        printf("Vertice invalido. Digite novamente: ");
        scanf("%d", &verticeInicial);
    }

    // BFS
    int *visitado = calloc(vertices, sizeof(int));
    int *distancia = malloc(vertices * sizeof(int));
    int *fila = malloc(vertices * sizeof(int));

    for(i = 0; i < vertices; i++){
        distancia[i] = -1;
    }

    int inicio = 0;
    int fim = 0;

    fila[fim] = verticeInicial;
    fim++;

    visitado[verticeInicial] = 1;
    distancia[verticeInicial] = 0;

    printf("\nOrdem da BFS: ");
    while(inicio < fim){
        int atual = fila[inicio];
        inicio++;

        for(i = 0; i < lista[atual].quantidade; i++){
            int vizinho = lista[atual].vizinhos[i];
            if(visitado[vizinho] == 0){
                visitado[vizinho] = 1;
                distancia[vizinho] = distancia[atual] + 1;
                fila[fim] = vizinho;
                fim++;
            }
        }
    }

    printf("\n");
    printf("\nDistancia a partir do vertice %d:\n", verticeInicial);
    for(i = 0; i < vertices; i++){
        printf("Vertice %d -> %d\n", i, distancia[i]);
    }

    for(i = 0; i < vertices; i++){
        free(lista[i].vizinhos);
    }
    free(lista);
    free(visitado);
    free(distancia);
    free(fila);

    return 0;
}