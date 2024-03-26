#include <stdio.h>
#include <stdbool.h>

#define TOTAL_BLOCKS 16
#define INODE_BLOCKS 8
#define AVAILABLE_BLOCKS (TOTAL_BLOCKS - INODE_BLOCKS)

bool isContiguousFree(int allocation[], int startBlock, int numBlocks) {
    for (int i = startBlock; i < startBlock + numBlocks; i++) {
        if (allocation[i] != -1) {
            return false;
        }
    }
    return true;
}

void allocateBlocks(int allocation[], int startBlock, int numBlocks, int fileIndex) {
    for (int i = startBlock; i < startBlock + numBlocks; i++) {
        allocation[i] = fileIndex;
    }
}

int main() {
    int allocation[TOTAL_BLOCKS] = {-1};  // -1 indicates free block
    int numFiles;
    int fileSize;

    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    for (int i = 0; i < numFiles; i++) {
        printf("\nFile %d\n", i + 1);

        printf("Enter the file size (in KB): ");
        scanf("%d", &fileSize);

        if (fileSize < 1) {
            printf("File size must be at least 1 KB.\n");
            return 1;
        }

        if (fileSize > AVAILABLE_BLOCKS) {
            printf("Not enough contiguous blocks available for the file.\n");
            return 1;
        }

        int startBlock = -1;
        int numBlocks = -1;

        for (int j = INODE_BLOCKS; j < TOTAL_BLOCKS; j++) {
            if (isContiguousFree(allocation, j, fileSize)) {
                startBlock = j;
                numBlocks = fileSize;
                break;
            }
        }

        if (startBlock == -1 || numBlocks == -1) {
            printf("Not enough contiguous blocks available for the file.\n");
            return 1;
        }

        allocateBlocks(allocation, startBlock, numBlocks, i);
        printf("Allocated %d blocks starting from block %d to the file.\n", numBlocks, startBlock);
    }

    printf("\nBlock Allocation Table:\n");
    printf("Block No.\tFile No.\n");
    for (int i = 0; i < TOTAL_BLOCKS; i++) {
        printf("%d\t\t", i);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Free\n");
        }
    }

    return 0;
}