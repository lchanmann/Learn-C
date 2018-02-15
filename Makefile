quicksort:
	gcc quicksort.c array_helpers.c -lsodium -o bin/quicksort && ./bin/quicksort

binary_heap:
	gcc binary_heap.c array_helpers.c -lsodium -o bin/binary_heap && ./bin/binary_heap

bit_ops:
	gcc bit_ops.c -o bin/bit_ops && ./bin/bit_ops

.PHONY: quicksort binary_heap bit_ops
