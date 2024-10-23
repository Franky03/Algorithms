#include <iostream>
#include <vector>
#include <algorithm>  // Para usar a função min

using namespace std;

int linhaMontagem(int n, const vector<vector<int>>& a, const vector<vector<int>>& t, const vector<int>& e, const vector<int>& x, vector<vector<int>>& linhaEscolhida){
    // a = tempos de montagem
    // t = tempos de transferência
    // e = tempos de entrada
    // x = tempos de saída

    // criar matriz f[2][n] onde f[0] representa a linha 1 e f[1] representa a linha 2
    vector<vector<int>> f(2, vector<int>(n));
    
    f[0][0] = e[0] + a[0][0];
    f[1][0] = e[1] + a[1][0];

    for(int i = 1; i < n; ++i){
        if(f[0][i-1] <= f[1][i-1] + t[1][i-1]){ // Se a linha 1 for mais rápida que fazer a transferência da linha 2 para a linha 1
            f[0][i] = a[0][i] + f[0][i-1]; // A linha 1 é mais rápida
            linhaEscolhida[0][i] = 1;
        }
        else {
            f[0][i] = a[0][i] + f[1][i-1] + t[1][i-1]; // A linha 2 é mais rápida
            linhaEscolhida[0][i] = 2;
        }

        if(f[1][i-1] <= f[0][i-1] + t[0][i-1]){ // Se a linha 2 for mais rápida que fazer a transferência da linha 1 para a linha 2
            f[1][i] = a[1][i] + f[1][i-1]; // A linha 2 é mais rápida
            linhaEscolhida[1][i] = 2;
        }
        else {
            f[1][i] = a[1][i] + f[0][i-1] + t[0][i-1]; // A linha 1 é mais rápida
            linhaEscolhida[1][i] = 1;
        }
    }

    return min(f[0][n-1] + x[0], f[1][n-1] + x[1]); // Retorna o tempo mínimo para sair da linha de montagem
}

void printaSolucao(int n, const vector<vector<int>>& linhaEscolhida, int linhaFinal){
    vector<int> caminho(n);

    int linha = linhaFinal;

    for(int i = n-1; i >= 0; --i){
        caminho[i] = linha;
        linha = linhaEscolhida[linha-1][i];
    }

    cout << "Caminho escolhido: ";
    for(int i = 0; i < n; ++i){
        cout << caminho[i] << " ";
    }
    cout << endl;
   
}

int main(){
    int n = 6;  // Número de estações

    // Tempo de processamento em cada estação para cada linha
    vector<vector<int>> a = {
        {7, 9, 3, 4, 8, 4},  // Linha 1
        {8, 5, 6, 4, 5, 7}   // Linha 2
    };

    // Tempo de transição entre as linhas
    vector<vector<int>> t = {
        {2, 3, 1, 3, 4},  // Transição da linha 1 para a linha 2
        {2, 1, 2, 2, 1}   // Transição da linha 2 para a linha 1
    };

    // Tempo de entrada nas linhas
    vector<int> e = {2, 4};

    // Tempo de saída das linhas
    vector<int> x = {3, 2};

    // Matriz que guarda a linha escolhida para cada estação
    vector<vector<int>> linhaEscolhida(2, vector<int>(n));

    int tempoMinimo = linhaMontagem(n, a, t, e, x, linhaEscolhida);
    cout << "Tempo mínimo para sair da linha de montagem: " << tempoMinimo << endl;

    printaSolucao(n, linhaEscolhida, tempoMinimo == (tempoMinimo - x[0]) ? 1 : 2);

    return 0;
}