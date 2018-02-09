#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

void quicksort(int array[], int size);
void _quicksort(int array[], int left, int right);
int partition(int array[], int left, int right, int pivot);

void _quicksortRightPivot(int array[], int left, int right);
int partitionByPivotIndex(int array[], int left, int right, int pivotIndex);

#endif /* _QUICK_SORT_H_ */
