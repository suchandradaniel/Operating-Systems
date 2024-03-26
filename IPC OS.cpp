#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    int shmid, pid;
    key_t key;
    char *shm_ptr, *data;
    
    // Generate a unique key for the shared memory segment
    key = ftok(".", 's');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    
    // Create the shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    // Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    
    if (pid == 0) { // Child process
        // Attach the shared memory segment to the child process's address space
        shm_ptr = shmat(shmid, NULL, 0);
        if (shm_ptr == (char *) -1) {
            perror("shmat");
            exit(1);
        }
        
        // Write to the shared memory
        data = "Hello from Process 2";
        strncpy(shm_ptr, data, SHM_SIZE);
        printf("Data written to shared memory by Child: %s\n", data);
        
        // Detach the shared memory segment from the child process's address space
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(1);
        }
    } else { // Parent process
        // Wait for the child process to finish writing
        wait(NULL);
        
        // Attach the shared memory segment to the parent process's address space
        shm_ptr = shmat(shmid, NULL, 0);
        if (shm_ptr == (char *) -1) {
            perror("shmat");
            exit(1);
        }
        
        // Read from the shared memory
        printf("Data read from shared memory by Parent: %s\n", shm_ptr);
        
        // Detach the shared memory segment from the parent process's address space
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(1);
        }
        
        // Mark the shared memory segment for removal
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    }
    
    return 0;
}
