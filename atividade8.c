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

    ListaAdjacencia *lista = malloc(vertices * sizeof(ListaAdjacencia));

    // Entrada da Lista
    for (int i = 0; i < vertices; i++) {
        printf("\nQuantos vertices estao ligados ao vertice %d? ", i);
        scanf("%d", &lista[i].quantidade);

        while (lista[i].quantidade < 0 || lista[i].quantidade >= vertices){
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
        } //else {
            //lista[i].vizinhos = NULL;
        //}
    }

    // Validação de Grafo Simples usando a sua Struct
    int eh_simples = 1;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < lista[i].quantidade; j++) {
            int vizinho = lista[i].vizinhos[j];

            // 1. Checa Laço
            if (vizinho == i){
                eh_simples = 0;
            }
        
            // 2. Checa Simetria
            int tem_volta = 0;
            for (int k = 0; k < lista[vizinho].quantidade; k++) {
                if (lista[vizinho].vizinhos[k] == i) tem_volta = 1;
            }
            if (tem_volta == 0) eh_simples = 0;
        }
    }

    if (eh_simples == 0) {
        printf("\nERRO: A lista inserida nao forma um grafo simples.\n");
        
        // Limpa antes de sair
        for (int i = 0; i < vertices; i++) {
            if (lista[i].quantidade > 0) {
                free(lista[i].vizinhos);
            }
        }
        free(lista);
        return 0; 
    }

    // Lógica do DFS Iterativo (Grafo Simples com Pilha Dupla)
    int *visitado = calloc(vertices, sizeof(int));
    
    int tem_ciclo = 0;
    int *pilha_v = malloc(vertices * vertices * sizeof(int));
    int *pilha_pai = malloc(vertices * vertices * sizeof(int));
    int topo = 0;

    for (int inicio = 0; inicio < vertices; inicio++) {
        if (visitado[inicio] == 0 && tem_ciclo == 0) {
            
            pilha_v[topo] = inicio;
            pilha_pai[topo] = -1; // Sem pai
            topo++;

            while (topo > 0) {
                topo--;
                int atual = pilha_v[topo];
                int pai_do_atual = pilha_pai[topo];

                if (visitado[atual] == 0) {
                    visitado[atual] = 1; 

                    // MUDANÇA: Percorre os vizinhos usando a sua struct
                    for (int j = 0; j < lista[atual].quantidade; j++) {
                        int vizinho = lista[atual].vizinhos[j];
                        
                        // Achou um visitado que NÃO é o pai
                        if (visitado[vizinho] == 1 && vizinho != pai_do_atual) {
                            tem_ciclo = 1;
                            topo = 0; 
                            break;
                        }
                        
                        if (visitado[vizinho] == 0) {
                            pilha_v[topo] = vizinho;
                            pilha_pai[topo] = atual; 
                            topo++;
                        }
                    }
                }
            }
        }
    }

    printf("\n--- Resultado DFS ---\n");
    if (tem_ciclo) printf("O grafo simples POSSUI um ciclo.\n");
    else printf("O grafo simples NAO possui ciclos.\n");

    // Limpeza de Memória
    for (int i = 0; i < vertices; i++) {
        if (lista[i].quantidade > 0) free(lista[i].vizinhos);
    }
    free(lista);
    free(visitado); free(pilha_v); free(pilha_pai);

    return 0;
}