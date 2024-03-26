#include <stdio.h>

int main()
{
    int i, j, k;
    int n = 3; 
    int available[3] = {1, 2, 0}; 
    int max[3][3] = {{3, 6, 8}, {4, 3, 3}, {3, 4, 4}}; 
    int allocation[3][3] = {{3, 3, 3}, {2, 0, 3}, {1, 2, 4}}; 
    int need[3][3]; 
    int finish[3] = {0};
    int safe = 0; 

    
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

 
    while(safe == 0) {
        safe = 1; 

        
        for(i=0; i<n; i++) {
            if(finish[i] == 0) {
                int flag = 0;
                for(j=0; j<n; j++) {
                    if(need[i][j] > available[j]) {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0) {
                    for(k=0; k<n; k++) {
                        available[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    safe = 0;
                }
            }
        }
    }


    int deadlock = 1;
    for(i=0; i<n; i++) {
        if(finish[i] == 0) {
            deadlock = 0;
            printf("Process %d is deadlocked.\n", i);
        }
    }
    if(deadlock) {
        printf("System is in a deadlock state.\n");
    } else {
        printf("System is not in a deadlock state.\n");
    }

    return 0;
}