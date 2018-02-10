#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

void quicksort(int array[], int size);
void _quicksort(int array[], int left, int right);
int partition(int array[], int left, int right, int pivot);

void _quicksortLeftPivot(int array[], int left, int right);
void _quicksortRightPivot(int array[], int left, int right);
int partitionRightPivot(int array[], int left, int right, int pivot);
int partitionLeftPivot(int array[], int left, int right, int pivot);

#endif /* _QUICK_SORT_H_ */
