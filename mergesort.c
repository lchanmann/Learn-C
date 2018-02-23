#include <stdio.h>
#include <string.h>

#include "array_helpers.h"
#include "mergesort.h"

/* Global constants */
#define MAX_ARRAY_SIZE 20

/* Helper functions declaration */
void run_mergesort(int array[], int size);


int main(void)
{
    int array_0[] = { };
    run_mergesort(array_0, 0);

    int array_1[] = { 1 };
    run_mergesort(array_1, 1);

    int array_2[] = { 2, 1 };
    run_mergesort(array_2, 2);

    int array_2_sorted[] = { 1, 2 };
    run_mergesort(array_2_sorted, 2);

    int array_2_same[] = { 1, 1 };
    run_mergesort(array_2_same, 2);

    int array_3_first_smallest[] = { 1, 3, 2 };
    run_mergesort(array_3_first_smallest, 3);

    int array_3_last_largest[] = { 2, 1, 3 };
    run_mergesort(array_3_last_largest, 3);

    int array_3_middle_median[] = { 3, 2, 1 };
    run_mergesort(array_3_middle_median, 3);

    int array_even[4];
    populateArray(array_even, 4);
    run_mergesort(array_even, 4);

    int array_odd[4];
    populateArray(array_odd, 5);
    run_mergesort(array_odd, 5);

    int array[MAX_ARRAY_SIZE];
    populateArray(array, MAX_ARRAY_SIZE);
    run_mergesort(array, MAX_ARRAY_SIZE);
}


void run_mergesort(int array[], int size)
{
    printf("mergesort(");
    printArray(array, size);
    printf(") ->");

    mergesort(array, 0, size - 1);

    printArray(array, size);
    printf("\n");
}

void mergesort(int array[], int left, int right)
{
    if (left < right) {
        int middle = (left + right) / 2;

        // Recursive mergesort on left and right sub-array
        mergesort(array, left, middle);
        mergesort(array, middle + 1, right);

        // Merge and sort the array
        merge(array, left, middle, right);
    }
}

void merge(int array[], int left, int middle, int right)
{
    int size = right - left + 1;
    int sorted[size];

    int i = left;                   // left sub-array pointer
    int j = middle + 1;             // right sub-array pointer
    int k = 0;

    // Merge the sub-arrays and sort their elements along the way
    while (i <= middle) {
        sorted[k++] = (j <= right && array[j] < array[i]) ?
            array[j++] : array[i++];
    }

    // Update the original array with the sorted array
    memcpy(array + left, sorted, k * sizeof(int));
}
