#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_JOBS 10

void bestFit(int blockSize[], int m, int jobSize[], int n) {
    int allocation[n];
  
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= jobSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }
  
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= jobSize[i];
        } else {
            allocation[i] = -1;
        }
    }
  
    printf("\nJob No.\tJob Size\tBlock no.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i+1, jobSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
  
int main() {
    int blockSize[MAX_BLOCKS], jobSize[MAX_JOBS];
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }
  
    printf("Enter number of jobs: ");
    scanf("%d", &n);
    printf("Enter the size of each job:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &jobSize[i]);
    }

    bestFit(blockSize, m, jobSize, n);
  
    return 0;
}
