#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_BLOCKS 100

struct Block {
    int block_number;
    struct Block *next;
};

struct File {
    char name[20];
    struct Block *first_block;
    struct Block *last_block;
};

struct File files[MAX_FILES];
struct Block blocks[MAX_BLOCKS];

void initialize() {
    for (int i = 0; i < MAX_FILES; i++) {
        strcpy(files[i].name, "");
        files[i].first_block = NULL;
        files[i].last_block = NULL;
    }
    for (int i = 0; i < MAX_BLOCKS; i++) {
        blocks[i].block_number = i;
        blocks[i].next = NULL;
    }
}

void createFile(char *name) {
    int i;
    for (i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].name, "") == 0) {
            strcpy(files[i].name, name);
            printf("File '%s' created successfully.\n", name);
            break;
        }
    }
    if (i == MAX_FILES) {
        printf("Cannot create file '%s'. File system is full.\n", name);
    }
}

void allocateBlock(struct File *file, int block_number) {
    if (file->first_block == NULL) {
        file->first_block = &blocks[block_number];
        file->last_block = &blocks[block_number];
    } else {
        file->last_block->next = &blocks[block_number];
        file->last_block = &blocks[block_number];
    }
}

void addBlockToFile(char *name, int block_number) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].name, name) == 0) {
            allocateBlock(&files[i], block_number);
            printf("Block %d added to file '%s'.\n", block_number, name);
            return;
        }
    }
    printf("File '%s' not found.\n", name);
}

void displayFile(char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].name, name) == 0) {
            printf("Blocks of file '%s':\n", name);
            struct Block *current_block = files[i].first_block;
            while (current_block != NULL) {
                printf("%d -> ", current_block->block_number);
                current_block = current_block->next;
            }
            printf("NULL\n");
            return;
        }
    }
    printf("File '%s' not found.\n", name);
}

int main() {
    initialize();
    int choice, block_number;
    char name[20];

    do {
        printf("\nLinked File Allocation\n");
        printf("1. Create File\n");
        printf("2. Add Block to File\n");
        printf("3. Display File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", name);
                createFile(name);
                break;
            case 2:
                printf("Enter file name: ");
                scanf("%s", name);
                printf("Enter block number to add: ");
                scanf("%d", &block_number);
                addBlockToFile(name, block_number);
                break;
            case 3:
                printf("Enter file name to display: ");
                scanf("%s", name);
                displayFile(name);
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
