#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n, head, i, total = 0;
    float avg;

    printf("Enter the number of tracks: ");
    scanf("%d", &n);

    int tracks[n];

    printf("Enter the track positions: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &tracks[i]);
    }

    printf("Enter the head position: ");
    scanf("%d", &head);

    total += abs(tracks[0] - head);
    for(i = 1; i < n; i++)
    {
        total += abs(tracks[i] - tracks[i-1]);
    }

    avg = (float)total/n;

    printf("Average head movement = %.2f\n", avg);

    return 0;
}