#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "campanha.hpp" 

Graph::Graph(int size) {
    this->size = size;
    // create order vector and initialize with -1
    this->order = std::vector<int>(this->size, -1);
    // create Strongly Connected Component vector and initialize with -1
    this->stronglyConnectedComponent = std::vector<int>(this->size, -1);

    this->orderCount = 0;
    this->matrix = createNullMatrix(this->size);
}

int Graph::calculateIndex(int index, bool negative) {
    index--;
    if (negative) 
        index += this->size / 2;
    return index;
}

void Graph::addToOrder(int index) {
    this->order[this->orderCount] = index;
    this->orderCount++;
}

bool isSatisfiable(Graph graph) {
    int n = graph.size/2;
    for (int i = 0; i < n; i++) {
        if (graph.stronglyConnectedComponent[i] == graph.stronglyConnectedComponent[i+n])
            return 0;
    }
    return 1;
}

void DFS1(Graph *graph, int* isAlreadyVisited, int vertice) {
    if (isAlreadyVisited[vertice]) 
        return;
    
    isAlreadyVisited[vertice] = 1;

    for (int i = 0; i < graph->size; i++) {
        if (graph->matrix[vertice][i]) { // for each neighbor vertice that has not yet been visited
            if (!isAlreadyVisited[i]) 
                DFS1(graph, isAlreadyVisited, i);
        }
    }

    graph->addToOrder(vertice);
}

void DFS2(Graph* graph, int* isAlreadyVisitedInv, int vertice, int counter) {
    if (isAlreadyVisitedInv[vertice])
        return;

    isAlreadyVisitedInv[vertice] = 1;
    for (int i = 0; i < graph->size; i++) {
        if (graph->matrix[vertice][i]) { // for each neighbor vertice that has not yet been visited
            if (!isAlreadyVisitedInv[i]) 
                DFS2(graph, isAlreadyVisitedInv, i, counter);
        }
    }
    
    graph->stronglyConnectedComponent[vertice] = counter;
}

void dephtFirstSearch(Graph *graph) {
    // create array to mark visited vertices in normal DFS
    int* isAlreadyVisited = new int[graph->size];
    for (int i = 0; i < graph->size; i++) {
        isAlreadyVisited[i] = 0;
    }

    // create array to mark visited vertices in topological order DFS
    int* isAlreadyVisitedInv = new int[graph->size];
    for (int i = 0; i < graph->size; i++) {
        isAlreadyVisitedInv[i] = 0;
    }

    // normal DFS to create topological order
    for (int i = 0; i < graph->size; i++) {
        if (!isAlreadyVisited[i]) {
            DFS1(graph, isAlreadyVisited, i);
        } 
    }

    // DFS in topological order
    int counter = 0;
    for (int i = 0; i < graph->orderCount; i++) {
        int vertice = graph->order[i];

        if (!isAlreadyVisitedInv[vertice]) {
            DFS2(graph, isAlreadyVisitedInv, vertice, counter);
            counter++;
        }
    } 
}

void printMatrix(Graph graph) {
    std::cout << std::setfill(' ') << std::setw(4) << " ";
    for (int i = 0; i < graph.size; i++) {
        if (i < graph.size / 2)
            std::cout << std::setfill(' ') << std::setw(4) << "X" << i+1;
        else
            std::cout << std::setfill(' ') << std::setw(4) << "X" << i+1 - graph.size/2 << "'";   
    }
    std::cout << std::endl;

    for (int i = 0; i < graph.size; i++) {
        if (i < graph.size / 2)
            std::cout << std::setfill(' ') << std::setw(3) << "X" << i+1 << " ";
        else
            std::cout << std::setfill(' ') << std::setw(3) << "X" << i+1 - graph.size/2 << "'"; 

        for (int j = 0; j < graph.size; j++) {
            if (j < graph.size / 2)
                std::cout << std::setfill(' ') << std::setw(4) << graph.matrix[i][j] << " ";
            else
                std::cout << std::setfill(' ') << std::setw(4) << graph.matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> createNullMatrix(int size) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++){
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

Graph* createAdjMatrix(int numFollowers, int numProposals) {
    Graph* graph = new Graph(2*numProposals);
   
    for (int i = 0; i < numFollowers; i++) {
        int accProposal1, accProposal2, rejProposal1, rejProposal2;
        std::cin >> accProposal1;
        std::cin >> accProposal2;
        std::cin >> rejProposal1;
        std::cin >> rejProposal2;

        // accepted proposals treatment
        if (accProposal1 == 0 || accProposal2 == 0) {
            if (accProposal1 == 0 && accProposal2 != 0) {
                graph->matrix[graph->calculateIndex(accProposal2, true)]
                            [graph->calculateIndex(accProposal2, false)] = 1;     // X' -> X
                // std::cout << "1- X" << accProposal2 << "' -> X" << accProposal2 << std::endl;  
            } 
            if (accProposal2 == 0 && accProposal1 != 0) {
                graph->matrix[graph->calculateIndex(accProposal1, true)]
                            [graph->calculateIndex(accProposal1, false)] = 1;     // X' -> X
                // std::cout << "2- X" << accProposal1 << "' -> X" << accProposal1 << std::endl;              
            }
        } else {
            graph->matrix[graph->calculateIndex(accProposal1, true)]
                        [graph->calculateIndex(accProposal2, false)] = 1;   // X' -> Y
            graph->matrix[graph->calculateIndex(accProposal2, true)]
                        [graph->calculateIndex(accProposal1, false)] = 1;   // Y' -> X
            // std::cout << "3- X" << accProposal1 << "' -> X" << accProposal2 << std::endl;
            // std::cout << "4- X" << accProposal2 << "' -> X" << accProposal1 << std::endl;
        }
        
        // rejected proposals treatment
        if (rejProposal1 == 0 || rejProposal2 == 0) {
            if (rejProposal1 == 0 && rejProposal2 != 0) {
                graph->matrix[graph->calculateIndex(rejProposal2, false)]
                            [graph->calculateIndex(rejProposal2, true)] = 1;     // X -> X'
                // std::cout << "5- X" << rejProposal2 << " -> X" << rejProposal2 << "'" << std::endl;  
            }
            if (rejProposal2 == 0 && rejProposal1 != 0) {
                graph->matrix[graph->calculateIndex(rejProposal1, false)]
                            [graph->calculateIndex(rejProposal1, true)] = 1;    // X -> X'
                // std::cout << "6- X" << rejProposal1 << " -> X" << rejProposal1 << "'" << std::endl;
            }
        } else {
            graph->matrix[graph->calculateIndex(rejProposal1, false)]
                        [graph->calculateIndex(rejProposal2, true)] = 1;   // X -> Y'
            graph->matrix[graph->calculateIndex(rejProposal2, false)]
                        [graph->calculateIndex(rejProposal1, true)] = 1;   // Y -> X'
            // std::cout << "7- X" << rejProposal1 << " -> X" << rejProposal2 << "'" << std::endl;
            // std::cout << "8- X" << rejProposal2 << " -> X" << rejProposal1 << "'" << std::endl;
        }
    }
    return graph;
}

void readFile() {
    int numFollowers;
    int numProposals;

    std::cin >> numFollowers;
    std::cin >> numProposals;

    while (numFollowers != 0 && numProposals != 0) {        
        Graph* graph = createAdjMatrix(numFollowers, numProposals);

        // printMatrix(*graph);

        dephtFirstSearch(graph);
        
        if(isSatisfiable(*graph))
            std::cout << "sim" << std::endl;
        else
            std::cout << "nao" << std::endl;

        delete graph;

        std::cin >> numFollowers;
        std::cin >> numProposals;
    }
}