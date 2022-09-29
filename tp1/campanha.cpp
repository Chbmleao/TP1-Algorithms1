#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "campanha.hpp" 

void printMatrix(int** matrix, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; i++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }   
}

int** createNullMatrix(int height) {
    int** adjMatrix;
    adjMatrix = new int*[height];
    for (int i = 0; i < height; i++) {
        adjMatrix[i] = new int[height];
        for (int j = 0; j < height; j++){
            adjMatrix[i][j] = 0;
        }
    }
    return adjMatrix;
}

int** createAdjMatrix(std::ifstream &inputFile, int numFollowers, int numProposals) {
    int** adjMatrix = createNullMatrix(2*numProposals); 
   
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

        if (accProposal1 != -1 && accProposal2 != -1) {     // X, Y
            adjMatrix[accProposal1 + numProposals][accProposal2] = 1;   // X' -> Y
            adjMatrix[accProposal2 + numProposals][accProposal1] = 1;   // Y' -> X
        }
        if (rejProposal1, rejProposal2) {   // X', Y'
            adjMatrix[accProposal1][accProposal2 + numProposals] = 1;   // X -> Y'
            adjMatrix[accProposal2][accProposal1 + numProposals] = 1;   // Y -> X'
        }
    }
    return adjMatrix;
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
            
            int** adjMatrix = createAdjMatrix(inputFile, numFollowers, numProposals);
        }
    } else {
        std::cout << "Could not open the Input File.";
    }
}