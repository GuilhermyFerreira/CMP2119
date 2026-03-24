#include <stdio.h>
#include <stdlib.h>
//Ciclo Euleriano

int main() {
    int v;
    printf("Digite o numero de vertices: ");
    scanf("%d", &v);

    int **adj = malloc(v * sizeof(int *));
    int *graus = calloc(v, sizeof(int));
    int simples = 1;

    printf("Digite a matriz de adjacencia:\n");
    for (int i = 0; i < v; i++) {
        adj[i] = malloc(v * sizeof(int));
        for (int j = 0; j < v; j++) {
            scanf("%d", &adj[i][j]);

            // Validação de Grafo Simples
            if (adj[i][j] != 0 && adj[i][j] != 1) {
                simples = 0; // Se tiver número > 1, tem arestas múltiplas
            }
            if (i == j && adj[i][j] != 0) {
                simples = 0; // Se a diagonal principal não for 0, tem laço
            }
            
            // Calculando o grau
            if (adj[i][j] == 1) graus[i]++;
        }
    }

    // Se falhar na validação, exibe a mensagem exata e encerra
    if (!simples) {
        printf("\nO grafo informado não é simples\n");
        return 0; 
    }

    // Contando quantos vértices têm grau ímpar
    int impares = 0;
    for (int i = 0; i < v; i++) {
        if (graus[i] % 2 != 0) {
            impares++;
        }
    }

    // Exibindo os resultados exatos conforme a imagem
    printf("\n");
    if (impares == 0) {
        printf("O grafo possui ciclo euleriano\n");
    } else if (impares == 2) {
        printf("O grafo possui caminho euleriano\n");
    } else {
        printf("O grafo não possui caminho nem ciclo euleriano\n");
    }

    // Limpeza
    for (int i = 0; i < v; i++) free(adj[i]);
    free(adj);
    free(graus);

    return 0;
}