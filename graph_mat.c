#include <stdio.h>
#include <stdlib.h>

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

    AddEdge(1, 2, graph);   // 1 -> 2
    AddEdge(1, 3, graph);   // 1 -> 3

    // do not allow recursive edge to itself
    AddEdge(3, 3, graph);
    printf("Adjacency matrix:\n");
    printTable(graph->adjacencyMatrix, N_NODES, N_NODES);
    printf("\n");

    // free
    DestroyGraph(graph);
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
