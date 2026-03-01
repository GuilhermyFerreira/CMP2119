#include <stdio.h>

#define MAX_V 10 // Limite máximo de Vértices
#define MAX_A 20 // Limite máximo de Arestas

int main() {
    int inc[MAX_V][MAX_A];       // Matriz de Incidência
    int adj[MAX_V][MAX_V] = {0}; // Matriz de Adjacência (inicializada com zeros)
    int num_v, num_a, i, j;

    // --- ENTRADA DE DADOS BÁSICA ---
    printf("Digite o numero de vertices (max %d): ", MAX_V);
    scanf("%d", &num_v);
    printf("Digite o numero de arestas (max %d): ", MAX_A);
    scanf("%d", &num_a);

    // 1. LER MATRIZ DE INCIDÊNCIA E VALIDAR VALORES
    printf("\nPreencha a matriz de incidencia:\n(Use 1 se a seta SAI, -1 se a seta ENTRA, 0 se NADA)\n");
    for(i = 0; i < num_v; i++) {
        for(j = 0; j < num_a; j++) {
            printf("Vertice %d, Aresta %d: ", i, j);
            scanf("%d", &inc[i][j]);
            
            // Validação 1: Só pode ser 1, -1 ou 0
            if(inc[i][j] != 1 && inc[i][j] != -1 && inc[i][j] != 0) {
                printf("Erro: Valor invalido! Use apenas 1, -1 ou 0.\n");
                return 1;
            }
        }
    }

    // 2. VALIDAÇÃO ESTRUTURAL DA INCIDÊNCIA
    // Uma aresta (coluna) em um grafo direcionado comum obrigatoriamente
    // tem que ter exatamente UMA origem (1) e UM destino (-1).
    for(j = 0; j < num_a; j++) { // Percorre as colunas (arestas)
        int conta_origem = 0, conta_destino = 0;
        for(i = 0; i < num_v; i++) { // Percorre as linhas (vértices)
            if(inc[i][j] == 1) conta_origem++;
            if(inc[i][j] == -1) conta_destino++;
        }
        
        if(conta_origem != 1 || conta_destino != 1) {
            printf("\nERRO DE VALIDACAO: A aresta %d esta mal formada.\n", j);
            printf("Toda aresta precisa de exatamente uma origem (1) e um destino (-1).\n");
            return 1;
        }
    }

    // 3. MOSTRAR LISTA DE GRAUS (Entrada e Saída)
    printf("\n--- Graus dos Vertices ---\n");
    for(i = 0; i < num_v; i++) {
        int grau_entrada = 0, grau_saida = 0;
        for(j = 0; j < num_a; j++) {
            if(inc[i][j] == -1) grau_entrada++; // -1 significa que a seta entra aqui
            if(inc[i][j] == 1) grau_saida++;    // 1 significa que a seta sai daqui
        }
        printf("Vertice %d -> Grau Entrada: %d | Grau Saida: %d\n", i, grau_entrada, grau_saida);
    }

    // 4. CONVERSÃO: INCIDÊNCIA -> ADJACÊNCIA
    // A lógica: Para cada aresta (coluna), achamos quem é a origem e quem é o destino.
    // Depois, vamos na matriz de adjacência e marcamos [origem][destino] = 1.
    for(j = 0; j < num_a; j++) {
        int origem = -1, destino = -1;
        
        for(i = 0; i < num_v; i++) {
            if(inc[i][j] == 1) origem = i;
            if(inc[i][j] == -1) destino = i;
        }
        
        // Se achou os dois pontas, marca na matriz de adjacência
        if(origem != -1 && destino != -1) {
            adj[origem][destino] = 1;
        }
    }

    // 5. IMPRIMIR MATRIZ DE ADJACÊNCIA CONVERTIDA
    printf("\n--- Matriz de Adjacencia Convertida ---\n");
    for(i = 0; i < num_v; i++) {
        for(j = 0; j < num_v; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n"); // Quebra a linha após imprimir todas as colunas de uma linha
    }

    return 0;
}
