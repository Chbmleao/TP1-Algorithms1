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
        int calculateIndex(int index, bool negative);
        void addToOrder(int index);
        int size;
        int orderCount;
        std::vector<std::list<int>> adjList; 
        std::vector<int> order;
        std::vector<int> stronglyConnectedComponent;
};

bool isSatisfiable(Graph graph);
void DFS1(Graph* graph, int* isAlreadyVisited, int vertice);
void DFS2(Graph* graph, int* isAlreadyVisitedInv, int vertice, int counter);
void dephtFirstSearch(Graph* graph);
// void printMatrix(Graph graph);
// std::vector<std::vector<int>> createNullMatrix(int side);
Graph* createAdjList(int numFollowers, int numProposals);
void readFile();
