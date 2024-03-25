#include <stdio.h>

struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time of the process
    int burst_time; // Burst time of the process
    int remaining_time; // Remaining burst time of the process
};

// Function to perform SJF scheduling
void sjf(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int shortest = -1;
    int shortest_time = -1;
    
    while (completed < n) {
        shortest = -1;
        shortest_time = -1;
        
        // Find the shortest job available at current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (shortest == -1 || processes[i].remaining_time < shortest_time) {
                    shortest = i;
                    shortest_time = processes[i].remaining_time;
                }
            }
        }
        
        // If no process is found, move time to next process arrival
        if (shortest == -1) {
            current_time++;
            continue;
        }
        
        // Execute the shortest job for 1 time unit
        processes[shortest].remaining_time--;
        current_time++;
        
        // If the job is completed
        if (processes[shortest].remaining_time == 0) {
            completed++;
            printf("Process %d completed at time %d\n", processes[shortest].pid, current_time);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    // Input process details
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        processes[i].pid = i + 1;
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    // Perform SJF scheduling
    sjf(processes, n);
    
    return 0;
}
