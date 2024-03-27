#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int counter = 0;

void *increment_counter(void *thread_id) {
    int tid = *((int *)thread_id);

    // Lock mutex before accessing shared variable
    pthread_mutex_lock(&mutex);
    counter++;
    printf("Thread %d incremented counter to %d\n", tid, counter);
    // Unlock mutex after accessing shared variable
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        int result = pthread_create(&threads[i], NULL, increment_counter, (void *)&thread_ids[i]);
        if (result) {
            printf("Error: Unable to create thread %d\n", i);
            exit(-1);
        }
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
