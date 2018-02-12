quicksort:
	gcc quicksort.c array_helpers.c -lsodium -o bin/quicksort && ./bin/quicksort

binary_heap:
	gcc binary_heap.c array_helpers.c -lsodium -o bin/binary_heap && ./bin/binary_heap

.PHONY: quicksort binary_heap
