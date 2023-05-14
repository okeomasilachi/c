#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void processCommand(char* command) {
    // Process the command here
    printf("Command: %s\n", command);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        // Reading commands from a file
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Error opening file.\n");
            return 1;
        }

        char command[MAX_COMMAND_LENGTH];
        while (fgets(command, MAX_COMMAND_LENGTH, file) != NULL) {
            processCommand(command);
        }

        fclose(file);
    } else {
        // Interactive or non-interactive input
        char command[MAX_COMMAND_LENGTH];
        while (1) {
            if (argc == 1) {
                printf("Enter a command (or 'exit' to quit): ");
                fflush(stdout);
            }

            if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
                break;
            }

            // Remove newline character at the end
            command[strcspn(command, "\n")] = '\0';

            if (strcmp(command, "exit") == 0) {
                break;
            }

            processCommand(command);
        }
    }

    return 0;
}

