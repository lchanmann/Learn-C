quicksort:
	gcc quicksort.c array_helpers.c -lsodium -o bin/quicksort && ./bin/quicksort

binary_heap:
	gcc binary_heap.c array_helpers.c -lsodium -o bin/binary_heap && ./bin/binary_heap

bit_ops:
	gcc bit_ops.c -o bin/bit_ops && ./bin/bit_ops

readers_writers:
	gcc readers_writers.c -lpthread -lsodium -o bin/readers_writers && ./bin/readers_writers

.PHONY: quicksort binary_heap bit_ops
