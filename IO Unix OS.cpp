#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int fd, n;
    char buffer[100];
    struct stat fileStat;
    DIR *dir;
    struct dirent *entry;

    // Open a file using open system call
    fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read data from the file using read system call
    n = read(fd, buffer, sizeof(buffer));
    if (n == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0'; // Null terminate the buffer
    printf("Read from file: %s\n", buffer);

    // Close the file using close system call
    close(fd);

    // Use stat system call to get information about a file
    if (stat("test.txt", &fileStat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    printf("File size: %lld bytes\n", (long long)fileStat.st_size);

    // Open a directory using opendir system call
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Read directory entries using readdir system call
    printf("Directory contents:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}
