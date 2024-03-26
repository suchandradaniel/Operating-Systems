#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5  

enum { THINKING, HUNGRY, EATING } state[N];
pthread_mutex_t mutex;
pthread_cond_t cond[N];

void test(int i) {
    if (state[i] == HUNGRY &&
        state[(i + 4) % N] != EATING &&
        state[(i + 1) % N] != EATING) {
        state[i] = EATING;
        printf("Philosopher %d is now EATING.\n", i + 1);
        pthread_cond_signal(&cond[i]);
    }
}

void pickup_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is now HUNGRY.\n", i + 1);
    test(i);
    while (state[i] != EATING)
        pthread_cond_wait(&cond[i], &mutex);
    pthread_mutex_unlock(&mutex);
}

void return_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    printf("Philosopher %d is now THINKING.\n", i + 1);
    test((i + 4) % N);
    test((i + 1) % N);
    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* arg) {
    int i = *(int*)arg;
    while (1) {
        printf("Philosopher %d is now THINKING.\n", i + 1);
        sleep(rand() % 3);

        pickup_forks(i);
        sleep(rand() % 3);
        return_forks(i);
    }
}

int main() {
    pthread_t tid[N];
    int i;
    int phil_id[N];

    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++)
        pthread_cond_init(&cond[i], NULL);

    for (i = 0; i < N; i++) {
        phil_id[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &phil_id[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&mutex);
    for (i = 0; i < N; i++)
        pthread_cond_destroy(&cond[i]);

    return 0;
}