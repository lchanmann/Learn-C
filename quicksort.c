#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    int array_3_first_smallest[] = { 1, 3, 2 };
    quicksort(array_3_first_smallest, 3);

    int array_3_last_largest[] = { 2, 1, 3 };
    quicksort(array_3_last_largest, 3);

    int array_3_middle_median[] = { 3, 1, 2 };
    quicksort(array_3_middle_median, 3);

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
    printf("):\n");

    // Default quicksort with partition walk from both sides
    _quicksort(array, 0, size - 1);
    printf("-- %-15s:", "default");
    printArray(array, size);
    printf("\n");

    // quicksort with the first element as the pivot
    memcpy(array, array_orig, mem_size);
    _quicksortLeftPivot(array, 0, size - 1);
    printf("-- %-15s:", "left pivot");
    printArray(array, size);
    printf("\n");

    // quicksort with the last element as the pivot
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

void _quicksortLeftPivot(int array[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int pivot = array[left];
    // The default partition will also work for quicksort using the first
    // element as the pivot. For special case when array has only 2 elements
    // the default _quicksort() is essentially equivalent to _quicksortLeftPivot().
    int position = partition(array, left, right, pivot);

    _quicksortLeftPivot(array, left, position - 1);
    _quicksortLeftPivot(array, position, right);
}

void _quicksortRightPivot(int array[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int pivot = array[right];
    // When the last element is used as the pivot the default partition walk
    // might NOT work because the partition point/position could overshoot the
    // array upperbound index by 1 when the last element is the largest element.
    int position = partitionRightPivot(array, left, right, pivot);

    _quicksortRightPivot(array, left, position - 1);
    _quicksortRightPivot(array, position, right);
}

int partitionRightPivot(int array[], int left, int right, int pivot)
{
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (array[j] <= pivot) {
            ++i;
            swap(array + i, array + j);
        }
    }
    ++i;
    swap(array + i, array + right);

    return i;
}
