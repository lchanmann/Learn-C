#include <stdio.h>
#include "quicksort.h"
#include "array_helpers.h"

/* Global constants */
#define MAX_ARRAY_SIZE 20

int main(void)
{
    int array_0[] = { };
    quicksort(array_0, 0);

    int array_1[] = { 1 };
    quicksort(array_1, 1);

    int array_2[] = { 2, 1 };
    quicksort(array_2, 2);

    int array_2_sorted[] = { 1, 2 };
    quicksort(array_2_sorted, 2);

    int array_2_same[] = { 1, 1 };
    quicksort(array_2_same, 2);

    int array_even[4];
    populateArray(array_even, 4);
    quicksort(array_even, 4);

    int array_odd[4];
    populateArray(array_odd, 5);
    quicksort(array_odd, 5);

    int array[MAX_ARRAY_SIZE];
    populateArray(array, MAX_ARRAY_SIZE);
    quicksort(array, MAX_ARRAY_SIZE);
}

void quicksort(int array[], int size)
{
    int mem_size = size * sizeof(int);
    int *array_orig = malloc(mem_size);

    // Backup the original array
    memcpy(array_orig, array, mem_size);

    printf("quicksort(");
    printArray(array, size);
    printf("):\n");

    // Default quicksort with partition walk from both sides
    _quicksort(array, 0, size - 1);
    printf("-- %-15s:", "default");
    printArray(array, size);
    printf("\n");

    // quicksort with the right most element as the pivot
    memcpy(array, array_orig, mem_size);
    _quicksortRightPivot(array, 0, size - 1);
    printf("-- %-15s:", "right pivot");
    printArray(array, size);
    printf("\n");

    // Spacing
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
