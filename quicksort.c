#include <stdio.h>
#include "quicksort.h"
#include "array_helpers.h"

int main(void)
{
    printf("Quicksort:\n");

    int array[] = { 12, 5, 8, 9, 2 };
    int size = sizeof(array) / sizeof(*array);

    quicksort(array, 0, size - 1);
    printArray(array, size);
}

void quicksort(int array[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int pivot = array[(left + right) / 2];
    int position = partition(array, left, right, pivot);

    quicksort(array, left, position - 1);
    quicksort(array, position, right);
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
