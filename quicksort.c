#include <stdio.h>
#include "quicksort.h"

int main(void)
{
    printf("Quicksort:\n");

    int array[] = { 2, 1 };
    int size = sizeof(array) / sizeof(*array);

    quicksort(array, 0, size - 1);
    printArray(array, size);
}

void quicksort(int array[], int left, int right)
{
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i) {
        printf(" %d", array[i]);
    }
}
