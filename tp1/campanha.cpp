#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "campanha.hpp" 

void printMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.size; i++) {
        for (int j = 0; j < matrix.size; j++) {
            std::cout << matrix.matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }   
    std::cout << std::endl;
}

Matrix createNullMatrix(int size) {
    Matrix nullMatrix;
    nullMatrix.matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        nullMatrix.matrix[i] = new int[size];
        for (int j = 0; j < size; j++){
            nullMatrix.matrix[i][j] = 0;
        }
    }
    nullMatrix.size = size;
    return nullMatrix;
}

Matrix createAdjMatrix(std::ifstream &inputFile, int numFollowers, int numProposals) {
    Matrix adjMatrix = createNullMatrix(2*numProposals); 
   
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
            adjMatrix.matrix[adjMatrix.calculateDeniedIndex(accProposal2)][accProposal2] = 1;   // X' -> X
            adjMatrix.matrix[accProposal2][adjMatrix.calculateDeniedIndex(accProposal2)] = 1;   // X -> X'
        } else if (accProposal2 == -1) {
            adjMatrix.matrix[adjMatrix.calculateDeniedIndex(accProposal1)][accProposal1] = 1;   // X' -> X
            adjMatrix.matrix[accProposal1][adjMatrix.calculateDeniedIndex(accProposal1)] = 1;   // X -> X'
        } else if (rejProposal1 == -1) {
            adjMatrix.matrix[adjMatrix.calculateDeniedIndex(rejProposal2)][rejProposal2] = 1;   // X' -> X
            adjMatrix.matrix[rejProposal2][adjMatrix.calculateDeniedIndex(rejProposal2)] = 1;   // X -> X'
        } else if (rejProposal2 == -1) {
            adjMatrix.matrix[adjMatrix.calculateDeniedIndex(rejProposal1)][rejProposal1] = 1;   // X' -> X
            adjMatrix.matrix[rejProposal1][adjMatrix.calculateDeniedIndex(rejProposal1)] = 1;   // X -> X'
        } else {
            adjMatrix.matrix[adjMatrix.calculateDeniedIndex(accProposal1)][accProposal2] = 1;   // X' -> Y
            adjMatrix.matrix[adjMatrix.calculateDeniedIndex(accProposal2)][accProposal1] = 1;   // Y' -> X
            adjMatrix.matrix[rejProposal1][adjMatrix.calculateDeniedIndex(rejProposal2)] = 1;   // X -> Y'
            adjMatrix.matrix[rejProposal2][adjMatrix.calculateDeniedIndex(rejProposal1)] = 1;   // Y -> X'
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
            
            Matrix adjMatrix = createAdjMatrix(inputFile, numFollowers, numProposals);

            printMatrix(adjMatrix);
        }
    } else {
        std::cout << "Could not open the Input File.";
    }
}