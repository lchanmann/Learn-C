# Global variables
CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS = -lsodium -lpthread

OUTPUT_OPTION = -o bin/$@
BUILD.c = $(CC) $(CFLAGS) $(LDFLAGS) $(OUTPUT_OPTION)
RUN_IT = ./bin/$@

quicksort binary_heap mergesort quickselect bubblesort graph_adj graph_mat: bin/array_helpers.o
	$(BUILD.c) $@.c $^ && $(RUN_IT)

bit_ops readers_writers socket_server:
	$(BUILD.c) $@.c && $(RUN_IT)

bin/array_helpers.o: array_helpers.c
	$(CC) $(CFLAGS) -o $@ -c $<

# NOTE: follow https://gist.github.com/gravitylow/fb595186ce6068537a6e9da6d8b5b96d
# to allow debugging on macos Sierra and higher. Also need to downgrade gdb to 8.0.1
# as the latest gdb 8.1 doesn't work at the moment.
%_debug: bin/array_helpers.o
	$(BUILD.c) -D_DEBUG_ -g $*.c $^ && gdb $(RUN_IT)


.PHONY: quicksort binary_heap bit_ops readers_writers mergesort socket_server
