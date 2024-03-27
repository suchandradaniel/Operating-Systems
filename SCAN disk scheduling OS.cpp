#include <stdio.h>
#include <stdlib.h>

#define MAX_TRACKS 100

// Function to sort an array in ascending order
void sortArray(int arr[], int size) {
    int i, j, temp;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to simulate the SCAN disk scheduling algorithm and calculate average head movement
void simulateSCAN(int tracks[], int numTracks, int currentPosition) {
    int i;
    int headMovement = 0;
    int closestTrack = -1;

    sortArray(tracks, numTracks);

    // Find the index of the closest track to the current position
    for (i = 0; i < numTracks; i++) {
        if (tracks[i] >= currentPosition) {
            closestTrack = i;
            break;
        }
    }
    if (closestTrack == -1) {
        closestTrack = numTracks - 1;
    }

    // Move towards higher tracks
    for (i = closestTrack; i < numTracks; i++) {
        headMovement += abs(tracks[i] - currentPosition);
        currentPosition = tracks[i];
    }

    // Move towards lower tracks
    headMovement += abs(tracks[numTracks - 1] - tracks[0]);

    currentPosition = tracks[0];
    headMovement += abs(tracks[0] - tracks[closestTrack]);

    // Move towards higher tracks (second pass)
    for (i = closestTrack + 1; i < numTracks; i++) {
        headMovement += abs(tracks[i] - currentPosition);
        currentPosition = tracks[i];
    }

    float averageHeadMovement = (float) headMovement / numTracks;
    printf("Average head movement: %.2f\n", averageHeadMovement);
}

int main() {
    int tracks[MAX_TRACKS];
    int numTracks;
    int currentPosition;

    printf("Enter the number of tracks: ");
    scanf("%d", &numTracks);

    printf("Enter the track positions: ");
    for (int i = 0; i < numTracks; i++) {
        scanf("%d", &tracks[i]);
    }

    printf("Enter the current position of the head: ");
    scanf("%d", &currentPosition);

    simulateSCAN(tracks, numTracks, currentPosition);

    return 0;
}