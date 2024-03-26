#include <stdio.h>
#include <pthread.h>
void *printNumbers(void *arg) {
    for (int i = 1; i <= 5; ++i) {
        printf("Thread 1: %d\n", i);
        fflush(stdout); 
        usleep(100000); 
    }
    return NULL;
}

void *printLetters(void *arg) {
    for (char ch = 'A'; ch <= 'E'; ++ch) {
        printf("Thread 2: %c\n", ch);
        fflush(stdout);
        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, printNumbers, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    if (pthread_create(&thread2, NULL, printLetters, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}