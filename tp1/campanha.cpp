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
    this->order = std::vector<int>(this->size, -1);
    this->orderCount = 0;
    
    // create adjList, a vector with lists
    this->adjList = std::vector<std::list<int>>(this->size);
    for (int i = 0; i < this->size; i++) {
        this->adjList[i] = std::list<int>();
    }
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

    std::list<int>::iterator it;
    for (it = graph->adjList[vertice].begin(); it != graph->adjList[vertice].end(); it++) {
        if (!isAlreadyVisited[*it])
            DFS1(graph, isAlreadyVisited, *it);
    }

    graph->addToOrder(vertice);
}

void DFS2(Graph* graph, int* isAlreadyVisitedInv, int vertice, int counter) {
    if (isAlreadyVisitedInv[vertice])
        return;

    isAlreadyVisitedInv[vertice] = 1;

    std::list<int>::iterator it;
    for (it = graph->adjList[vertice].begin(); it != graph->adjList[vertice].end(); it++) {
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

void printList(Graph graph) {
    for (int i = 0; i < graph.size; i++) {
        std::cout << i << " -> ";
        std::list<int>::iterator it;
        for (it = graph.adjList[i].begin(); it != graph.adjList[i].end(); it++) {
            std::cout << *it << " / ";
        }
        std::cout << std::endl;
    }
    
}

Graph* createAdjList(int numFollowers, int numProposals) {
    Graph* graph = new Graph(2*numProposals);
   
    for (int i = 0; i < numFollowers; i++) {
        int accProposal1, accProposal2, rejProposal1, rejProposal2;
        std::cin >> accProposal1;
        std::cin >> accProposal2;
        std::cin >> rejProposal1;
        std::cin >> rejProposal2;

        std::cout << accProposal1;
        std::cout << accProposal2;
        std::cout << rejProposal1;
        std::cout << rejProposal2;
        std::cout << std::endl;

        // accepted proposals treatment
        if (accProposal1 == 0 || accProposal2 == 0) {
            if (accProposal1 == 0 && accProposal2 != 0) 
                graph->adjList[accProposal2+numProposals].push_back(accProposal2); // Y' -> Y  
            if (accProposal2 == 0 && accProposal1 != 0) 
                graph->adjList[accProposal1+numProposals].push_back(accProposal1); // X' -> X  
        } else {
            graph->adjList[accProposal1+numProposals].push_back(accProposal2); // X' -> Y 
            graph->adjList[accProposal2+numProposals].push_back(accProposal1); // Y' -> X
        }
        
        // rejected proposals treatment
        if (rejProposal1 == 0 || rejProposal2 == 0) {
            if (rejProposal1 == 0 && rejProposal2 != 0) 
                graph->adjList[rejProposal2].push_back(rejProposal2+numProposals); // Y -> Y'
            if (rejProposal2 == 0 && rejProposal1 != 0) 
                graph->adjList[rejProposal1].push_back(rejProposal1+numProposals); // X -> X'
        } else {
            graph->adjList[rejProposal1].push_back(rejProposal2+numProposals); // X -> Y'
            graph->adjList[rejProposal2].push_back(rejProposal1+numProposals); // Y -> X'
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
        
        printList(*graph);

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