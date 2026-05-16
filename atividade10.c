#include <stdio.h>

int main() {

    int v, i, j, k, p;

    printf("Digite a quantidade de vertices: ");
    scanf("%d", &v);

    while(v <= 0){
        printf("Valor invalido. Digite novamente: ");
        scanf("%d", &v);
    }

    int A[v][v];

    printf("\nDigite a matriz de adjacencia:\n");

    for(i = 0; i < v; i++){
        for(j = 0; j < v; j++){

            scanf("%d", &A[i][j]);

            while(A[i][j] != 0 && A[i][j] != 1){
                printf("Valor invalido. Digite 0 ou 1: ");
                scanf("%d", &A[i][j]);
            }
        }
    }

    // -------- Validacao de grafo simples --------

    for(i = 0; i < v; i++){

        // laco
        if(A[i][i] != 0){
            printf("\nO grafo nao e simples (possui laco)\n");
            return 0;
        }

        // simetria
        for(j = 0; j < v; j++){

            if(A[i][j] != A[j][i]){
                printf("\nO grafo nao e simples (nao direcionado)\n");
                return 0;
            }
        }
    }

    // matriz resultado começa sendo A
    int resultado[v][v];

    for(i = 0; i < v; i++){
        for(j = 0; j < v; j++){
            resultado[i][j] = A[i][j];
        }
    }

    // matriz acumuladora
    int acumulada[v][v];

    for(i = 0; i < v; i++){
        for(j = 0; j < v; j++){
            acumulada[i][j] = A[i][j];
        }
    }

    // -------- Calcula A² até A^(v-1) --------

    for(p = 2; p <= v - 1; p++){

        int temp[v][v];

        // multiplicacao de matrizes
        for(i = 0; i < v; i++){

            for(j = 0; j < v; j++){

                temp[i][j] = 0;

                for(k = 0; k < v; k++){

                    temp[i][j] += resultado[i][k] * A[k][j];
                }
            }
        }

        // copia temp para resultado
        for(i = 0; i < v; i++){
            for(j = 0; j < v; j++){

                resultado[i][j] = temp[i][j];

                // soma na acumuladora
                acumulada[i][j] += resultado[i][j];
            }
        }

        // mostrar matriz da potencia atual
        printf("\nA^%d:\n", p);

        for(i = 0; i < v; i++){
            for(j = 0; j < v; j++){

                printf("%4d", resultado[i][j]);
            }
            printf("\n");
        }
    }

    // -------- Verifica conectividade --------

    int conexo = 1;

    for(i = 0; i < v; i++){

        for(j = 0; j < v; j++){

            // ignora diagonal principal
            if(i != j && acumulada[i][j] == 0){

                conexo = 0;
            }
        }
    }

    printf("\nMatriz acumulada:\n");

    for(i = 0; i < v; i++){
        for(j = 0; j < v; j++){

            printf("%4d", acumulada[i][j]);
        }
        printf("\n");
    }

    if(conexo)
        printf("\nO grafo e conexo.\n");
    else
        printf("\nO grafo nao e conexo.\n");

    return 0;
}