#include <stdio.h>

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i) {
        printf(" %d", array[i]);
    }
}

void swap(int *a, int *b)
{
    if (a == b) {
        return;
    }

    int temp = *a;
    *a = *b;
    *b = temp;
}
