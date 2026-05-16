#include <iostream>
using namespace std;

int main() {

    int n;

    cout << "Quantos vertices o grafo tem? ";
    cin >> n;

    while(n <= 0){
        cout << "Valor invalido. Digite novamente: ";
        cin >> n;
    }

    int grafo[n][n];

    cout << "\nDigite a matriz de adjacencia:\n";

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){

            cin >> grafo[i][j];

            while(grafo[i][j] != 0 && grafo[i][j] != 1){
                cout << "Valor invalido. Digite 0 ou 1: ";
                cin >> grafo[i][j];
            }
        }
    }

    // -------- Validacao de grafo simples --------

    for(int i = 0; i < n; i++){

        // verifica laco
        if(grafo[i][i] != 0){
            cout << "\nO grafo nao e simples (possui laco).\n";
            return 0;
        }

        // verifica simetria
        for(int j = 0; j < n; j++){

            if(grafo[i][j] != grafo[j][i]){
                cout << "\nO grafo nao e simples (nao e simetrico).\n";
                return 0;
            }
        }
    }

    // -------- Verificacao de clique --------
    // Vamos testar todos os grupos de 3 vertices

    int encontrou = 0;

    for(int i = 0; i < n; i++){

        for(int j = i + 1; j < n; j++){

            for(int k = j + 1; k < n; k++){

                // para ser clique:
                // todos precisam estar ligados entre si

                if(grafo[i][j] == 1 &&
                   grafo[i][k] == 1 &&
                   grafo[j][k] == 1){

                    encontrou = 1;

                    cout << "\nClique encontrado: ";
                    cout << i << " " << j << " " << k << "\n";
                }
            }
        }
    }

    if(encontrou == 0){
        cout << "\nO grafo nao possui clique de tamanho 3.\n";
    }

    return 0;
}