#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sodium.h>
#include "readers_writers.h"

// Global constants
#define NUM_READERS 5
#define NUM_WRITERS 5

#define NUM_READ 5
#define NUM_WRITE 5

// Shared data
int gSharedValue;

pthread_mutex_t gSharedValueLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t gReadPhase = PTHREAD_COND_INITIALIZER;
pthread_cond_t gWritePhase = PTHREAD_COND_INITIALIZER;

int gReaderCount = 0;


int main(void)
{
    int i;

    int readerIds[NUM_READERS];
    int writerIds[NUM_WRITERS];

    pthread_t readerThreads[NUM_READERS];
    pthread_t writerThreads[NUM_WRITERS];

    // Start reader threads
    for (i = 0; i < NUM_READERS; ++i) {
        readerIds[i] = i;
        pthread_create(&readerThreads[i], NULL, readSharedValue, &readerIds[i]);
    }

    // Start writer threads
    for (i = 0; i < NUM_WRITERS; ++i) {
        writerIds[i] = i;
        pthread_create(&writerThreads[i], NULL, writeSharedValue, &writerIds[i]);
    }

    // Wait for readers to finish
    for (i = 0; i < NUM_READERS; ++i) {
        pthread_join(readerThreads[i], NULL);
        readerThreads[i] = NULL;
    }

    // Wait for writers to finish
    for (i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writerThreads[i], NULL);
        writerThreads[i] = NULL;
    }

    return 0;
}

void *readSharedValue(void *threadId)
{
    int tid = *((int *)threadId);
    int i, numReaders;

    for (i = 0; i < NUM_READ; ++i) {
        // wait for some random amount of time for reading
        sleep(1 + randombytes_uniform(NUM_READERS + NUM_WRITERS - 1));

        // Enter critical section
        pthread_mutex_lock(&gSharedValueLock);
            while (gReaderCount == -1) {
                pthread_cond_wait(&gReadPhase, &gSharedValueLock);
            }
            numReaders = ++gReaderCount;
        pthread_mutex_unlock(&gSharedValueLock);

        // Read data
        printf("[r%d,%d]: reading %2d, number of readers: %d\n", tid, i, gSharedValue, numReaders);

        // Exit critical section
        pthread_mutex_lock(&gSharedValueLock);
            --gReaderCount;
            if (gReaderCount == 0) {
                pthread_cond_signal(&gWritePhase);
            }
        pthread_mutex_unlock(&gSharedValueLock);
    }

    pthread_exit(0);
}

void *writeSharedValue(void * threadId)
{
    int tid = *((int *)threadId);
    int i, numReaders;

    for (i = 0; i < NUM_WRITE; ++i) {
        // wait for some random amount of time for writing
        sleep(1 + randombytes_uniform(NUM_READERS + NUM_WRITERS - 1));

        // Enter critical section
        pthread_mutex_lock(&gSharedValueLock);
            while (gReaderCount != 0) {
                pthread_cond_wait(&gReadPhase, &gSharedValueLock);
            }
            numReaders = --gReaderCount;
        pthread_mutex_unlock(&gSharedValueLock);

        // Read data
        printf("[w%d,%d]: writing %2d, number of readers: %d\n", tid, i, ++gSharedValue, numReaders);

        // Exit critical section
        pthread_mutex_lock(&gSharedValueLock);
            gReaderCount = 0;
            pthread_cond_broadcast(&gReadPhase);
        pthread_mutex_unlock(&gSharedValueLock);
    }

    pthread_exit(0);
}
