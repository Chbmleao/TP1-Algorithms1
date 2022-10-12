#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "campanha.hpp" 

Graph::Graph(int size) {
    this->size = size;
    // create Strongly Connected Component vector and initialize with -1
    this->stronglyConnectedComponent = std::vector<int>(this->size, -1);
    // create order vector and initialize with -1
    this->dfsOrder = std::vector<int>(this->size, -1);
    this->dfsOrderCount = 0;
    
    // create adjList, a vector with lists
    this->adjList = std::vector<std::list<int>>(this->size);
    for (int i = 0; i < this->size; i++) {
        this->adjList[i] = std::list<int>();
    }

    // create adjListInv, a vector with lists
    this->adjListInv = std::vector<std::list<int>>(this->size);
    for (int i = 0; i < this->size; i++) {
        this->adjListInv[i] = std::list<int>();
    }
}

// insert a vertice into the array dfsOrder
void Graph::addToDfsOrder(int index) {
    this->dfsOrder[this->dfsOrderCount] = index;
    this->dfsOrderCount++;
}

// if the boolean expression is satisfiable returns 1, otherwise, returns 0 
bool isSatisfiable(Graph graph) {
    int n = graph.size/2;
    for (int i = 0; i < n; i++) {
        // verify if a vertice is in the same strongly connected component as its complement
        if (graph.stronglyConnectedComponent[i] == graph.stronglyConnectedComponent[i+n])
            return 0;
    }
    return 1;
}

// walk on the graph, stores the return order
void DFS1(Graph *graph, int* isAlreadyVisited, int vertice) {
    isAlreadyVisited[vertice] = 1;

    std::list<int>::iterator it;
    for (it = graph->adjList[vertice].begin(); it != graph->adjList[vertice].end(); it++) {
        if (!isAlreadyVisited[*it])
            DFS1(graph, isAlreadyVisited, *it);
    }

    graph->addToDfsOrder(vertice);
}

// walk on the inverse graph, stores the strongly connected component
void DFS2(Graph* graph, int* isAlreadyVisitedInv, int vertice, int counter) {
    isAlreadyVisitedInv[vertice] = 1;

    std::list<int>::iterator it;
    for (it = graph->adjListInv[vertice].begin(); it != graph->adjListInv[vertice].end(); it++) {
        if (!isAlreadyVisitedInv[*it])
            DFS2(graph, isAlreadyVisitedInv, *it, counter);
    }
    
    graph->stronglyConnectedComponent[vertice] = counter;
}

void dephtFirstSearch(Graph *graph) {
    // create array to mark visited vertices in normal DFS
    int* isAlreadyVisited = new int[graph->size];
    for (int i = 0; i < graph->size; i++) {
        isAlreadyVisited[i] = 0;
    }

    // create array to mark visited vertices in DFS1 order
    int* isAlreadyVisitedInv = new int[graph->size];
    for (int i = 0; i < graph->size; i++) {
        isAlreadyVisitedInv[i] = 0;
    }

    // normal DFS to create an order
    for (int i = 0; i < graph->size; i++) {
        if (!isAlreadyVisited[i]) {
            DFS1(graph, isAlreadyVisited, i);
        } 
    }

    // DFS in DFS1 order
    int counter = 0;
    for (int i = graph->dfsOrderCount-1; i >= 0; i--) {
        int vertice = graph->dfsOrder[i];

        if (!isAlreadyVisitedInv[vertice]) {
            DFS2(graph, isAlreadyVisitedInv, vertice, counter);
            counter++;
        }
    } 
}

Graph* createAdjList(int numFollowers, int numProposals) {
    Graph* graph = new Graph(2*numProposals);
   
    for (int i = 0; i < numFollowers; i++) {
        int accProposal1, accProposal2, rejProposal1, rejProposal2;
        // receive the proposals accepted and rejected by a follower
        std::cin >> accProposal1;
        std::cin >> accProposal2;
        std::cin >> rejProposal1;
        std::cin >> rejProposal2;
        accProposal1--;
        accProposal2--;
        rejProposal1--;
        rejProposal2--;

        // adjList
        // accepted proposals treatment
        if (accProposal1 == -1 || accProposal2 == -1) {
            if (accProposal1 == -1 && accProposal2 != -1) 
                graph->adjList[accProposal2+numProposals].push_back(accProposal2); // Y' -> Y  
            if (accProposal2 == -1 && accProposal1 != -1) 
                graph->adjList[accProposal1+numProposals].push_back(accProposal1); // X' -> X  
        } else {
            graph->adjList[accProposal1+numProposals].push_back(accProposal2); // X' -> Y 
            graph->adjList[accProposal2+numProposals].push_back(accProposal1); // Y' -> X
        }
        
        // rejected proposals treatment
        if (rejProposal1 == -1 || rejProposal2 == -1) {
            if (rejProposal1 == -1 && rejProposal2 != -1) 
                graph->adjList[rejProposal2].push_back(rejProposal2+numProposals); // Y -> Y'
            if (rejProposal2 == -1 && rejProposal1 != -1) 
                graph->adjList[rejProposal1].push_back(rejProposal1+numProposals); // X -> X'
        } else {
            graph->adjList[rejProposal1].push_back(rejProposal2+numProposals); // X -> Y'
            graph->adjList[rejProposal2].push_back(rejProposal1+numProposals); // Y -> X'
        }

        // adjListInv
        // accepted proposals treatment
        if (accProposal1 == -1 || accProposal2 == -1) {
            if (accProposal1 == -1 && accProposal2 != -1) 
                graph->adjListInv[accProposal2].push_back(accProposal2+numProposals); // Y' -> Y  
            if (accProposal2 == -1 && accProposal1 != -1) 
                graph->adjListInv[accProposal1].push_back(accProposal1+numProposals); // X' -> X  
        } else {
            graph->adjListInv[accProposal2].push_back(accProposal1+numProposals); // X' -> Y 
            graph->adjListInv[accProposal1].push_back(accProposal2+numProposals); // Y' -> X
        }
        
        // rejected proposals treatment
        if (rejProposal1 == -1 || rejProposal2 == -1) {
            if (rejProposal1 == -1 && rejProposal2 != -1) 
                graph->adjListInv[rejProposal2+numProposals].push_back(rejProposal2); // Y -> Y'
            if (rejProposal2 == -1 && rejProposal1 != -1) 
                graph->adjListInv[rejProposal1+numProposals].push_back(rejProposal1); // X -> X'
        } else {
            graph->adjListInv[rejProposal2+numProposals].push_back(rejProposal1); // X -> Y'
            graph->adjListInv[rejProposal1+numProposals].push_back(rejProposal2); // Y -> X'
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
        Graph* graph = createAdjList(numFollowers, numProposals);

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