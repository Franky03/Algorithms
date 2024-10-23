#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> knapsack(int n, int M, vector<int> p, vector<int> v){ // O(n*M)
    vector<vector<int>> k(n+1, vector<int>(M+1, 0)); // tabela k para armazenar os valores

    // itera sobre os itens
    for(int i = 0; i <= n; i++){
        // itera sobre as capacidades da mochila
        for(int j=0; j <= M; j++){
            // caso base
            if(i==0 || j==0){
                k[i][j] = 0;
            } 
            // se o peso do item atual for menor ou igual a capacidade da mochila
            else if(p[i-1] <= j){
                // maximo entre o valor do item atual + o valor do item anterior
                k[i][j] = max(v[i-1] + k[i-1][j-p[i-1]], k[i-1][j]);
            }
            // caso contrário, não podemos incluir o item 
            else {
                k[i][j] = k[i-1][j];
            }
        }
    }

    return k;
}

void printaItens(int n, int M, vector<int> p, vector<int> v, vector<vector<int>> k){ // O(n)
    int i = n;
    int j = M;
    vector<int> itens;

    while(i > 0 && j > 0){
        if(k[i][j] != k[i-1][j]){ // se for diferente, o item foi incluído na mochila
            itens.push_back(i); 
            j = j - p[i-1]; // subtrai o peso do item da capacidade da mochila -> vai para a linha anterior da tabela k onde o item foi incluído
        }
        i--; // vai para o item anterior
    }

    cout << "Itens escolhidos: ";
    for(int i = 0; i < itens.size(); i++){
        cout << itens[i] << " ";
    }
    cout << endl;

}

int main() {
    // Número de itens
    int n = 4;
    // Capacidade da mochila
    int M = 7;
    // Vetor de pesos
    vector<int> p = {1, 3, 4, 5};
    // Vetor de valores
    vector<int> v = {1, 4, 5, 7};

    // Chamada da função knapsack
    vector<vector<int>> k = knapsack(n, M, p, v);
    cout << "Valor máximo que pode ser carregado: " << k[n][M] << endl;

    // Chamada da função printaItens
    printaItens(n, M, p, v, k);


    return 0;
}