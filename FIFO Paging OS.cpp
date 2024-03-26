#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 3
#define NUM_PAGES 10

// Function to find if a page is present in memory
int findPage(int page, int *frames, int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            return 1; // Page found
        }
    }
    return 0; // Page not found
}

// Function to print the content of frames
void printFrames(int *frames, int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

int main() {
    int frames[NUM_FRAMES] = {-1}; // Initialize frames with -1 to indicate empty
    int page_reference[] = {0, 1, 2, 3, 0, 4, 5, 1, 6, 7}; // Reference string
    int page_faults = 0;

    for (int i = 0; i < NUM_PAGES; i++) {
        printf("Reference: %d\n", page_reference[i]);
        if (!findPage(page_reference[i], frames, NUM_FRAMES)) {
            // Page fault, replace the oldest page in memory (FIFO)
            frames[page_faults % NUM_FRAMES] = page_reference[i];
            page_faults++;
        }
        printFrames(frames, NUM_FRAMES);
    }

    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}
