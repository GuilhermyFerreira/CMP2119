#include <stdio.h>

int main() {
    int vertice;
    int i, j;

    // 1) LER E VALIDAR VÉRTICES
    printf("Digite o numero de vertices do grafo: ");
    scanf("%d", &vertice);
    while(vertice <= 0) {
        printf("Numero invalido, digite um valor maior que 0: ");
        scanf("%d", &vertice);
    }

    int adj[vertice][vertice];
    int graus[vertice];
    int simples = 1;

    // 2) LER MATRIZ E VALIDAR GRAFO SIMPLES
    printf("Digite a matriz de adjacencia:\n");
    for(i = 0; i < vertice; i++){
        graus[i] = 0; // Zera o grau para garantir
        for(j = 0; j < vertice; j++){
            scanf("%d", &adj[i][j]);
            
            // Aceita apenas 0 ou 1
            while(adj[i][j] != 0 && adj[i][j] != 1) {
                 printf("Valor invalido - digite 0 ou 1\n");
                 scanf("%d", &adj[i][j]);
             }
             
             // Não pode ter laço na diagonal principal
             if(i == j && adj[i][j] == 1) {
                 simples = 0; 
             }
             
             // Soma os graus
             graus[i] += adj[i][j];
        }
    }

    if(simples == 0) {
        printf("\nO grafo informado não é simples\n");
        return 0;
    }

    // 3) A LÓGICA DE EULER (Contar vértices de grau Ímpar)
    int impares = 0;
    for(i = 0; i < vertice; i++){
        if(graus[i] % 2 != 0) {
            impares++;
        }
    }

    // 4) RESULTADOS EXATOS
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