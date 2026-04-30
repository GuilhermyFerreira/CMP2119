#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *vizinhos;
    int quantidade;
} ListaAdj;

int main(){

    int v, i, j;

    printf("Digite a quantidade de vertices: ");
    scanf("%d", &v);

    while(v <= 0){
        printf("Valor invalido. Digite novamente: ");
        scanf("%d", &v);
    }

    ListaAdj *lista = malloc(v * sizeof(ListaAdj));

    // Entrada da lista
    for(i = 0; i < v; i++){

        printf("\nQuantidade de vizinhos do vertice %d: ", i);
        scanf("%d", &lista[i].quantidade);

        while(lista[i].quantidade < 0 || lista[i].quantidade > v){
            printf("Valor invalido. Digite novamente: ");
            scanf("%d", &lista[i].quantidade);
        }

        lista[i].vizinhos = malloc(lista[i].quantidade * sizeof(int));

        for(j = 0; j < lista[i].quantidade; j++){

            scanf("%d", &lista[i].vizinhos[j]);

            while(lista[i].vizinhos[j] < 0 || lista[i].vizinhos[j] >= v){
                printf("Vertice invalido. Digite novamente: ");
                scanf("%d", &lista[i].vizinhos[j]);
            }
        }
    }

    int inicio;

    printf("\nDigite o vertice inicial: ");
    scanf("%d", &inicio);

    while(inicio < 0 || inicio >= v){
        printf("Vertice invalido. Digite novamente: ");
        scanf("%d", &inicio);
    }

    // BFS
    int *visit = calloc(v, sizeof(int));
    int *dist = malloc(v * sizeof(int));
    int *fila = malloc(v * sizeof(int));

    for(i = 0; i < v; i++){
        dist[i] = -1;
    }

    int comeco = 0;
    int fim = 0;

    fila[fim] = inicio;
    fim++;

    visit[inicio] = 1;
    dist[inicio] = 0;

    printf("\nOrdem da BFS: ");

    while(comeco < fim){

        int atual = fila[comeco];
        comeco++;

        // imprime ordem de visita
        printf("%d ", atual);

        for(i = 0; i < lista[atual].quantidade; i++){

            int vizinho = lista[atual].vizinhos[i];

            if(visit[vizinho] == 0){

                visit[vizinho] = 1;
                dist[vizinho] = dist[atual] + 1;

                fila[fim] = vizinho;
                fim++;
            }
        }
    }

    printf("\n");

    printf("\nDistancia a partir do vertice %d:\n", inicio);

    for(i = 0; i < v; i++){
        printf("Vertice %d -> %d\n", i, dist[i]);
    }

    // liberar memória
    for(i = 0; i < v; i++){
        free(lista[i].vizinhos);
    }

    free(lista);
    free(visit);
    free(dist);
    free(fila);

    return 0;
}