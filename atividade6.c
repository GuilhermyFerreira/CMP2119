#include <stdio.h>

int main() {
    int vertice;
    int i, j;

    printf("Digite o numero de vertices do grafo: ");
    scanf("%d", &vertice);
    while(vertice <= 0) {
        printf("Numero invalido, digite um valor maior que 0: ");
        scanf("%d", &vertice);
    }

    int adj[vertice][vertice];
    int graus[vertice];
    int simples = 1;

    printf("Digite a matriz de adjacencia:\n");
    for(i = 0; i < vertice; i++){
        graus[i] = 0;
        for(j = 0; j < vertice; j++){
            scanf("%d", &adj[i][j]);
            while(adj[i][j] != 0 && adj[i][j] != 1) {
                 printf("Valor invalido - digite 0 ou 1\n");
                 scanf("%d", &adj[i][j]);
             }
             graus[i] += adj[i][j];
        }
    }
    for(i = 0; i < j; i++){
        if(adj[i][i] != 0){
            printf("grafo nao e simples\n");
            return 0;
        }
    }

    for(i = 0; i < vertice; i++){
        for(j = 0; j < vertice; j++){
            if(adj[i][j] != adj[j][i]){
                printf("grafo nao e simples\n");
                return 0;
            }
        }
    }

    if(simples == 0) {
        printf("\nO grafo informado não é simples\n");
        return 0;
    }

    int impares = 0;
    for(i = 0; i < vertice; i++){
        if(graus[i] % 2 != 0) {
            impares++;
        }
    }

    printf("\n");
    if(impares == 0) {
        printf("O grafo possui ciclo euleriano\n");
    } else if(impares == 2) {
        printf("O grafo possui caminho euleriano\n");
    } else {
        printf("O grafo não possui caminho nem ciclo euleriano\n");
    }

    return 0;
}