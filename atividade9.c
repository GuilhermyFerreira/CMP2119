#include <stdio.h>

int main() {
    int n, i, j, k;

    printf("Quantos vertices o grafo tem? ");
    scanf("%d", &n);

    while (n <= 0) {
        printf("Valor invalido. Digite novamente: ");
        scanf("%d",&n);
    }

    int grafo[n][n];

    printf("\nDigite a matriz de adjacencia (0 ou 1):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &grafo[i][j]);

            while(grafo[i][j] != 0 && grafo[i][j] != 1){
                printf("Valor invalido. Digite 0 ou 1: ");
                scanf("%d", &grafo[i][j]);
            }
        }
    }

    // Validação de Grafo Simples
    for (i = 0; i < n; i++) {
        if (grafo[i][i] != 0) {
            printf("\nO grafo nao e simples (possui laco).\n");
            return 0;
        }

        for (j = 0; j < n; j++) {
            if (grafo[i][j] != grafo[j][i]) {
                printf("\nO grafo nao e simples (nao e simetrico).\n");
                return 0;
            }
        }
    }

    int encontrou = 0;

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            for (k = j + 1; k < n; k++) {
                
                if (grafo[i][j] == 1 && grafo[i][k] == 1 && grafo[j][k] == 1) {
                    encontrou = 1;
                    printf("\nClique de tamanho 3 encontrado entre os vertices: %d, %d e %d\n", i + 1, j + 1, k + 1);
                }
            }
        }
    }

    if (encontrou==0) {
        printf("\nO grafo nao possui nenhum clique de tamanho 3.\n");
    }

    return 0;
}