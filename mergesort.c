#include <stdio.h>

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
}
