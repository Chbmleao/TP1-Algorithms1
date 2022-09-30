#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

void printMatrix(int** matrix, int height);
int** createNullMatrix(int height);
int** createAdjMatrix(std::ifstream &inputFile, int numFollowers, int numProposals);
void readFile(std::string fileName);
