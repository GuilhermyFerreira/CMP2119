import java.util.Scanner;

class ListaAdjacenciaSimples {
    int[] vizinhos;
    int quantidade;
}

public class GrafoSimples {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int vertices;

        System.out.print("Digite o numero de vertices do grafo simples: ");
        vertices = scanner.nextInt();
        while (vertices <= 0) {
            System.out.print("Numero invalido. Digite novamente: ");
            vertices = scanner.nextInt();
        }

        ListaAdjacenciaSimples[] lista = new ListaAdjacenciaSimples[vertices];
        for (int i = 0; i < vertices; i++) {
            lista[i] = new ListaAdjacenciaSimples();
        }

        // Entrada da Lista
        for (int i = 0; i < vertices; i++) {
            System.out.print("\nQuantos vertices estao ligados ao vertice " + i + "? ");
            lista[i].quantidade = scanner.nextInt();

            while (lista[i].quantidade < 0 || lista[i].quantidade >= vertices) {
                System.out.print("Invalido! (Maximo " + (vertices - 1) + "): ");
                lista[i].quantidade = scanner.nextInt();
            }

            if (lista[i].quantidade > 0) {
                lista[i].vizinhos = new int[lista[i].quantidade];

                System.out.println("Digite os vertices ligados ao vertice " + i + ":");
                for (int j = 0; j < lista[i].quantidade; j++) {
                    lista[i].vizinhos[j] = scanner.nextInt();

                    while (lista[i].vizinhos[j] < 0 || lista[i].vizinhos[j] >= vertices) {
                        System.out.print("Vertice invalido. Digite novamente: ");
                        lista[i].vizinhos[j] = scanner.nextInt();
                    }
                }
            }
        }

        // Validação de Grafo Simples
        int eh_simples = 1;
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < lista[i].quantidade; j++) {
                int vizinho = lista[i].vizinhos[j];

                // 1. Checa Laço
                if (vizinho == i) eh_simples = 0;

                // 2. Checa Aresta Múltipla
                for (int k = j + 1; k < lista[i].quantidade; k++) {
                    if (lista[i].vizinhos[k] == vizinho) eh_simples = 0;
                }

                // 3. Checa Simetria (Via de mão dupla)
                int tem_volta = 0;
                for (int k = 0; k < lista[vizinho].quantidade; k++) {
                    if (lista[vizinho].vizinhos[k] == i) tem_volta = 1;
                }
                if (tem_volta == 0) eh_simples = 0;
            }
        }

        if (eh_simples == 0) {
            System.out.println("\nERRO: A lista inserida nao forma um grafo simples.");
            scanner.close();
            return; // Encerra o programa
        }

        // Lógica do DFS Iterativo (Grafo Simples com Pilha Dupla)
        int[] visitado = new int[vertices];
        int tem_ciclo = 0;
        
        int[] pilha_v = new int[vertices * vertices];
        int[] pilha_pai = new int[vertices * vertices];
        int topo = 0;

        for (int inicio = 0; inicio < vertices; inicio++) {
            if (visitado[inicio] == 0 && tem_ciclo == 0) {
                
                pilha_v[topo] = inicio;
                pilha_pai[topo] = -1; // Sem pai
                topo++;

                while (topo > 0) {
                    topo--;
                    int atual = pilha_v[topo];
                    int pai_do_atual = pilha_pai[topo];

                    if (visitado[atual] == 0) {
                        visitado[atual] = 1; 

                        // Percorre os vizinhos
                        for (int j = 0; j < lista[atual].quantidade; j++) {
                            int vizinho = lista[atual].vizinhos[j];
                            
                            // Achou um visitado que NÃO é o pai
                            if (visitado[vizinho] == 1 && vizinho != pai_do_atual) {
                                tem_ciclo = 1;
                                topo = 0; 
                                break;
                            }
                            
                            if (visitado[vizinho] == 0) {
                                pilha_v[topo] = vizinho;
                                pilha_pai[topo] = atual; 
                                topo++;
                            }
                        }
                    }
                }
            }
        }

        System.out.println("\n--- Resultado DFS ---");
        if (tem_ciclo == 1) System.out.println("O grafo simples POSSUI um ciclo.");
        else System.out.println("O grafo simples NAO possui ciclos.");

        scanner.close();
    }
}