#include <stdio.h>

#define MAX_PARTITIONS 10

void worstFit(int partitions[], int numPartitions, int processes[], int numProcesses) {
    int allocation[MAX_PARTITIONS] = {-1};  // -1 indicates unallocated memory
    int i, j;

    for (i = 0; i < numProcesses; i++) {
        int worstIndex = -1;
        for (j = 0; j < numPartitions; j++) {
            if (partitions[j] >= processes[i]) {
                if (worstIndex == -1 || partitions[j] > partitions[worstIndex]) {
                    worstIndex = j;
                }
            }
        }

        if (worstIndex != -1) {
            allocation[worstIndex] = i;
            partitions[worstIndex] -= processes[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tPartition No.\n");
    for (i = 0; i < numProcesses; i++) {
        printf("%d\t\t%d\t\t", i+1, processes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int partitions[MAX_PARTITIONS] = {40, 10, 30, 60};  // Memory partitions (in KB)
    int numPartitions = 4;
    int processes[] = {100, 50, 30, 120, 35};  // Process sizes (in KB)
    int numProcesses = 5;

    printf("Memory Partitions:\n");
    for (int i = 0; i < numPartitions; i++) {
        printf("Partition %d: %d KB\n", i+1, partitions[i]);
    }

    printf("\nProcesses:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: %d KB\n", i+1, processes[i]);
    }

    worstFit(partitions, numPartitions, processes, numProcesses);

    return 0;
}