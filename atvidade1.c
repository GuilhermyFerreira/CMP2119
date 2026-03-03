#include <stdio.h>

#define MAX 5

int main() {
    int matriz[MAX][MAX];
    int n, i, j;

    printf("escreva o numero de vertices (max %d): ", MAX);
    scanf("%d", &n);

    while (n > MAX || n < 1) {
        printf("tamanho invalido.\n");
        printf("escreva o numero de vertices (max %d): ", MAX);
        scanf("%d", &n);
    }

    printf("digite a matriz (0 ou 1):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("posicao [%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);

            while (matriz[i][j] != 0 && matriz[i][j] != 1) {
                printf("apenas 0 ou 1 sao permitidos.\n");
                printf("posicao [%d][%d]: ", i, j);
                scanf("%d", &matriz[i][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matriz[i][j] != matriz[j][i]) {
                printf("matriz nao e simetrica.\n");
                return 1;
            }
        }
    }
         
        for (i = 0; i < n; i++) {
            int grau = 0;
            for (j = 0; j < n; j++) {
                if (matriz[i][j] == 1) {
                    grau++;
                }
            }
            printf("vertice %d tem grau: %d\n", i, grau);
        }

}