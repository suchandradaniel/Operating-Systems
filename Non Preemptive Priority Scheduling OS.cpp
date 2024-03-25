#include <stdio.h>

// Process structure
struct Process {
    int id;             // Process ID
    int arrival_time;   // Arrival Time
    int burst_time;     // Burst Time
    int priority;       // Priority
    int completion_time;    // Completion Time
    int turnaround_time;    // Turnaround Time
    int waiting_time;       // Waiting Time
};

// Function to perform Non-Preemptive Priority Scheduling
void non_preemptive_priority_scheduling(struct Process processes[], int n) {
    int current_time = 0;   // Current time initialized to 0
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Find completion time for each process
    for (int i = 0; i < n; i++) {
        current_time += processes[i].burst_time;
        processes[i].completion_time = current_time;
        total_turnaround_time += processes[i].completion_time - processes[i].arrival_time;
        total_waiting_time += processes[i].completion_time - processes[i].arrival_time - processes[i].burst_time;
    }

    // Calculate turnaround time and waiting time
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }

    // Print result
    printf("Process\t Arrival Time\t Burst Time\t Priority\t Completion Time\t Turnaround Time\t Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t\t %d\n", processes[i].id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Print average turnaround time and waiting time
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time = %.2f\n", (float)total_waiting_time / n);
}

int main() {
    // Number of processes
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input processes
    struct Process processes[n];
    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        processes[i].id = i + 1;
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }

    // Perform Non-Preemptive Priority Scheduling
    non_preemptive_priority_scheduling(processes, n);

    return 0;
}
