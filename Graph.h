#pragma once
#include "Node.h"
#include "Edge.h"

class Graph {
    void sortEdges();
    public:
        Graph(Node** vertices, Edge** edges, int numNodes, int numEdges);
        ~Graph();
        Graph* kruskal();
        void print()const;
    private:
        Node** vertices_;
        int numNodes_;
        Edge** edges_;
        int numEdges_;
};