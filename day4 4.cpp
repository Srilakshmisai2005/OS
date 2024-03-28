#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    char pattern[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];

    // Check if pattern is provided as command-line argument
    if (argc != 2) {
        printf("Usage: %s <pattern>\n", argv[0]);
        return 1;
    }

    // Copy the pattern from command-line argument
    strcpy(pattern, argv[1]);

    // Read lines from standard input
    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        // Check if pattern is found in the line
        if (strstr(line, pattern) != NULL) {
            // If pattern is found, print the line
            printf("%s", line);
        }
    }

    return 0;
}
