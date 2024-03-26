#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_PROCESS 100

int block_size[MAX_BLOCKS];
int process_size[MAX_PROCESS];
int allocation[MAX_PROCESS];

void bestFit(int m, int n) {
    // Initialize all blocks as not allocated
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    // Go through each process and find the best fit block
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (block_size[j] >= process_size[i]) {
                if (bestIdx == -1 || block_size[j] < block_size[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        // If a suitable block is found, allocate it
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            block_size[bestIdx] -= process_size[i];
        }
    }

    // Print the allocation details
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d \t\t %d \t\t", i + 1, process_size[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n; // m -> number of blocks, n -> number of processes

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &block_size[i]);
    }

    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &process_size[i]);
    }

    bestFit(m, n);

    return 0;
}
