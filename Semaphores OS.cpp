#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_COUNT 10

int sharedData = 0;
sem_t semaphore;

void* thread1(void* arg) {
    int i;
    for (i = 0; i < MAX_COUNT; i++) {
        sem_wait(&semaphore); 
        sharedData++;
        printf("Thread 1: Doubled value: %d\n", sharedData * 2);
        sem_post(&semaphore); 
    }
    pthread_exit(NULL);
    return 0;
}

void* thread2(void* arg) {
    int i;
    for (i = 0; i < MAX_COUNT; i++) {
        sem_wait(&semaphore); 
        sharedData++;
        printf("Thread 2: Five times value: %d\n", sharedData * 5);
        sem_post(&semaphore);  
    }
    pthread_exit(NULL);
    return 0;
}

int main() {
    pthread_t tid1, tid2;

    sem_init(&semaphore, 0, 1);

    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&semaphore);

    return 0;
}
