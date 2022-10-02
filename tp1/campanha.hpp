#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

struct Graph {
    int** matrix;
    int size;
    int calculateDeniedIndex(int index) {
        int deniedIndex = index + (this->size / 2);
        return deniedIndex;
    }
};

void DFS(Graph graph, int** isAlreadyVisited, int vertice);
void dephtFirstSearch(Graph graph);
void printMatrix(Graph graph);
Graph createNullMatrix(int side);
Graph createAdjMatrix(int numFollowers, int numProposals);
void readFile();
