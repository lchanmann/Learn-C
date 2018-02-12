#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

void BH_insert(int **heapPtr, int size, int data);
int BH_extractMin(int **heapPtr, int *size);
void BH_delete(int **heapPtr, int *size, int index);

#endif /* _BINARY_HEAP_H_ */
