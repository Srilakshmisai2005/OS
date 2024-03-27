#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIR_NAME_LEN 100
#define MAX_FILE_NAME_LEN 100
#define MAX_FILES_PER_DIR 100

typedef struct {
    char name[MAX_FILE_NAME_LEN];
    // Add other attributes of the file as needed
} File;

typedef struct {
    char name[MAX_DIR_NAME_LEN];
    File files[MAX_FILES_PER_DIR];
    int file_count;
} Directory;

Directory directories[MAX_FILES_PER_DIR];
int dir_count = 0;

// Function to create a new directory
void create_directory(const char *name) {
    if (dir_count < MAX_FILES_PER_DIR) {
        strcpy(directories[dir_count].name, name);
        directories[dir_count].file_count = 0;
        dir_count++;
        printf("Directory '%s' created successfully.\n", name);
    } else {
        printf("Cannot create directory '%s'. Maximum directory limit reached.\n", name);
    }
}

// Function to create a new file in a directory
void create_file(const char *dir_name, const char *file_name) {
    int i;
    for (i = 0; i < dir_count; i++) {
        if (strcmp(directories[i].name, dir_name) == 0) {
            if (directories[i].file_count < MAX_FILES_PER_DIR) {
                strcpy(directories[i].files[directories[i].file_count].name, file_name);
                directories[i].file_count++;
                printf("File '%s' created successfully in directory '%s'.\n", file_name, dir_name);
                return;
            } else {
                printf("Cannot create file '%s'. Maximum file limit reached in directory '%s'.\n", file_name, dir_name);
                return;
            }
        }
    }
    printf("Directory '%s' not found.\n", dir_name);
}

// Function to list all files in a directory
void list_files(const char *dir_name) {
    int i;
    for (i = 0; i < dir_count; i++) {
        if (strcmp(directories[i].name, dir_name) == 0) {
            printf("Files in directory '%s':\n", dir_name);
            if (directories[i].file_count == 0) {
                printf("No files found.\n");
            } else {
                int j;
                for (j = 0; j < directories[i].file_count; j++) {
                    printf("%s\n", directories[i].files[j].name);
                }
            }
            return;
        }
    }
    printf("Directory '%s' not found.\n", dir_name);
}

int main() {
    // Example usage
    create_directory("Folder1");
    create_directory("Folder2");

    create_file("Folder1", "file1.txt");
    create_file("Folder1", "file2.txt");
    create_file("Folder2", "file3.txt");

    list_files("Folder1");
    list_files("Folder2");

    return 0;
}