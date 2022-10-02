#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "campanha.hpp" 

void DFS(Graph graph, int* isAlreadyVisited, int vertice) {
    isAlreadyVisited[vertice] = 1;
    for (int i = 0; i < graph.size; i++) {
        if (graph.matrix[vertice][i] == 1) { // for each neighbor vertice that has not yet been visited
            if (isAlreadyVisited[i] == 0) {
                DFS(graph, isAlreadyVisited, i);
            } 
        }
    }
    std::cout <<  vertice << " ";
}

void dephtFirstSearch(Graph graph) {
    // create array to mark visited vertices
    int* isAlreadyVisited = new int[graph.size];
    for (int i = 0; i < graph.size; i++) {
        isAlreadyVisited[i] = 0;
    }
    for (int i = 0; i < graph.size; i++) {
        if (isAlreadyVisited[i] == 0) {
                DFS(graph, isAlreadyVisited, i);
        } 
    }
}

void printMatrix(Graph graph) {
    std::cout << std::setfill(' ') << std::setw(4) << " ";
    for (int i = 0; i < graph.size; i++) {
        std::cout << std::setfill(' ') << std::setw(4) << i;
    }
    std::cout << std::endl;

    for (int i = 0; i < graph.size; i++) {
        std::cout << std::setfill(' ') << std::setw(4) << i;
        for (int j = 0; j < graph.size; j++) {
            std::cout << std::setfill(' ') << std::setw(4) << graph.matrix[i][j];
        }
        std::cout << std::endl;
    }
}

Graph createNullMatrix(int size) {
    Graph nullGraph;
    nullGraph.matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        nullGraph.matrix[i] = new int[size];
        for (int j = 0; j < size; j++){
            nullGraph.matrix[i][j] = 0;
        }
    }
    nullGraph.size = size;
    return nullGraph;
}

Graph createAdjMatrix(int numFollowers, int numProposals) {
    Graph graph = createNullMatrix(2*numProposals); 
   
    for (int i = 0; i < numFollowers; i++) {
        int accProposal1, accProposal2, rejProposal1, rejProposal2;
        std::cin >> accProposal1;
        std::cin >> accProposal2;
        std::cin >> rejProposal1;
        std::cin >> rejProposal2;
        accProposal1--;
        accProposal2--;
        rejProposal1--;
        rejProposal2--;

        if (accProposal1 == -1) {
            graph.matrix[graph.calculateDeniedIndex(accProposal2)][accProposal2] = 1;   // X' -> X
            graph.matrix[accProposal2][graph.calculateDeniedIndex(accProposal2)] = 1;   // X -> X'
        } else if (accProposal2 == -1) {
            graph.matrix[graph.calculateDeniedIndex(accProposal1)][accProposal1] = 1;   // X' -> X
            graph.matrix[accProposal1][graph.calculateDeniedIndex(accProposal1)] = 1;   // X -> X'
        } else if (rejProposal1 == -1) {
            graph.matrix[graph.calculateDeniedIndex(rejProposal2)][rejProposal2] = 1;   // X' -> X
            graph.matrix[rejProposal2][graph.calculateDeniedIndex(rejProposal2)] = 1;   // X -> X'
        } else if (rejProposal2 == -1) {
            graph.matrix[graph.calculateDeniedIndex(rejProposal1)][rejProposal1] = 1;   // X' -> X
            graph.matrix[rejProposal1][graph.calculateDeniedIndex(rejProposal1)] = 1;   // X -> X'
        } else {
            graph.matrix[graph.calculateDeniedIndex(accProposal1)][accProposal2] = 1;   // X' -> Y
            graph.matrix[graph.calculateDeniedIndex(accProposal2)][accProposal1] = 1;   // Y' -> X
            graph.matrix[rejProposal1][graph.calculateDeniedIndex(rejProposal2)] = 1;   // X -> Y'
            graph.matrix[rejProposal2][graph.calculateDeniedIndex(rejProposal1)] = 1;   // Y -> X'
        }
    }
    return graph;
}

void readFile() {
    int numFollowers;
    int numProposals;

    while (!(numFollowers == 0 && numProposals == 0)) {
        std::cin >> numFollowers;
        std::cin >> numProposals;

        if(numFollowers == 0 && numProposals == 0) 
            break;
        
        Graph graph = createAdjMatrix(numFollowers, numProposals);

        printMatrix(graph);

        dephtFirstSearch(graph);
    }
}