#include <stdio.h>
#include <sodium.h>

#define MAX_RANDOM_INT 10

void populateArray(int array[], int size)
{
    for (int i = 0; i < size; ++i) {
        array[i] = randombytes_uniform(MAX_RANDOM_INT);
    }
}

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
