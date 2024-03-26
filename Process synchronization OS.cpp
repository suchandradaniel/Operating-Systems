#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid[4]; 
    int i, j;

    for (i = 0; i < 4; i++) {
        pid[i] = fork(); 
        if (pid[i] < 0) {
            printf("Error: Failed to create child process\n");
            exit(1);
        }
        else if (pid[i] == 0) { 
            switch (i) {
                case 0: 
                    printf("Child Process %d (Odd numbers): ", getpid());
                    for (j = 1; j <= 10; j++) {
                        if (j % 2 != 0)
                            printf("%d ", j);
                    }
                    printf("\n");
                    break;
                case 1: 
                    printf("Child Process %d (Even numbers): ", getpid());
                    for (j = 1; j <= 10; j++) {
                        if (j % 2 == 0)
                            printf("%d ", j);
                    }
                    printf("\n");
                    break;
                case 2: 
                    printf("Child Process %d (Multiples of 3): ", getpid());
                    for (j = 1; j <= 10; j++) {
                        if (j % 3 == 0)
                            printf("%d ", j);
                    }
                    printf("\n");
                    break;
                case 3: 
                    printf("Child Process %d (Multiples of 5): ", getpid());
                    for (j = 1; j <= 10; j++) {
                        if (j % 5 == 0)
                            printf("%d ", j);
                    }
                    printf("\n");
                    break;
            }
            exit(0); 
        }
    }

    
    for (i = 0; i < 4; i++) {
        waitpid(pid[i], NULL, 0);
    }

    return 0;
}