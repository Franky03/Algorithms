#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

struct Edge {
    int peso;
    int to;

    // Para garantir que o Edge seja comparado pelo peso na priority_queue
    bool operator>(const Edge &e) const {
        return peso > e.peso;
    }
};

void primMST(vector<vector<Edge>> &graph, int V, int start){ 
    vector<int> chave(V, numeric_limits<int>::max()); // Menor peso da aresta que liga v à árvore
    vector<int> pai(V, -1); // Vértice que antecede v na árvore
    vector<bool> inMST(V, false); // true se v está na árvore

    // Fila de prioridade para armazenar os vértices
    priority_queue<Edge, vector<Edge>, greater<Edge>> Q;

    chave[start] = 0;
    Q.push({0, start});

    while(!Q.empty()){
        int u = Q.top().to; // Vértice com a menor chave
        Q.pop(); // Remove da fila

        if(inMST[u]) continue; // Se já está na árvore, ignora
        inMST[u] = true;

        // Processa os vizinhos
        for(auto& edge : graph[u]){
            int v = edge.to;
            int peso = edge.peso;

            // Se v ainda não está na árvore e o peso da aresta é menor que a chave[v]
            if(!inMST[v] && peso < chave[v]){
                chave[v] = peso;
                pai[v] = u;
                Q.push({chave[v], v}); // Adiciona à fila de prioridade
            }
        }
    }

    // Imprime as arestas da MST
    cout << "Arestas na MST:\n";
   for (int i = 1; i < V; ++i) {
    if (pai[i] != -1) { // Verifica se o vértice tem pai
        // Transforme o índice numérico em letras, somando 97 para obter o valor ASCII de 'a'
        cout << char(pai[i] + 97) << " - " << char(i + 97) << " com peso " << chave[i] << "\n";
    }

    // printar o valor da solução
    int solucao = 0;
    for (int i = 0; i < V; ++i) {
        solucao += chave[i];
    }
    cout << "Solução: " << solucao << "\n";
}
}

int main(){
    int V = 9; // Número de vértices

    // Grafo representado por listas de adjacência
    vector<vector<Edge>> graph(V);

    graph[0].push_back({4, 1});  // a -> b (4)
    graph[0].push_back({8, 7});  // a -> h (8)

    graph[1].push_back({4, 0});  // b -> a (4)
    graph[1].push_back({8, 2});  // b -> c (8)
    graph[1].push_back({11, 7}); // b -> h (11)

    graph[2].push_back({8, 1});  // c -> b (8)
    graph[2].push_back({7, 3});  // c -> d (7)
    graph[2].push_back({4, 5});  // c -> i (4)
    graph[2].push_back({2, 8});  // c -> i (2)

    graph[3].push_back({7, 2});  // d -> c (7)
    graph[3].push_back({9, 4});  // d -> e (9)
    graph[3].push_back({14, 5}); // d -> f (14)

    graph[4].push_back({9, 3});  // e -> d (9)
    graph[4].push_back({10, 5}); // e -> f (10)

    graph[5].push_back({4, 2});  // f -> c (4)
    graph[5].push_back({14, 3}); // f -> d (14)
    graph[5].push_back({10, 4}); // f -> e (10)
    graph[5].push_back({3, 6});  // f -> g (2)

    graph[6].push_back({3, 5});  // g -> f (2)
    graph[6].push_back({1, 7});  // g -> h (1)
    graph[6].push_back({6, 8});  // g -> i (6)

    graph[7].push_back({8, 0});  // h -> a (8)
    graph[7].push_back({11, 1}); // h -> b (11)
    graph[7].push_back({1, 6});  // h -> g (1)

    graph[8].push_back({2, 2});  // i -> c (2)
    graph[8].push_back({6, 6});  // i -> g (6)

    // Chamar Prim a partir do vértice 0
    primMST(graph, V, 0);

    return 0;
}