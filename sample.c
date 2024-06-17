#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // For access() function
#include <sys/stat.h> // For stat() function

#define BUFSIZE 256

// Function to encode a shell command argument
void encode_shell_string(const char *input, char *output, size_t out_size) {
    size_t len = strlen(input);
    size_t pos = 0;

    for (size_t i = 0; i < len && pos < out_size - 1; ++i) {
        if (input[i] == '"' || input[i] == '\\' || input[i] == '$') {
            output[pos++] = '\\'; // Escape special characters
        }
        output[pos++] = input[i];
    }

    output[pos] = '\0'; // Null-terminate the output string
}

// Function to check if a file exists
int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

// Function to print file size in bytes
void print_file_size(const char *filename) {
    char cmd[BUFSIZE];
    char encoded_filename[BUFSIZE];

    encode_shell_string(filename, encoded_filename, sizeof(encoded_filename));

    snprintf(cmd, sizeof(cmd), "wc -c < \"%s\"", encoded_filename);
    
    system(cmd); // Execute the command
}

int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) { 
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }
	
	// Check if the file exists and is accessible
    if (!file_exists(argv[1])) {
        fprintf(stderr, "File %s does not exist or cannot be accessed.\n", argv[1]);
        return -1;
    }

    // Print the size of the specified file
    print_file_size(argv[1]);

    return 0;
}
