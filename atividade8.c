#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *vizinhos;
    int quantidade;
} ListaAdjacencia;

int main() {
    int vertices;

    printf("Digite o numero de vertices do grafo simples: ");
    scanf("%d", &vertices);
    while (vertices <= 0) {
        printf("Numero invalido. Digite novamente: ");
        scanf("%d", &vertices);
    }

    if (vertices < 3){
        printf("Grafo nao pode conter ciclo\n");
        return 0;
    }

    ListaAdjacencia *lista = malloc(vertices * sizeof(ListaAdjacencia));

    // Entrada da Lista
    for (int i = 0; i < vertices; i++) {
        printf("\nQuantos vertices estao ligados ao vertice %d? ", i);
        scanf("%d", &lista[i].quantidade);

        while (lista[i].quantidade < 0 || lista[i].quantidade >= vertices-1){
            printf("Invalido! (Maximo %d): ", vertices - 1);   
            scanf("%d", &lista[i].quantidade);
        }
        if (lista[i].quantidade > 0) {
            lista[i].vizinhos = malloc(lista[i].quantidade * sizeof(int));

            printf("Digite os vertices ligados ao vertice %d:\n", i);
            for (int j = 0; j < lista[i].quantidade; j++) {
                scanf("%d", &lista[i].vizinhos[j]);
                while (lista[i].vizinhos[j] < 0 || lista[i].vizinhos[j] >= vertices) {
                    printf("Vertice invalido. Digite novamente: ");
                    scanf("%d", &lista[i].vizinhos[j]);
                }
            }
        }
    }

    // Validação de Grafo Simples
    int eh_simples = 1;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < lista[i].quantidade; j++) {
            int vizinho = lista[i].vizinhos[j];

            if (vizinho == i){
                eh_simples = 0;
            }
        
            int tem_volta = 0;
            for (int k = 0; k < lista[vizinho].quantidade; k++) {
                if (lista[vizinho].vizinhos[k] == i) {
                    tem_volta = 1;
                }
            }
            if (tem_volta == 0) {
                eh_simples = 0;
            }
        }
    }

    if (eh_simples == 0) {
        printf("\nERRO: A lista inserida nao forma um grafo simples.\n");
        
        for (int i = 0; i < vertices; i++) {
            if (lista[i].quantidade > 0) {
                free(lista[i].vizinhos);
            }
        }
        free(lista);
        return 0; 
    }

    int vertice_inicial;
    printf("\nDigite o vertice de onde deseja iniciar a busca (0 a %d): ", vertices - 1);
    scanf("%d", &vertice_inicial);
    
    while (vertice_inicial < 0 || vertice_inicial >= vertices) {
        printf("Vertice invalido. Digite novamente (0 a %d): ", vertices - 1);
        scanf("%d", &vertice_inicial);
    }

    // DFS
    int *visitado = calloc(vertices, sizeof(int));    
    int tem_ciclo = 0;
    int *pilha_v = malloc(vertices * vertices * sizeof(int));
    int *anterior = malloc(vertices * vertices * sizeof(int));
    int topo = 0;

    pilha_v[topo] = vertice_inicial;
    anterior[topo] = -1; 
    topo++;

    while (topo > 0) {
        topo--;
        int atual = pilha_v[topo];
        int anteriorAtual = anterior[topo];

        if (visitado[atual] == 0) {
            visitado[atual] = 1; 

            for (int j = 0; j < lista[atual].quantidade; j++) {
                int vizinho = lista[atual].vizinhos[j];

                if (visitado[vizinho] == 1 && vizinho != anteriorAtual) {
                    tem_ciclo = 1;
                    topo = 0; 
                    break;
                }
                
                if (visitado[vizinho] == 0) {
                    pilha_v[topo] = vizinho;
                    anterior[topo] = atual; 
                    topo++;
                }
            }
        }
    }

    printf("\n--- Resultado DFS ---\n");
    if (tem_ciclo) {
        printf("O grafo simples POSSUI um ciclo acessivel a partir do vertice %d.\n", vertice_inicial);
    } else {
        printf("O grafo simples NAO possui ciclos a partir do vertice %d.\n", vertice_inicial);
    }

    for (int i = 0; i < vertices; i++) {
        if (lista[i].quantidade > 0) free(lista[i].vizinhos);
    }
    free(lista);
    free(visitado); free(pilha_v); free(anterior);

    return 0;
}