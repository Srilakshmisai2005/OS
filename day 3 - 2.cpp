#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

void *producer(void *arg) {
    int item = 1;
    while (1) {
        sem_wait(&empty); // Decrement empty count
        sem_wait(&mutex); // Lock buffer
        buffer[in] = item;
        printf("Produced item %d\n", item++);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex); // Unlock buffer
        sem_post(&full);  // Increment full count

        sleep(1); // Sleep for some time
    }
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);  // Decrement full count
        sem_wait(&mutex); // Lock buffer
        int item = buffer[out];
        printf("Consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex); // Unlock buffer
        sem_post(&empty); // Increment empty count

        sleep(2); // Sleep for some time
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Join threads
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
