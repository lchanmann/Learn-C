#include <stdio.h>
#include <stdlib.h>
#include "binary_heap.h"
#include "array_helpers.h"

int main(void)
{
    // Binary heap is a complete binary tree whose elements are arranged such that
    // parent nodes are either smaller than thier children (min heap) or larger
    // (max heap).
    //
    // E.g. Min heap
    //              5
    //            /   \
    //          10     8
    //         /  \   /
    //       12   15 11
    //
    // I assume min heap from now on as the same concept for insertion, delete
    // and other operations is also applied for max heap.

    int size = 0;
    int *heap = NULL;

    //              15
    BH_insert(&heap, size++, 15);

    //              11
    //             /
    //           15
    BH_insert(&heap, size++, 11);

    //              5
    //            /   \
    //          15     11
    BH_insert(&heap, size++, 5);

    printArray(heap, size);
    free(heap);
}

void BH_insert(int **heapPtr, int size, int data)
{
    int index = size++;

    // Resize the heap at every insert for now
    *heapPtr = (int *) realloc(*heapPtr, size * sizeof(int));

    // Insert data to the end of the heap.
    // -- parentheses is needed as pointer indirection has lower precedence than indexing
    (*heapPtr)[index] = data;

    // Bubble up
    while (index > 0) {
        int parent = (index - 1) / 2;

        if ((*heapPtr)[parent] <= (*heapPtr)[index]) {
            return;
        }

        swap(*heapPtr + index, *heapPtr + parent);
        index = parent;
    }
}
