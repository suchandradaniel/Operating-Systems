#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 10
#define MAX_RECORDS_PER_FILE 100

struct File {
    char name[20];
    char records[MAX_RECORDS_PER_FILE][256]; // Assuming each record can hold up to 255 characters
    int num_records;
};

struct File files[MAX_FILES];

void initialize() {
    for (int i = 0; i < MAX_FILES; i++) {
        strcpy(files[i].name, "");
        files[i].num_records = 0;
    }
}

void createFile(char *name) {
    int i;
    for (i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].name, "") == 0) {
            strcpy(files[i].name, name);
            files[i].num_records = 0;
            printf("File '%s' created successfully.\n", name);
            break;
        }
    }
    if (i == MAX_FILES) {
        printf("Cannot create file '%s'. File system is full.\n", name);
    }
}

void addRecord(char *name, char *record) {
    int i;
    for (i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].name, name) == 0) {
            if (files[i].num_records < MAX_RECORDS_PER_FILE) {
                strcpy(files[i].records[files[i].num_records], record);
                files[i].num_records++;
                printf("Record added to file '%s' successfully.\n", name);
            } else {
                printf("Cannot add record to file '%s'. Maximum records reached.\n", name);
            }
            break;
        }
    }
    if (i == MAX_FILES) {
        printf("File '%s' not found.\n", name);
    }
}

void displayFile(char *name) {
    int i;
    for (i = 0; i < MAX_FILES; i++) {
        if (strcmp(files[i].name, name) == 0) {
            printf("Records of file '%s':\n", name);
            for (int j = 0; j < files[i].num_records; j++) {
                printf("%s\n", files[i].records[j]);
            }
            break;
        }
    }
    if (i == MAX_FILES) {
        printf("File '%s' not found.\n", name);
    }
}

int main() {
    initialize();
    int choice;
    char name[20];
    char record[256];

    do {
        printf("\nSequential File Allocation\n");
        printf("1. Create File\n");
        printf("2. Add Record\n");
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
                printf("Enter record to add: ");
                getchar(); // Clear input buffer
                fgets(record, sizeof(record), stdin);
                record[strcspn(record, "\n")] = '\0'; // Remove newline character
                addRecord(name, record);
                break;
            case 3:
                printf("Enter file name: ");
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
