#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

struct Matrix {
    int** matrix;
    int size;
    int calculateDeniedIndex(int index) {
        int deniedIndex = index + (this->size / 2);
        return deniedIndex;
    }
};

void printMatrix(Matrix matrix);
Matrix createNullMatrix(int side);
Matrix createAdjMatrix(std::ifstream &inputFile, int numFollowers, int numProposals);
void readFile(std::string fileName);
