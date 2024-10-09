#pragma once
#include "Node.h"

class Edge {
    public:
        Node* first_;
        Node* second_;
        int weight_;
        Edge(Node* first=0, Node* second=0, int weight=0);
        ~Edge();
};