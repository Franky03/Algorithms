#include "Graph.h"
#include <iostream>
using namespace std;


Graph* sampleGraph(){
    int n = 6;
	Node** v = new Node*[n];
	for (int i = 0; i < n; i++)
		v[i] = new Node(0, i, 0);

	int m = 9;
	Edge**  edges = new Edge*[m];

    edges[0] = new Edge(v[0], v[1], 7);
    edges[1] = new Edge(v[0], v[2], 5);
    edges[2] = new Edge(v[0], v[4], 10);
    edges[3] = new Edge(v[1], v[3], 3);
    edges[4] = new Edge(v[1], v[5], 2);
    edges[5] = new Edge(v[2], v[3], 4);
    edges[6] = new Edge(v[2], v[4], 8);
    edges[7] = new Edge(v[3], v[5], 1);
    edges[8] = new Edge(v[4], v[5], 9);
	
    return new Graph(v, edges, n, m);
}

int main()
{
	Graph* graph = sampleGraph();
	cout << "***** INITIAL GRAPH *****" << endl;
	graph->print();
	
	Graph* mst = graph->kruskal();
	cout << "***** THE MINIMUM SPANNING TREE *****" << endl;
    mst->print();


	return 0;
}
