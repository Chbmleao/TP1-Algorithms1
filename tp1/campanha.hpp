#include <stdio.h>
#include <stdlib.h>

void printMatrix(int** matrix, int height);
int** createNullMatrix(int height);
int** createAdjMatrix(std::ifstream &inputFile, int numFollowers, int numProposals);
void readFile(std::string fileName);
