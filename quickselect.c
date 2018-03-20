#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include <string.h>

#include "array_helpers.h"
#include "quickselect.h"

/* Global constants */
#define MAX_ARRAY_SIZE 10

/* comparison function for qsort */
int compare(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}


int main(void)
{
    int array[MAX_ARRAY_SIZE];
    int *array_orig;
    int mem_size;

    mem_size = MAX_ARRAY_SIZE * sizeof(int);
    array_orig = malloc(mem_size);
    populateArray(array_orig, MAX_ARRAY_SIZE);
    memcpy(array, array_orig, mem_size);

    printf("array: ");
    printArray(array, MAX_ARRAY_SIZE);
    printf("\n");

    for (int k = 1; k <= MAX_ARRAY_SIZE; ++k) {
        int kth;

        kth = quickselect(k, array, MAX_ARRAY_SIZE);
        printf("-- quickselect(%d, array): %d\n", k, kth);
        memcpy(array, array_orig, mem_size);
    }

    // Print the array in sorted order for evaluation
    qsort(array, MAX_ARRAY_SIZE, sizeof(int), compare);
    printf("sorted:");
    printArray(array, MAX_ARRAY_SIZE);
}

int quickselect(int k, int array[], int size)
{
    // Safety check
    if (k < 1 || k > size) {
        fprintf(stderr, "Error: k is out of bound.");
        exit(1);
    }

    return quickselectRecursive(k, array, 0, size - 1);
}

int quickselectRecursive(int k, int array[], int left, int right)
{
    int pivot_location;

    // Partition the array and getting the location of pivot
    pivot_location = partition(array, left, right);
    if (k - 1 == pivot_location) {
        return array[pivot_location];
    }
    else if (k - 1 < pivot_location) {
        return quickselectRecursive(k, array, left, pivot_location - 1);
    }
    else {
        return quickselectRecursive(k, array, pivot_location + 1, right);
    }
}

int partition(int array[], int left, int right)
{
    int index, pivot;
    int wall, j;

    // Choose a pivot at random
    index = left + randombytes_uniform(right - left + 1);
    pivot = array[index];

    // Swap the pivot to the rightmost to simplify walking through
    // the array and comparing each elements against the pivot
    swap(array + index, array + right);

    // Walk through the array and put the pivot in the correct position
    wall = left - 1;
    for (j = left; j < right; ++j) {
        if (array[j] <= pivot) {
            ++wall;
            swap(array + j, array + wall);
        }
    }
    ++wall;
    swap(array + wall, array + right);

    return wall;
}
