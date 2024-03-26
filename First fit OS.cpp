#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1000 // Size of the memory block
#define PROCESS_COUNT 5  // Number of processes

int memory[MEMORY_SIZE]; // Memory block represented as an array
int processes[PROCESS_COUNT]; // Array to hold process sizes

// Function to initialize memory
void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i] = 0; // Initialize all memory locations to 0 (indicating free)
    }
}

// Function to allocate memory using First Fit algorithm
void firstFit(int processSize) {
    int i;
    for (i = 0; i < MEMORY_SIZE; i++) {
        int blockSize = 0;
        // Find the first block of free memory that is large enough to hold the process
        while (memory[i] == 0 && i < MEMORY_SIZE && blockSize < processSize) {
            blockSize++;
            i++;
        }
        if (blockSize >= processSize) {
            // Allocate memory for the process
            for (int j = i - blockSize; j < i; j++) {
                memory[j] = processSize;
            }
            printf("Process of size %d allocated from %d to %d\n", processSize, i - blockSize, i - 1);
            return;
        }
    }
    printf("Unable to allocate memory for process of size %d\n", processSize);
}

int main() {
    initializeMemory(); // Initialize memory

    // Example process sizes
    processes[0] = 100;
    processes[1] = 200;
    processes[2] = 50;
    processes[3] = 300;
    processes[4] = 150;

    // Allocate memory for each process
    for (int i = 0; i < PROCESS_COUNT; i++) {
        firstFit(processes[i]);
    }

    return 0;
}
