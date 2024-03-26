#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_FILES 3

typedef struct {
    char name[20];
    char files[MAX_FILES][20];
    int fileCount;
} UserDirectory;

typedef struct {
    UserDirectory directories[MAX_USERS];
    int userCount;
} DirectorySystem;

void createUserDirectory(DirectorySystem* system, const char* name) {
    if (system->userCount >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    UserDirectory* user = &(system->directories[system->userCount]);
    strcpy(user->name, name);
    user->fileCount = 0;

    system->userCount++;
    printf("User directory '%s' created successfully.\n", name);
}

void createFile(UserDirectory* user, const char* fileName) {
    if (user->fileCount >= MAX_FILES) {
        printf("Maximum number of files reached for user '%s'.\n", user->name);
        return;
    }

    strcpy(user->files[user->fileCount], fileName);
    user->fileCount++;
    printf("File '%s' created successfully in user directory '%s'.\n", fileName, user->name);
}

int main() {
    DirectorySystem system;
    system.userCount = 0;

    createUserDirectory(&system, "user1");
    createUserDirectory(&system, "user2");
    createUserDirectory(&system, "user3");

    createFile(&(system.directories[0]), "file1.txt");
    createFile(&(system.directories[0]), "file2.txt");
    createFile(&(system.directories[0]), "file3.txt");

    createFile(&(system.directories[1]), "file4.txt");
    createFile(&(system.directories[1]), "file5.txt");

    createFile(&(system.directories[2]), "file6.txt");

    return 0;
}