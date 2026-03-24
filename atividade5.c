#include <stdio.h>

int main(){
    int num_vertices, linha, coluna;

    // Pedindo a quantidade de vértices
    printf("Informe a quantidade de vertices do grafo: ");
    scanf("%d", &num_vertices);
    
    while(num_vertices <= 0) {
        printf("Quantidade invalida! Digite um numero estritamente positivo:\n");
        scanf("%d", &num_vertices);
    }

    // Usando VLA para criar a matriz com o tamanho exato
    int grafo[num_vertices][num_vertices];

    printf("Preencha a matriz de adjacencia:\n");

    for(linha = 0; linha < num_vertices; linha++){
        for(coluna = 0; coluna < num_vertices; coluna++){
            scanf("%d", &grafo[linha][coluna]);
            
            // Validação de entrada
            while(grafo[linha][coluna] != 0 && grafo[linha][coluna] != 1) {
                 printf("Erro: Para grafos simples, utilize apenas 0 ou 1.\n");
                 printf("Insira o valor novamente:\n");
                 scanf("%d", &grafo[linha][coluna]);
             }
        }
    }

    // Calculando a quantidade de conexões (grau) de cada vértice
    int conexoes[num_vertices];
    
    for(linha = 0; linha < num_vertices; linha++){
        conexoes[linha] = 0;
        for(coluna = 0; coluna < num_vertices; coluna++){
            conexoes[linha] += grafo[linha][coluna];
        }
    }

    // --- Verificacao: Grafo Ciclo ---
    int eh_ciclo = 1;

    if(num_vertices < 3) eh_ciclo = 0;

    for(linha = 0; linha < num_vertices; linha++){
        if(conexoes[linha] != 2){
            eh_ciclo = 0;
        }
    }

    // --- Verificacao: Grafo Completo ---
    int eh_completo = 1;

    for(linha = 0; linha < num_vertices; linha++){
        if(conexoes[linha] != num_vertices - 1){
            eh_completo = 0;
        }
    }

    // --- Verificacao: Grafo Roda ---
    int eh_roda = 1;
    int eixo = 0; // Contabiliza quem é o centro da roda

    for(linha = 0; linha < num_vertices; linha++){
        if(conexoes[linha] == num_vertices - 1){
            eixo++;
        }
    }

    if(eixo != 1){
        eh_roda = 0;
    } else {
        for(linha = 0; linha < num_vertices; linha++){
            if(conexoes[linha] != num_vertices - 1 && conexoes[linha] != 3){
                eh_roda = 0;
            }
        }
    }

    // --- Exibindo os Resultados ---
    printf("\n--- Resultados da Analise ---\n");
    
    if(eh_ciclo)
        printf("Classificacao: Grafo Ciclo\n");
    else
        printf("O grafo NAO e um Ciclo\n");

    if(eh_completo)
        printf("Classificacao: Grafo Completo\n");
    else
        printf("O grafo NAO e Completo\n");

    if(eh_roda)
        printf("Classificacao: Grafo Roda\n");
    else
        printf("O grafo NAO e uma Roda\n");

    return 0;
}