#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked list node structure
struct Node {
    char* directory;
    struct Node* next;
};

// Function to build the linked list of PATH directories
struct Node* build_path_list() {
    struct Node* head = NULL;
    struct Node* tail = NULL;

    // Get the PATH environment variable
    char* path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "Unable to retrieve PATH environment variable\n");
        return NULL;
    }

    // Tokenize the path using ':' delimiter
    char* token = strtok(path, ":");
    while (token != NULL) {
        // Create a new node
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }

        // Copy the directory into the node
        newNode->directory = strdup(token);
        if (newNode->directory == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free(newNode);
            return NULL;
        }

        newNode->next = NULL;

        // Add the node to the linked list
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        // Get the next token
        token = strtok(NULL, ":");
    }

    return head;
}

// Function to print the path list
void print_path_list(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%s\n", current->directory);
        current = current->next;
    }
}

// Function to free the memory of the path list
void free_path_list(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp->directory);
        free(temp);
    }
}

int main() {
    struct Node* pathList = build_path_list();

    if (pathList != NULL) {
        printf("Path List:\n");
        print_path_list(pathList);

        // Clean up memory
        free_path_list(pathList);
    }

    return 0;
}

