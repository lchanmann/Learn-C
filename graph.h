#ifndef _GRAPH_H_
#define _GRAPH_H_

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
        int **adjacencyMatrix;
    };
} Graph;


Graph *NewGraph(int n);
void DestroyGraph(Graph *graph);
void AddEdge(int u, int v, Graph *graph);

#endif /* _GRAPH_H_ */
