#include <stdio.h>

int main() {
    int vertice1, vertice2;
    int i, j;

    // 1) LER GRAFO 1
    printf("Digite o numero de vertices do grafo 1: ");
    scanf("%d", &vertice1);
    while(vertice1 <= 0) {
        printf("Numero invalido, digite um valor maior que 0: ");
        scanf("%d", &vertice1);
    }

    int g1[vertice1][vertice1]; // Criando a matriz dinamicamente sem ponteiro

    printf("Digite a matriz de adjacencia do grafo 1:\n");
    for(i = 0; i < vertice1; i++){
        for(j = 0; j < vertice1; j++){
            scanf("%d", &g1[i][j]);
            while(g1[i][j] != 0 && g1[i][j] != 1) {
                 printf("Valor invalido - digite 0 ou 1\n");
                 scanf("%d", &g1[i][j]);
             }
        }
    }

    // 2) LER GRAFO 2
    printf("\nDigite o numero de vertices do grafo 2: ");
    scanf("%d", &vertice2);
    while(vertice2 <= 0) {
        printf("Numero invalido, digite um valor maior que 0: ");
        scanf("%d", &vertice2);
    }

    int g2[vertice2][vertice2];

    printf("Digite a matriz de adjacencia do grafo 2:\n");
    for(i = 0; i < vertice2; i++){
        for(j = 0; j < vertice2; j++){
            scanf("%d", &g2[i][j]);
            while(g2[i][j] != 0 && g2[i][j] != 1) {
                 printf("Valor invalido - digite 0 ou 1\n");
                 scanf("%d", &g2[i][j]);
             }
        }
    }

    // --- TESTE 1: Número de vértices ---
    if(vertice1 != vertice2){
        printf("\nNao sao isomorfos - Numero de vertices diferente\n");
        return 0;
    }

    // --- TESTE 2: Número de arestas ---
    int e1 = 0, e2 = 0;
    for(i = 0; i < vertice1; i++){
        for(j = 0; j < vertice1; j++){
            if(g1[i][j] == 1) e1++;
            if(g2[i][j] == 1) e2++;
        }
    }
    
    // Divide por 2 porque a matriz conta ida e volta
    e1 = e1 / 2;
    e2 = e2 / 2;

    if(e1 != e2){
        printf("\nNao sao isomorfos - Numero de arestas diferente\n");
        return 0;
    }

    // --- TESTE 3: Sequência de Graus ---
    int grau1[vertice1], grau2[vertice1];
    for(i = 0; i < vertice1; i++){
        grau1[i] = 0;
        grau2[i] = 0;
        for(j = 0; j < vertice1; j++){
            grau1[i] += g1[i][j];
            grau2[i] += g2[i][j];
        }
    }

    // Ordenar os graus do menor para o maior (Bubble Sort)
    for(i = 0; i < vertice1 - 1; i++){
        for(j = 0; j < vertice1 - 1; j++){
            if(grau1[j] > grau1[j+1]){
                int temp = grau1[j];
                grau1[j] = grau1[j+1];
                grau1[j+1] = temp;
            }
            if(grau2[j] > grau2[j+1]){
                int temp = grau2[j];
                grau2[j] = grau2[j+1];
                grau2[j+1] = temp;
            }
        }
    }

    // Comparar os graus ordenados
    for(i = 0; i < vertice1; i++){
        if(grau1[i] != grau2[i]){
            printf("\nNao sao isomorfos - Sequencia de graus diferente\n");
            return 0;
        }
    }

    // Se sobreviveu a todos os testes
    printf("\nOs grafos PODEM ser isomorfos\n");

    return 0;
}