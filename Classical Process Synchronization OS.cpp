#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define PRODUCER_THREADS 2
#define CONSUMER_THREADS 2

int buffer[BUFFER_SIZE];
int itemCount = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *param) {
    int produced_item;
    
    while (1) {
        produced_item = rand() % 100; // Generate random item
        
        pthread_mutex_lock(&mutex);
        
        while (itemCount == BUFFER_SIZE) { // Buffer is full, wait
            pthread_cond_wait(&full, &mutex);
        }
        
        buffer[in] = produced_item; // Add item to buffer
        in = (in + 1) % BUFFER_SIZE;
        itemCount++;
        
        printf("Producer %ld produced item: %d\n", pthread_self(), produced_item);
        
        pthread_cond_signal(&empty); // Signal consumer(s) that buffer is not empty
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *param) {
    int consumed_item;
    
    while (1) {
        pthread_mutex_lock(&mutex);
        
        while (itemCount == 0) { // Buffer is empty, wait
            pthread_cond_wait(&empty, &mutex);
        }
        
        consumed_item = buffer[out]; // Consume item from buffer
        out = (out + 1) % BUFFER_SIZE;
        itemCount--;
        
        printf("Consumer %ld consumed item: %d\n", pthread_self(), consumed_item);
        
        pthread_cond_signal(&full); // Signal producer(s) that buffer is not full
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t producer_threads[PRODUCER_THREADS];
    pthread_t consumer_threads[CONSUMER_THREADS];
    
    // Create producer threads
    for (int i = 0; i < PRODUCER_THREADS; i++) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }
    
    // Create consumer threads
    for (int i = 0; i < CONSUMER_THREADS; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }
    
    // Join threads (not reached in this example)
    for (int i = 0; i < PRODUCER_THREADS; i++) {
        pthread_join(producer_threads[i], NULL);
    }
    for (int i = 0; i < CONSUMER_THREADS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }
    
    return 0;
}
