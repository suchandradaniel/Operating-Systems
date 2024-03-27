#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define DISK_SIZE 100

struct File {
    char name[20];
    int start_block;
    int length;
};

struct File files[MAX_FILES];
int disk[DISK_SIZE];

void initialize() {
    memset(disk, -1, sizeof(disk)); // Initialize disk blocks to -1 (unallocated)
}

void allocate(char *name, int length) {
    int start = -1;
    for (int i = 0; i < DISK_SIZE; i++) {
        int j;
        for (j = 0; j < length; j++) {
            if (disk[i + j] != -1) {
                break; // Not enough contiguous space, move to the next block
            }
        }
        if (j == length) {
            start = i;
            break; // Found enough contiguous space
        }
    }

    if (start != -1) {
        strcpy(files[MAX_FILES - length].name, name);
        files[MAX_FILES - length].start_block = start;
        files[MAX_FILES - length].length = length;
        for (int i = start; i < start + length; i++) {
            disk[i] = MAX_FILES - length; // Mark disk blocks as allocated
        }
        printf("File '%s' allocated starting from block %d\n", name, start);
    } else {
        printf("Not enough contiguous space available for file '%s'\n", name);
    }
}

void deallocate(char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].name, name) == 0) {
            int start = files[i].start_block;
            int length = files[i].length;
            for (int j = start; j < start + length; j++) {
                disk[j] = -1; // Mark disk blocks as unallocated
            }
            printf("File '%s' deallocated\n", name);
            files[i].start_block = -1;
            files[i].length = 0;
            strcpy(files[i].name, "");
            return;
        }
    }
    printf("File '%s' not found\n", name);
}

void display() {
    printf("\nDisk Status:\n");
    for (int i = 0; i < DISK_SIZE; i++) {
        if (i % 10 == 0) printf("\n");
        printf("%2d ", disk[i]);
    }
    printf("\n\nFiles Allocated:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].start_block != -1) {
            printf("Name: %-10s Start Block: %-3d Length: %-3d\n", files[i].name, files[i].start_block, files[i].length);
        }
    }
}

int main() {
    initialize();
    int choice, length;
    char name[20];

    do {
        printf("\nFile Allocation Strategies\n");
        printf("1. Allocate File\n");
        printf("2. Deallocate File\n");
        printf("3. Display Disk Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", name);
                printf("Enter file length: ");
                scanf("%d", &length);
                allocate(name, length);
                break;
            case 2:
                printf("Enter file name to deallocate: ");
                scanf("%s", name);
                deallocate(name);
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}
