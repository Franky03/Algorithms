#include "Graph.h"
#include <iostream>
using namespace std;

Graph::Graph(Node** vertices, Edge** edges, int numNodes, int numEdges) : vertices_(vertices), numNodes_(numNodes), edges_(edges), numEdges_(numEdges){
    sortEdges();
}

Graph::~Graph(){
    for(int i=0; i<numNodes_; i++){
        delete vertices_[i];
    }
    for(int i=0; i<numEdges_; i++){
        delete edges_[i];
    }
    delete[] vertices_;
    delete[] edges_;
}

void make_set(Node* x){
    x->parent_ = x;
    x->rank_ = 0;
} // cria um conjunto com um único elemento, o parent_ é o próprio nó e o rank_ é 0

Node* find_set(Node* x){
    if(x != x->parent_){ 
        x->parent_ = find_set(x->parent_); // path compression, a cada chamada de find_set, o nó x passa a apontar diretamente para o pai
    } // se x não for o representante do conjunto, x passa a apontar diretamente para o representante
    return x->parent_; // retorna o representante do conjunto
}

void union_set(Node* x, Node* y){
    Node* root_x = find_set(x);
    Node* root_y = find_set(y);

    if(root_x->rank_ > root_y->rank_){
        root_y->parent_ = root_x; // se a árvore de x for maior que a de y, y passa a apontar para x
    }
    else {
        root_x->parent_ = root_y; // se a árvore de y for maior que a de x, x passa a apontar para y
        if(root_x->rank_ == root_y->rank_){
            root_y->rank_++; // se as árvores tiverem o mesmo tamanho, a árvore de y passa a ter um nível a mais 
            // pois a árvore de x foi adicionada a árvore de y, então a árvore de y passa a ter um nível a mais que a de x
        }
    }
}

void Graph::sortEdges(){ // insertion sort
    int i, j;
    Edge* key;
    for(i=1; i< numEdges_; i++){
        key = edges_[i];
        j = i-1;
        while(j>=0 && edges_[j]->weight_ > key->weight_){
            edges_[j+1] = edges_[j];
            j = j-1;
        }
        edges_[j+1] = key;
    }

}

Graph* Graph::kruskal(){
    Graph* G = new Graph(NULL, NULL, 0,0);
    Edge** E = new Edge*[numEdges_];
    Node** V = new Node*[numNodes_];
    int m = 0;
    for(int i = 0; i < numNodes_; i++){
        make_set(vertices_[i]);
    }
    sortEdges();
    for(int i = 0; i < numEdges_; i++){
        if(find_set(edges_[i]->first_) != find_set(edges_[i]->second_)){
            E[m] = edges_[i];
            m++;
            union_set(edges_[i]->first_, edges_[i]->second_);
        }
    }

    for(int i = 0; i < numNodes_; i++){
        V[i] = new Node(0, i, 0);
    }
    G->edges_ = E;
    G->vertices_ = V;
    G->numEdges_ = m;
    G->numNodes_ = numNodes_;

    return G;
}

void
Graph::print()const
{
	cout << endl << "VERTICES: ";
	for (int i = 0; i < numNodes_; i++)
		cout << vertices_[i]->element_ << " ";
	cout << endl;

	cout << endl << "EDGES:" << endl;
	for (int j = 0; j < numEdges_; j++)
	{
		cout << (edges_[j])->first_->element_ << ", ";
		cout << (edges_[j])->weight_ << ", ";
		cout << (edges_[j])->second_->element_ << endl;
	}
	cout << endl;
}