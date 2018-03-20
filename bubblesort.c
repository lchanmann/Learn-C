#include <stdio.h>
#include <string.h>

#include "array_helpers.h"
#include "bubblesort.h"

/* Global constants */
#define MAX_ARRAY_SIZE 10


int main(void)
{
    int array[MAX_ARRAY_SIZE];
    populateArray(array, MAX_ARRAY_SIZE);

    int array_clone[MAX_ARRAY_SIZE];
    memcpy(array_clone, array, MAX_ARRAY_SIZE * sizeof(int));

    printf("bubblesort(");
    printArray(array, MAX_ARRAY_SIZE);
    printf("):\n");
    // Start sorting
    bubblesort(array, MAX_ARRAY_SIZE);
    printf("sorted: ");
    printArray(array, MAX_ARRAY_SIZE);
    printf("\n\n");

    /** populateArray(array, MAX_ARRAY_SIZE); */
    printf("bubblesortLeftFirst(");
    printArray(array_clone, MAX_ARRAY_SIZE);
    printf("):\n");
    // Start sorting
    bubblesortLeftFirst(array_clone, MAX_ARRAY_SIZE);
    printf("sorted: ");
    printArray(array_clone, MAX_ARRAY_SIZE);
    printf("\n");
}

/* bubble the smaller elements to the right */
void bubblesort(int array[], int size)
{
    int i, swapped_at, counter = 0, swapped = 0;

    while (size != 0) {
        swapped_at = 0;
        for (i = 1; i < size; ++i) {
            if (array[i-1] > array[i]) {
                swap(array + i-1, array + i);
                swapped_at = i;
                ++swapped;
            }
            ++counter;
        }
        size = swapped_at;

        printf("-- ");
        printArray(array, MAX_ARRAY_SIZE);
        printf("\n");
    }
    printf("Total comparison: %d, swaped: %d, ", counter, swapped);
}

/* bubble the larger elements to the left */
void bubblesortLeftFirst(int array[], int size)
{
    int i, j, counter = 0, swapped = 0;

    // i range: [0, size-1)
    for (i = 0; i < size - 1; ++i) {
        // j range: [i+1, size-1)
        for (j = i + 1; j < size; ++j) {
            // by comparing and sorting the leftmost unsorted element first yield
            // optimal number of swap however it would need more comparisons
            // then the original optimized version of bubblesort above.
            if (array[i] > array[j]) {
                swap(array + i, array + j);
                ++swapped;
            }
            ++counter;
        }

        printf("-- ");
        printArray(array, MAX_ARRAY_SIZE);
        printf("\n");
    }
    printf("Total comparison: %d, swapped: %d, ", counter, swapped);
}
