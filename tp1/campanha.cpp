#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "campanha.hpp" 

void printMatrix(int** matrix, int side) {
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }   
}

int** createNullMatrix(int side) {
    int** matrix;
    matrix = new int*[side];
    for (int i = 0; i < side; i++) {
        matrix[i] = new int[side];
        for (int j = 0; j < side; j++){
            matrix[i][j] = 0;
        }
    }
    return matrix;
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

        if (accProposal1 == -1) {
            adjMatrix[accProposal1 + numProposals][accProposal1] = 1;   // X' -> X
            adjMatrix[accProposal1][accProposal1 + numProposals] = 1;   // X -> X'
        } else if (accProposal2 == -1) {
            adjMatrix[accProposal2 + numProposals][accProposal2] = 1;   // X' -> X
            adjMatrix[accProposal2][accProposal2 + numProposals] = 1;   // X -> X'
        } else if (rejProposal1 == -1) {
            adjMatrix[rejProposal1 + numProposals][rejProposal1] = 1;   // X' -> X
            adjMatrix[rejProposal1][rejProposal1 + numProposals] = 1;   // X -> X'
        } else if (rejProposal2 == -1) {
            adjMatrix[rejProposal2 + numProposals][rejProposal2] = 1;   // X' -> X
            adjMatrix[rejProposal2][rejProposal2 + numProposals] = 1;   // X -> X'
        } else {
            if (accProposal1 != -1 && accProposal2 != -1) {     // X, Y
            adjMatrix[accProposal1 + numProposals][accProposal2] = 1;   // X' -> Y
            adjMatrix[accProposal2 + numProposals][accProposal1] = 1;   // Y' -> X
            }
            if (rejProposal1, rejProposal2) {   // X', Y'
                adjMatrix[accProposal1][accProposal2 + numProposals] = 1;   // X -> Y'
                adjMatrix[accProposal2][accProposal1 + numProposals] = 1;   // Y -> X'
            }
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