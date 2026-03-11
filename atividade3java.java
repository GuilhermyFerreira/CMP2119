import java.util.Scanner;

class ListaAdj {
    int[] vizinhos;
    int quantidade;
}

public class Grafo {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Digite o numero de vertices: ");
        int vertices = sc.nextInt();

        if (vertices <= 0) {
            System.out.println("Numero invalido.");
            return;
        }

        // criar lista de adjacencia
        ListaAdj[] lista = new ListaAdj[vertices];

        for (int i = 0; i < vertices; i++) {    
            lista[i] = new ListaAdj();

            System.out.print("\nQuantos vertices ligados ao vertice " + i + "? ");
            lista[i].quantidade = sc.nextInt();

            lista[i].vizinhos = new int[lista[i].quantidade];

            System.out.println("Digite os vertices ligados:");

            for (int j = 0; j < lista[i].quantidade; j++) {
                lista[i].vizinhos[j] = sc.nextInt();
            }
        }

        // mostrar lista de adjacencia
        System.out.println("\nLista de adjacencia:");

        for (int i = 0; i < vertices; i++) {
            System.out.print(i + " -> ");

            for (int j = 0; j < lista[i].quantidade; j++) {
                System.out.print(lista[i].vizinhos[j] + " ");
            }

            System.out.println();
        }

        // criar matriz de adjacencia
        int[][] matriz = new int[vertices][vertices];

        // converter lista -> matriz
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < lista[i].quantidade; j++) {

                int destino = lista[i].vizinhos[j];
                matriz[i][destino] = 1;
            }
        }

        // mostrar matriz
        System.out.println("\nMatriz de adjacencia:");

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                System.out.print(matriz[i][j] + " ");
            }
            System.out.println();
        }

        // verificar se e direcionado (olhando a lista)
        boolean simetrico = true;

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < lista[i].quantidade; j++) {

                int destino = lista[i].vizinhos[j];
                boolean encontrouVolta = false;

                for (int k = 0; k < lista[destino].quantidade; k++) {

                    if (lista[destino].vizinhos[k] == i) {
                        encontrouVolta = true;
                        break;
                    }
                }

                if (!encontrouVolta) {
                    simetrico = false;
                }
            }
        }

        if (simetrico) {
            System.out.println("\nO grafo nao e direcionado.");
        } else {
            System.out.println("\nO grafo e direcionado.");
        }

        sc.close();
    }
}