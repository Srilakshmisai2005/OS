#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes, num_resources;

int request_resources(int pid, int request[]) {
    // Check if request can be granted
    for (int i = 0; i < num_resources; i++) {
        if (request[i] > need[pid][i] || request[i] > available[i])
            return -1; // Request cannot be granted
    }

    // Simulate granting request
    for (int i = 0; i < num_resources; i++) {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    return 0; // Request granted successfully
}

void release_resources(int pid, int release[]) {
    // Release resources back to the system
    for (int i = 0; i < num_resources; i++) {
        available[i] += release[i];
        allocation[pid][i] -= release[i];
        need[pid][i] += release[i];
    }
}

int safety_algorithm() {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safe_sequence[MAX_PROCESSES];
    int count = 0;

    // Initialize work and finish
    for (int i = 0; i < num_resources; i++)
        work[i] = available[i];

    // Find a safe sequence
    while (count < num_processes) {
        int found = 0;
        for (int i = 0; i < num_processes; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == num_resources) {
                    // Process can finish
                    for (int k = 0; k < num_resources; k++)
                        work[k] += allocation[i][k];
                    safe_sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            return -1; // No safe sequence exists
    }

    // Print safe sequence
    printf("Safe sequence: ");
    for (int i = 0; i < num_processes; i++)
        printf("%d ", safe_sequence[i]);
    printf("\n");

    return 0; // Safe sequence found
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    // Input available resources
    printf("Enter available resources:\n");
    for (int i = 0; i < num_resources; i++)
        scanf("%d", &available[i]);

    // Input maximum resources
    printf("Enter maximum resources for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < num_resources; j++)
            scanf("%d", &maximum[i][j]);
    }

    // Input allocation for each process
    printf("Enter allocation for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // Run safety algorithm
    if (safety_algorithm() == -1)
        printf("Unsafe state detected\n");
    else
        printf("System is in safe state\n");

    return 0;
}
