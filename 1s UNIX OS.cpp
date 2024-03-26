#include <stdio.h>
#include <stdlib.h>

int main() {
    // Execute Unix command "ls -l" to list files in the current directory
    system("ls -l");

    // Execute another Unix command "echo Hello, World!" to print a message
    system("echo Hello, World!");

    return 0;
}
