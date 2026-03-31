#include <stdio.h>

int main() {
    int v, i, j;

    printf("Introduza o numero de vertices do grafo simples: ");
    scanf("%d", &v);
    while(v <= 0) {
        printf("Invalido. Introduza um valor maior que 0: ");
        scanf("%d", &v);
    }

    int quantidade[v];
    int lista[v][v];

    // 1) LER A LISTA DE ADJACÊNCIA
    printf("\n--- Preenchimento da Lista de Adjacencia ---\n");
    for(i = 0; i < v; i++) {
        printf("Quantos vizinhos o vertice %d tem? ", i);
        scanf("%d", &quantidade[i]);
        while(quantidade[i] < 0 || quantidade[i] >= v) {
            printf("Invalido! (Num grafo simples, o maximo de vizinhos e %d): ", v-1);
            scanf("%d", &quantidade[i]);
        }

        if(quantidade[i] > 0) {
            printf("Digite os %d vizinhos do vertice %d: ", quantidade[i], i);
            for(j = 0; j < quantidade[i]; j++) {
                scanf("%d", &lista[i][j]);
            }
        }
    }

    // 2) VALIDAÇÃO DE GRAFO SIMPLES
    int eh_simples = 1;
    for(i = 0; i < v; i++) {
        for(j = 0; j < quantidade[i]; j++) {
            int vizinho = lista[i][j];

            // Verificacao 1: Laço (Aponta para si mesmo)
            if(vizinho == i) eh_simples = 0;

            // Verificacao 2: Aresta Múltipla (Vizinho repetido na mesma lista)
            for(int k = j + 1; k < quantidade[i]; k++) {
                if(lista[i][k] == vizinho) eh_simples = 0;
            }

            // Verificacao 3: Simetria (Se 'i' aponta para 'vizinho', o 'vizinho' tem de apontar para 'i')
            int tem_volta = 0;
            for(int k = 0; k < quantidade[vizinho]; k++) {
                if(lista[vizinho][k] == i) tem_volta = 1;
            }
            if(tem_volta == 0) eh_simples = 0;
        }
    }

    if (eh_simples == 0) {
        printf("\nERRO: A lista inserida nao forma um grafo simples.\n");
        printf("(Verifique se existem lacos, repeticoes ou se esqueceu de colocar a volta de alguma aresta).\n");
        return 0; 
    }

    // 3) DFS ITERATIVA COM PILHA DUPLA
    int visitado[v];
    for(i = 0; i < v; i++) visitado[i] = 0;

    int tem_ciclo = 0;

    int pilha_v[v * v];
    int pilha_pai[v * v]; 
    int topo = 0;

    for(int inicio = 0; inicio < v; inicio++) {
        if(visitado[inicio] == 0 && tem_ciclo == 0) {
            
            pilha_v[topo] = inicio;
            pilha_pai[topo] = -1; // Sem pai
            topo++;

            while(topo > 0) {
                topo--;
                int atual = pilha_v[topo];
                int pai_do_atual = pilha_pai[topo];

                if(visitado[atual] == 0) {
                    visitado[atual] = 1; 

                    // MUDANÇA AQUI: Percorre apenas a lista do vértice
                    for (int k = 0; k < quantidade[atual]; k++) {
                        int vizinho = lista[atual][k];
                        
                        // Encontrou um visitado que NÃO é o pai (é um ciclo!)
                        if (visitado[vizinho] == 1 && vizinho != pai_do_atual) {
                            tem_ciclo = 1;
                            topo = 0; // Esvazia para sair
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

    printf("\n--- Resultado DFS Simples ---\n");
    if (tem_ciclo) printf("O grafo simples POSSUI um ciclo.\n");
    else printf("O grafo simples NAO possui ciclos.\n");

    return 0;
}