#include <stdio.h>
#include <stdlib.h>

// Sua Struct Original
typedef struct {
    int *vizinhos;
    int quantidade;
} ListaAdjacencia;

int main() {
    int vertices;

    printf("Digite o numero de vertices do grafo direcionado: ");
    scanf("%d", &vertices);
    while (vertices <= 0) {
        printf("Numero invalido. Digite novamente: ");
        scanf("%d", &vertices);
    }

    if (vertices < 3) {
        printf("Grafo nao pode conter ciclo (considerando ciclos simples de 3+ vertices)\n");
        return 0;
    }

    ListaAdjacencia *lista = malloc(vertices * sizeof(ListaAdjacencia));

    // Entrada da Lista
    for (int i = 0; i < vertices; i++) {
        printf("\nQuantos vertices estao ligados ao vertice %d? ", i);
        scanf("%d", &lista[i].quantidade);

        while (lista[i].quantidade < 0 || lista[i].quantidade > vertices - 1){
            printf("Quantidade invalida. Tente novamente: ");   
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

    int vertice_inicial;
    printf("\nDigite o vertice de onde deseja iniciar a busca (0 a %d): ", vertices - 1);
    scanf("%d", &vertice_inicial);
    
    while (vertice_inicial < 0 || vertice_inicial >= vertices) {
        printf("Vertice invalido. Digite novamente (0 a %d): ", vertices - 1);
        scanf("%d", &vertice_inicial);
    }

    // DFS
    int *visitado = calloc(vertices, sizeof(int));
    int *na_trilha = calloc(vertices, sizeof(int));
    
    int tem_ciclo = 0;
    int *pilha = malloc(vertices * 2 * sizeof(int));
    int *acoes = malloc(vertices * 2 * sizeof(int));
    int topo = 0;
    
    pilha[topo] = vertice_inicial;
    acoes[topo] = 0; 
    topo++;

    while (topo > 0) {
        topo--;
        int atual = pilha[topo];
        int acao = acoes[topo];

        if (acao == 1) {
            na_trilha[atual] = 0; // Tira da trilha
        }
        else if (visitado[atual] == 0) {
            visitado[atual] = 1;  
            na_trilha[atual] = 1;

            pilha[topo] = atual;
            acoes[topo] = 1;
            topo++;

            for (int j = 0; j < lista[atual].quantidade; j++) {
                int vizinho = lista[atual].vizinhos[j];
                
                if (na_trilha[vizinho] == 1) {
                    tem_ciclo = 1; 
                    topo = 0; 
                    break;
                }
                
                if (visitado[vizinho] == 0) {
                    pilha[topo] = vizinho;
                    acoes[topo] = 0;
                    topo++;
                }
            }
        }
    }

    printf("\n--- Resultado DFS ---\n");
    if (tem_ciclo) {
        printf("O grafo direcionado POSSUI um ciclo acessivel a partir do vertice %d.\n", vertice_inicial);
    } else {
        printf("O grafo direcionado NAO possui ciclos a partir do vertice %d.\n", vertice_inicial);
    }

    for (int i = 0; i < vertices; i++) {
        if (lista[i].quantidade > 0) free(lista[i].vizinhos);
    }
    free(lista);
    free(visitado); free(na_trilha); free(pilha); free(acoes);

    return 0;
}