#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // For access() function
#include <sys/stat.h> // For stat() function

#define BUFSIZE 256

// Function to check if a file exists
int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// Function to print file size in bytes
void print_file_size(const char *filename) {
    char cmd[BUFSIZE];
    snprintf(cmd, sizeof(cmd), "wc -c < \"%s\"", filename); // Safely construct the command
    system(cmd); // Execute the command
}

int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) { 
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }

    // Print the size of the specified file
    print_file_size(argv[1]);

    return 0;
}
