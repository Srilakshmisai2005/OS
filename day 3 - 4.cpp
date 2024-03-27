#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

pthread_mutex_t mutex;
sem_t rw_mutex;
int readers_count = 0;
int shared_data = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    while (1) {
        pthread_mutex_lock(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex);
        }
        pthread_mutex_unlock(&mutex);

        printf("Reader %d is reading shared data: %d\n", reader_id, shared_data);

        pthread_mutex_lock(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex);
        }
        pthread_mutex_unlock(&mutex);

        sleep(1); // Sleep for some time
    }
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    while (1) {
        sem_wait(&rw_mutex);

        printf("Writer %d is writing to shared data\n", writer_id);
        shared_data++; // Modify shared data

        sem_post(&rw_mutex);

        sleep(2); // Sleep for some time
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize mutex and semaphore
    pthread_mutex_init(&mutex, NULL);
    sem_init(&rw_mutex, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, (void *)&writer_ids[i]);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutex and semaphore
    pthread_mutex_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
