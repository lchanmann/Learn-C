#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Local h files */
#include "graph.h"
#include "array_helpers.h"

/* Global macros */
#define N_NODES 5


int main(void)
{
    Graph *graph = NewGraph(N_NODES);

    printf("Add links to node 0\n");
    AddEdge(0, 1, graph);   // 0 -> 1
    AddEdge(0, 4, graph);   // 0 -> 4
    // adding already existing edge has no effect on the adjacency matrix
    AddEdge(0, 4, graph);

    // adding edge 1 -> 2 is the same as 2 -> 1
    AddEdge(1, 2, graph);   // 1 -> 2
    AddEdge(2, 1, graph);   // 2 -> 1

    // do not allow recursive edge to itself
    AddEdge(3, 3, graph);
    printf("Adjacency matrix:\n");
    printTable(graph->adjacencyMatrix, N_NODES, N_NODES);

    NodeList *neighbors = Neighbors(0, graph);
    // print neighbors of node 0
    printf("Node 0's neighbors: {");
    printArray(neighbors->data, neighbors->size);
    printf(" }\n");

    // free
    DestroyGraph(graph);
    DestroyNodeList(neighbors);
}

Graph *NewGraph(int n)
{
    Graph *graph = malloc(sizeof(Graph));

    graph->vertices = n;
    graph->edges = 0;
    graph->maxEdges = 1/2.0 * n * (n-1);
    graph->adjacencyMatrix = malloc(n*n * sizeof(int));

    // initialize adjacency matrix
    for (int i = 0; i < n*n; ++i) {
        graph->adjacencyMatrix[i] = 0;
    }

    return graph;
}

void DestroyGraph(Graph *graph)
{
    if (NULL != graph) {
        free(graph->adjacencyMatrix);
        free(graph);
    }
    graph = NULL;
}

void AddEdge(int u, int v, Graph *graph)
{
    if (!VALID_BOUND(u)) {
        fprintf(stderr, "u(%d) is out of bound.", u);
        exit(1);
    }

    if (!VALID_BOUND(v)) {
        fprintf(stderr, "v(%d) is out of bound.", u);
        exit(1);
    }

    if (u != v) {
        graph->adjacencyMatrix[u * N_NODES + v] = 1;
        graph->adjacencyMatrix[v * N_NODES + u] = 1;
    }
}

NodeList *Neighbors(int v, Graph *graph)
{
    NodeList *neighbors = malloc(sizeof(NodeList));
    neighbors->size = 0;

    int i = 0, j;
    int temp[N_NODES - 1];
    int memSize = 0;

    for (j = 0; j < N_NODES; ++j) {
        if (graph->adjacencyMatrix[v * N_NODES + j] == 1) {
            temp[i++] = j;
            neighbors->size += 1;
        }
    }
    // copy temp to neighbor data
    memSize = neighbors->size * sizeof(int);
    neighbors->data = malloc(memSize);
    memcpy(neighbors->data, temp, memSize);

    return neighbors;
}
