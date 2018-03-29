#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "array_helpers.h"

/* Global macros */
#define N_NODES 5
#define VALID_BOUND(I) ((I) >= 0 && (I) < N_NODES)


int main(void)
{
    Graph *graph = NewGraph(N_NODES);
    int i, *neighbors = NULL;

    printf("Add links for node 0\n");
    AddEdge(0, 1, graph);   // 0 -> 1
    AddEdge(0, 2, graph);   // 0 -> 2
    AddEdge(0, 3, graph);   // 0 -> 3
    AddEdge(0, 4, graph);   // 0 -> 4
    printf("-- 0 has %d edges\n", graph->adjacencyList[0].size);

    AddEdge(0, 0, graph);   // 0 -> 0 has no effect
    AddEdge(1, 0, graph);   // 1 -> 0 is the same as 0 -> 1
    AddEdge(2, 0, graph);   // 2 -> 0 is the same as 0 -> 2
    AddEdge(3, 0, graph);   // 3 -> 0 is the same as 0 -> 3
    AddEdge(4, 0, graph);   // 4 -> 0 is the same as 0 -> 4
    printf("Adding duplicate links would not be counted\n");
    printf("-- 0 has %d edges\n", graph->adjacencyList[0].size);

    // print all neighbor nodes
    for (i = 0; i < N_NODES; ++i) {
        neighbors = Neighbors(i, graph);
        printf("-- %d's neighbors: {", i);
        printArray(neighbors, graph->adjacencyList[i].size);
        printf(" }\n");

        // free
        free(neighbors);
        neighbors = NULL;
    }

    // print all adjacency list size
    printf("Adjacency list size:\n");
    for (i = 0; i < N_NODES; ++i) {
        printf("-- %d has %d edges\n", i, graph->adjacencyList[i].size);
    }

    AddEdge(1, 2, graph);
    AddEdge(1, 3, graph);
    AddEdge(1, 4, graph);
    AddEdge(2, 3, graph);
    AddEdge(2, 4, graph);
    AddEdge(3, 4, graph);

    // print all adjacency list size
    printf("Fully connected graph:\n");
    for (int i = 0; i < N_NODES; ++i) {
        printf("-- %d has %d edges\n", i, graph->adjacencyList[i].size);
    }

    // free
    DestroyGraph(graph);
}

Graph *NewGraph(int n)
{
    Graph *graph = malloc(sizeof(Graph));

    graph->vertices = n;
    graph->edges = 0;
    // max edges of a graph is n choose 2
    graph->maxEdges = 1/2.0 * n * (n-1);
    graph->adjacencyList = malloc(n * sizeof(LinkedList));

    // initialize adjacency list
    for (int i = 0; i < n; ++i) {
        graph->adjacencyList[i].size = 0;
        graph->adjacencyList[i].head = NULL;
    }

    return graph;
}

void DestroyGraph(Graph *graph)
{
    if (graph != NULL) {
        free(graph->adjacencyList);
        free(graph);
    }
    graph = NULL;
}

void AddItem(LinkedList *list, int data)
{
    LinkedListNode *node = malloc(sizeof(LinkedListNode));

    node->data = data;
    // add item to head of the linked list
    node->next = list->size == 0 ? NULL : list->head;
    list->head = node;
    ++(list->size);
}

bool ItemExist(const LinkedList *list, const int data)
{
    if (list->size > 0) {
        LinkedListNode *current = list->head;

        while (NULL != current) {
            if (current->data == data) {
                return true;
            }
            current = current->next;
        }
    }
    return false;
}

/* AddEdge - add link/edge to two nodes "u" and "v" in a graph.
 *
 * Check the bound of "u" and "v":
 *    u > 0 and u < graph->vertices
 *    v > 0 and v < graph->vertices.
 *
 * "u" must not equal to "v" and graph->maxEdges is the upper bound of the
 * number of edges the graph can have.
 */
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

    if (u != v && graph->edges <= graph->maxEdges) {
        // it is faster to check the smaller linked list
        if (graph->adjacencyList[u].size < graph->adjacencyList[v].size) {
            if (ItemExist(&graph->adjacencyList[u], v))
                return;
        }
        else {
            if (ItemExist(&graph->adjacencyList[v], u))
                return;
        }

        // undirect graph: add links for both "u" -> "v" and "v" and "u"
        AddItem(&graph->adjacencyList[u], v);
        AddItem(&graph->adjacencyList[v], u);
        graph->edges += 1;
    }
}

int *Neighbors(int v, Graph *graph)
{
    int *neighbors = malloc(graph->adjacencyList[v].size * sizeof(int));
    LinkedList *list = &graph->adjacencyList[v];
    LinkedListNode *current = list->head;
    int i = 0;

    while (NULL != current) {
        neighbors[i++] = current->data;
        current = current->next;
    }
    return neighbors;
}
