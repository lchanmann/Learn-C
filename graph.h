#ifndef _GRAPH_H_
#define _GRAPH_H_

/* Define macros */
#define VALID_BOUND(I) ((I) >= 0 && (I) < N_NODES)

/* Custom types */
typedef struct _LinkedListNode {
    int data;
    struct _LinkedListNode *next;
} LinkedListNode;

typedef struct _LinkedList {
  LinkedListNode *head;
  int size;
} LinkedList;

typedef struct _Graph {
    int vertices;
    int edges;
    int maxEdges;
    union {
        LinkedList *adjacencyList;
        // store adjacency matrix in 1-dimensional array
        int *adjacencyMatrix;
    };
} Graph;

typedef struct _NodeList {
    int *data;
    int size;
} NodeList;


/* Function declaration */
Graph *NewGraph(int n);
void DestroyGraph(Graph *graph);
void AddEdge(int u, int v, Graph *graph);
NodeList *Neighbors(int v, Graph *graph);

void DestroyNodeList(NodeList *list)
{
    if (NULL != list) {
        free(list->data);
        free(list);
    }
    list = NULL;
}

#endif /* _GRAPH_H_ */
