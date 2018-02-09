#include <stdio.h>
#include "quicksort.h"
#include "array_helpers.h"

/* Global constants */
#define MAX_ARRAY_SIZE 20

int main(void)
{
    int size;

    for (size = 0; size < MAX_ARRAY_SIZE; ++size) {
        int array[size];

        populateArray(array, size);
        quicksort(array, size);
    }
}

void quicksort(int array[], int size)
{
    printf("quicksort(");
    printArray(array, size);
    printf(")");

    _quicksortRightPivot(array, 0, size - 1);

    printf(" =>");
    printArray(array, size);
    printf("\n");
}

void _quicksort(int array[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int pivot = array[(left + right) / 2];
    int position = partition(array, left, right, pivot);

    _quicksort(array, left, position - 1);
    _quicksort(array, position, right);
}

int partition(int array[], int left, int right, int pivot)
{
    while (left <= right) {
        while (array[left] < pivot) ++left;
        while (array[right] > pivot) --right;

        if (left <= right) {
            swap(array + left, array + right);
            ++left; --right;
        }
    }

    return left;
}

void _quicksortRightPivot(int array[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int position = partitionByPivotIndex(array, left, right, right);

    _quicksortRightPivot(array, left, position - 1);
    _quicksortRightPivot(array, position, right);
}

int partitionByPivotIndex(int array[], int left, int right, int pivotIndex)
{
    int i = left - 1;

    for(int j = left; j <= right; ++j) {
        if (j == pivotIndex) {
            continue;
        }

        if (array[j] <= array[pivotIndex]) {
            ++i;
            swap(array + i, array + j);
        }
    }
    ++i;
    swap(array + i, array + pivotIndex);

    return i;
}
