#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int findOptimalPage(int pages[], int numPages, int frames[], int numFrames, int currentPosition) {
    int farthestIndex = -1;
    int farthestDistance = INT_MIN;

    for (int i = 0; i < numFrames; i++) {
        int j;
        bool found = false;
        for (j = currentPosition; j < numPages; j++) {
            if (frames[i] == pages[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            return i;
        }

        if (j > farthestDistance) {
            farthestDistance = j;
            farthestIndex = i;
        }
    }

    return farthestIndex;
}

int getPageFaults(int pages[], int numPages, int numFrames) {
    int frames[numFrames];
    int numFaults = 0;

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < numPages; i++) {
        bool found = false;

        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            int position = findOptimalPage(pages, numPages, frames, numFrames, i + 1);
            frames[position] = pages[i];
            numFaults++;
        }
    }

    return numFaults;
}

int main() {
    int numFrames = 3;
    int pages[] = {4, 1, 2, 4, 3, 2, 1, 5};
    int numPages = sizeof(pages) / sizeof(pages[0]);

    int numFaults = getPageFaults(pages, numPages, numFrames);

    printf("Page Reference Sequence:\n");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", pages[i]);
    }

    printf("\n\nNumber of Page Faults: %d\n", numFaults);

    return 0;
}