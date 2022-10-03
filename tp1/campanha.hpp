#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Graph {
    public:
        Graph(int size);
        int calculateIndex(int index, bool negative);
        void addToOrder(int index);
        std::vector<std::vector<int>> matrix; 
        int size;   
        std::vector<int> order;
        int orderCount;
};

bool isSatisfiable(Graph graph);
void DFS(Graph* graph, int** isAlreadyVisited, int vertice);
void dephtFirstSearch(Graph* graph);
void printMatrix(Graph graph);
std::vector<std::vector<int>> createNullMatrix(int side);
Graph* createAdjMatrix(int numFollowers, int numProposals);
void readFile();
