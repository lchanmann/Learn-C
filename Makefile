quicksort:
	gcc quicksort.c array_helpers.c -lsodium -o bin/quicksort && ./bin/quicksort

.PHONY: quicksort
