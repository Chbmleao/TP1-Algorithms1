#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "campanha.hpp" 

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

Graph createAdjMatrix(std::ifstream &inputFile, int numFollowers, int numProposals) {
    Graph graph = createNullMatrix(2*numProposals); 
   
    for (int i = 0; i < numFollowers; i++) {
        int accProposal1, accProposal2, rejProposal1, rejProposal2;
        inputFile >> accProposal1;
        inputFile >> accProposal2;
        inputFile >> rejProposal1;
        inputFile >> rejProposal2;
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

void readFile(std::string fileName) {
    std::ifstream inputFile(fileName);
    if(inputFile.is_open()) {
        std::string strAux;
        int numFollowers;
        int numProposals;

        while (inputFile.good()) {
            inputFile >> numFollowers;
            inputFile >> numProposals;

            if(numFollowers == 0 && numProposals == 0) 
                break;
            
            Graph graph = createAdjMatrix(inputFile, numFollowers, numProposals);

            printMatrix(graph);
        }
    } else {
        std::cout << "Could not open the Input File.";
    }
}