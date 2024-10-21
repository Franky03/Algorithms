#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

typedef pair<int, int> Edge; // vértice e o peso da aresta

void dijkstra(vector<vector<Edge>> &graph, int V, int start){ 
    // graph : lista de adjacência
    // V : número de vértices
    // start : vértice inicial

    vector<int> chave(V, numeric_limits<int>::max()); // chave[v] = menor peso da aresta que liga v a uma árvore
    vector<int> pai(V, -1); // pai[v] = vértice que antecede v na árvore
    vector<bool> inMST(V, false); // inMST[v] = true se v está na árvore

    priority_queue<Edge, vector<Edge>, greater<Edge>> Q; // fila de prioridade min-heap

    chave[start] = 0;
    Q.push({0, start});

    while(!Q.empty()){
        int u = Q.top().second; // vértice com a menor chave
        Q.pop(); // O(log V)

        if(inMST[u]) continue; // vértice já está na árvore
        inMST[u] = true;

        for(auto& [v, peso]: graph[u]){
            if(!inMST[v] && peso + chave[u] < chave[v]){
                chave[v] = peso + chave[u];
                pai[v] = u; // u é o pai de v
                Q.push({chave[v], v}); // O(log V)
            }
        }
    }

    cout << "Menor caminho a partir do vértice " << start << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "Distância até " << i << ": " << chave[i] << "\n";
    }

    cout << "Caminho:\n";
    for (int i = 0; i < V; ++i) {
        cout << i << " <- ";
        for(int u = pai[i]; u != -1; u = pai[u]){
            cout << u << " <- ";
        }
        cout << "\n";
    }
    

}

int main(){
    int V = 5; // Número de vértices

    // Grafo representado por listas de adjacência
    vector<vector<Edge>> graph(V);

    // Adicionando as arestas (u, v, peso)
    graph[0].push_back({1, 2});
    graph[0].push_back({3, 6});
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 8});
    graph[1].push_back({4, 5});
    graph[2].push_back({1, 3});
    graph[2].push_back({4, 7});
    graph[3].push_back({0, 6});
    graph[3].push_back({1, 8});
    graph[3].push_back({4, 9});
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 7});
    graph[4].push_back({3, 9});

    // print lista de adjacencia
    for (int i = 0; i < V; ++i) {
        cout << i << ": ";
        for(auto& [v, peso]: graph[i]){
            cout << v << "(" << peso << ") ";
        }
        cout << "\n";
    }

    // Chamar Prim a partir do vértice 0
    dijkstra(graph, V, 0);

    return 0;
}