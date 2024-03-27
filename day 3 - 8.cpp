#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
    int input_fd, output_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open input file
    input_fd = open("input.txt", O_RDONLY);
    if (input_fd == -1) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    // Open or create output file
    output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (output_fd == -1) {
        perror("Failed to open or create output file");
        exit(EXIT_FAILURE);
    }

    // Read from input file and write to output file
    while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(output_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
    }

    // Close files
    if (close(input_fd) == -1) {
        perror("Error closing input file");
        exit(EXIT_FAILURE);
    }
    if (close(output_fd) == -1) {
        perror("Error closing output file");
        exit(EXIT_FAILURE);
    }

    printf("File copied successfully!\n");

    return 0;
}
