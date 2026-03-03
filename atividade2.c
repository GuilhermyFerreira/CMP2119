#include <stdio.h>

int main() {
    int num_v, num_a, i, j;
    
    printf("Digite o numero de vertices: ");
    scanf("%d", &num_v);
    printf("Digite o numero de arestas: ");
    scanf("%d", &num_a);
    int inc[num_v][num_a];
    int adj[num_v][num_v];
    
    printf("\nPreencha a matriz de incidencia:\n(Use 1 se a seta sai, -1 se a seta entra, 0 se nada)\n");
    for(i = 0; i < num_v; i++) {
        for(j = 0; j < num_a; j++) {
            printf("Vertice %d, Aresta %d: ", i, j);
            scanf("%d", &inc[i][j]);

            while(inc[i][j] != 1 && inc[i][j] != -1 && inc[i][j] != 0) {
                printf("valor invalido! Use apenas 1, -1 ou 0.\n");
                scanf("%d", &inc[i][j]);
            }
        }
    }

    for(j = 0; j < num_a; j++) {   
        int conta_origem = 0, conta_destino = 0;    
        for(i = 0; i < num_v; i++) {
            if(inc[i][j] == 1) conta_origem++;
            if(inc[i][j] == -1) conta_destino++;
        }
        if(conta_origem != 1 || conta_destino != 1) {
            printf("Toda aresta precisa de exatamente uma origem (1) e um destino (-1).\n");
            return 1;
        }
    }

    printf("\nGraus dos Vertices\n");
    for(i = 0; i < num_v; i++) {
        int grau_entrada = 0, grau_saida = 0;
        for(j = 0; j < num_a; j++) {
            if(inc[i][j] == -1) grau_entrada++;
            if(inc[i][j] == 1) grau_saida++;
        }
        printf("Vertice %d = Grau Entrada: %d | Grau Saida: %d\n", i, grau_entrada, grau_saida);
    }

    for (i = 0; i < num_v; i++) {
        for(j = 0; j < num_v; j++) {
            adj[i][j] = 0;
        }
    }

    for(j = 0; j < num_a; j++) {
        int origem = -1, destino =-1;
        
        for(i = 0; i < num_v; i++) {
            if(inc[i][j] == 1) origem = i;
            if(inc[i][j] == -1) destino = i;
        }
        if(origem != -1 && destino != -1) {
            adj[origem][destino] = 1;
        }
    }

    printf("\nMatriz de Adjacencia Convertida\n");
    for(i = 0; i < num_v; i++) {
        for(j = 0; j < num_v; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    return 0;
}