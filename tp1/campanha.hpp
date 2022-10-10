#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>

class Graph {
    public:
        Graph(int size);
        void addToDfsOrder(int index);
        int size;
        int dfsOrderCount;
        std::vector<int> dfsOrder;
        std::vector<int> stronglyConnectedComponent;
        std::vector<std::list<int>> adjList;
        std::vector<std::list<int>> adjListInv;  
};

bool isSatisfiable(Graph graph);
void DFS1(Graph* graph, int* isAlreadyVisited, int vertice);
void DFS2(Graph* graph, int* isAlreadyVisitedInv, int vertice, int counter);
void dephtFirstSearch(Graph* graph);
Graph* createAdjList(int numFollowers, int numProposals);
void readFile();