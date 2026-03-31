#include <stdio.h>

int main() {
    int v, i, j;

    printf("Introduza o numero de vertices do grafo direcionado: ");
    scanf("%d", &v);
    while(v <= 0) {
        printf("Invalido. Introduza um valor maior que 0: ");
        scanf("%d", &v);
    }

    // A nossa Lista de Adjacência sem ponteiros
    int quantidade[v];
    int lista[v][v];

    printf("\n--- Preenchimento da Lista de Adjacencia ---\n");
    for(i = 0; i < v; i++) {
        printf("Quantos vizinhos o vertice %d tem? ", i);
        scanf("%d", &quantidade[i]);
        
        while(quantidade[i] < 0 || quantidade[i] > v) {
            printf("Invalido! O numero deve ser entre 0 e %d: ", v);
            scanf("%d", &quantidade[i]);
        }

        if(quantidade[i] > 0) {
            printf("Digite os %d vizinhos do vertice %d (separados por espaco): ", quantidade[i], i);
            for(j = 0; j < quantidade[i]; j++) {
                scanf("%d", &lista[i][j]);
                // Valida se o vizinho existe
                while(lista[i][j] < 0 || lista[i][j] >= v) {
                    printf("Vertice invalido! Digite um vizinho entre 0 e %d: ", v-1);
                    scanf("%d", &lista[i][j]);
                }
            }
        }
    }

    int visitado[v];
    int na_trilha[v]; // Marca quem está no caminho atual
    for(i = 0; i < v; i++) {
        visitado[i] = 0;
        na_trilha[i] = 0;
    }

    int tem_ciclo = 0;

    // A nossa Pilha Iterativa (Tamanho máximo = v * 2)
    int pilha[v * 2];
    int acoes[v * 2]; 
    int topo = 0;

    // Inicia a DFS
    for(int inicio = 0; inicio < v; inicio++) {
        if(visitado[inicio] == 0 && tem_ciclo == 0) {
            
            pilha[topo] = inicio;
            acoes[topo] = 0; // Ação 0: Entrar/Explorar
            topo++;

            while(topo > 0) {
                topo--;
                int atual = pilha[topo];
                int acao = acoes[topo];

                if(acao == 1) {
                    // Ação 1: Já terminamos de explorar, tira da trilha
                    na_trilha[atual] = 0;
                } 
                else if (visitado[atual] == 0) {
                    visitado[atual] = 1;  
                    na_trilha[atual] = 1;

                    // Re-empilha para tirar da trilha no final
                    pilha[topo] = atual;
                    acoes[topo] = 1;
                    topo++;

                    // MUDANÇA AQUI: Percorremos apenas a lista de vizinhos do vértice atual!
                    for (int k = 0; k < quantidade[atual]; k++) {
                        int vizinho = lista[atual][k];
                        
                        if (na_trilha[vizinho] == 1) {
                            tem_ciclo = 1; // Encontramos um ciclo!
                            topo = 0; // Força a saída do While
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
        }
    }

    printf("\n--- Resultado DFS Direcionado ---\n");
    if (tem_ciclo) printf("O grafo direcionado POSSUI um ciclo.\n");
    else printf("O grafo direcionado NAO possui ciclos.\n");

    return 0;
}