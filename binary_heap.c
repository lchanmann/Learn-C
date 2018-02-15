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

    printf("Insert data into the binary heap:\n");

    //              12
    BH_insert(&heap, size++, 12);

    printf("-- heap =");
    printArray(heap, size);
    printf("\n");

    //              11
    //             /
    //           12
    BH_insert(&heap, size++, 11);

    printf("-- heap =");
    printArray(heap, size);
    printf("\n");

    //              5
    //            /   \
    //          12     11
    BH_insert(&heap, size++, 5);

    printf("-- heap =");
    printArray(heap, size);
    printf("\n");

    //              5
    //            /   \
    //          10     8
    //         /  \   /
    //       12   15 11
    BH_insert(&heap, size++, 10);
    BH_insert(&heap, size++, 15);
    BH_insert(&heap, size++, 8);

    printf("-- heap =");
    printArray(heap, size);
    printf("\n");

    int min = BH_extractMin(&heap, &size);
    printf("Extract the smallest element (%d) from the heap:\n", min);

    //              8
    //            /   \
    //          10     11
    //         /  \
    //       12   15
    printf("-- heap =");
    printArray(heap, size);
    printf("\n");

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

int BH_extractMin(int **heapPtr, int *size)
{
    int min = (*heapPtr)[0];

    BH_delete(heapPtr, size, 0);
    return min;
}

void BH_delete(int **heapPtr, int *size, int index)
{
    int newSize = --(*size);

    // Replace the deleted element with the last element
    (*heapPtr)[index] = (*heapPtr)[newSize];

    // Shrink the memory block for the heap
    *heapPtr = (int *) realloc(*heapPtr, newSize * sizeof(int));

    // Bubble down the replacement element
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        // No more children to process
        if (left > newSize - 1) return;

        // Find the smallest children
        int k = (right < newSize - 1 && (*heapPtr)[right] < (*heapPtr)[left]) ? right : left;

        // If the current element is the smallest the heap is in good shape
        if ((*heapPtr)[index] < (*heapPtr)[k]) return;

        // Swap the current element with its smaller child
        swap(*heapPtr + index, *heapPtr + k);
        index = k;
    }
}
