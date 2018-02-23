#include <stdio.h>
#include <string.h>

#include "array_helpers.h"
#include "mergesort.h"

int main(void)
{
    int array[] = { 38, 27, 43, 9, 82, 10 };
    int size = sizeof(array) / sizeof(int);

    mergesort(array, 0, size - 1);
    printArray(array, size);
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
