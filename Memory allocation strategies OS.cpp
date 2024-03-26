#include <stdio.h>

int main() {
    int partitions[] = { 300, 600, 350, 200, 750, 125 };
    int num_partitions = 6;
    int processes[] = { 115, 500, 358, 200, 375 };
    int num_processes = 5;
    int allocation[num_processes];
    int i, j;
 

    for (i = 0; i < num_processes; i++)
        allocation[i] = -1;
 
    
    for (i = 0; i < num_processes; i++) {
        int best_index = -1;
        for (j = 0; j < num_partitions; j++) {
            if (partitions[j] >= processes[i]) {
                if (best_index == -1 || partitions[j] < partitions[best_index])
                    best_index = j;
            }
        }
   
        if (best_index != -1) {
            allocation[i] = best_index;
            partitions[best_index] -= processes[i];
        }
    }
 
   
    printf("Process No.\tProcess Size\tPartition No.\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t\t%d\t\t", i+1, processes[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }
 
    return 0;
}