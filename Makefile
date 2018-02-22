# Global variables
CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS = -lsodium -lpthread

OUTPUT_OPTION = -o bin/$@
BUILD.c = $(CC) $(CFLAGS) $(LDFLAGS) $(OUTPUT_OPTION) $@.c
RUN_IT = ./bin/$@

quicksort binary_heap mergesort: bin/array_helpers.o
	$(BUILD.c) $^ && $(RUN_IT)

bit_ops readers_writers:
	$(BUILD.c) && $(RUN_IT)

bin/array_helpers.o: array_helpers.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: quicksort binary_heap bit_ops readers_writers mergesort
