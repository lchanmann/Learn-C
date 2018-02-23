#include <stdio.h>
#include <string.h>

#include "array_helpers.h"
#include "mergesort.h"

/* Global constants */
#define MAX_ARRAY_SIZE 20

/* Helper functions declaration */
void runMergesort(int array[], int size);


int main(void)
{
    int array_0[] = { };
    runMergesort(array_0, 0);

    int array_1[] = { 1 };
    runMergesort(array_1, 1);

    int array_2[] = { 2, 1 };
    runMergesort(array_2, 2);

    int array_2_sorted[] = { 1, 2 };
    runMergesort(array_2_sorted, 2);

    int array_2_same[] = { 1, 1 };
    runMergesort(array_2_same, 2);

    int array_3_first_smallest[] = { 1, 3, 2 };
    runMergesort(array_3_first_smallest, 3);

    int array_3_last_largest[] = { 2, 1, 3 };
    runMergesort(array_3_last_largest, 3);

    int array_3_middle_median[] = { 3, 2, 1 };
    runMergesort(array_3_middle_median, 3);

    int array_even[4];
    populateArray(array_even, 4);
    runMergesort(array_even, 4);

    int array_odd[4];
    populateArray(array_odd, 5);
    runMergesort(array_odd, 5);

    int array[MAX_ARRAY_SIZE];
    populateArray(array, MAX_ARRAY_SIZE);
    runMergesort(array, MAX_ARRAY_SIZE);

    // Return inversion count from mergesort
    //
    // Inversion count is the count of out-of-order element pairs
    // i.e. array[i] > array[j] and i < j
    int an_array[] = { 38, 27, 43, 9, 82, 10 };
    int size = sizeof(an_array) / sizeof(int);

    // Inversion pairs in the array are:
    // (38, 27)
    // (82, 10)
    // (27, 9) (38, 9) (43, 9)
    // (27, 10) (38, 10) (43, 10)
    // the total inversion count = 8
    printf("mergesort(");
    printArray(an_array, size);
    printf("):\n");

    int inv_count = mergesort(an_array, 0, size - 1);

    printf("-- inversion count = %d\n", inv_count);
}


void runMergesort(int array[], int size)
{
    printf("mergesort(");
    printArray(array, size);
    printf("):\n");

    mergesort(array, 0, size - 1);

    printArray(array, size);
    printf("\n");
}

int mergesort(int array[], int left, int right)
{
    int inv_count = 0;
    if (left < right) {
        int middle = (left + right) / 2;

        // Recursive mergesort on left and right sub-array
        inv_count = mergesort(array, left, middle);
        inv_count += mergesort(array, middle + 1, right);

        // Merge and sort the array
        inv_count += merge(array, left, middle, right);
    }

    return inv_count;
}

int merge(int array[], int left, int middle, int right)
{
    int size = right - left + 1;
    int sorted[size];

    int i = left;                   // left sub-array pointer
    int j = middle + 1;             // right sub-array pointer
    int k = 0;
    int inv_count = 0;

    // Merge the sub-arrays and sort their elements along the way
    while (i <= middle) {
        if (j <= right && array[j] < array[i]) {
            sorted[k] = array[j++];
            // Mergesort presumes left and right sub-arrays are already sorted.
            //
            // When an element from the right sub-array is smaller one in the left,
            // it is guaranteed to be smaller than the rest of the elements
            // in the left sub-array. Thus, inversion pairs can be constructed
            // with all of those elements.
            inv_count += middle - i + 1;

#ifdef _DEBUG_
            // Print out inversion pairs
            printf("-- inversion pairs: ");
            for (int c = i; c <= middle; ++c) {
                printf("(%d, %d) ", array[c], sorted[k]);
            }
            printf("\n");
#endif /* _SHOW_INVERSION_PAIRS */
        }
        else {
            sorted[k] = array[i++];
        }
        ++k;
    }

    // Update the original array with the sorted array
    memcpy(array + left, sorted, k * sizeof(int));

    // Return inversion count
    return inv_count;
}
