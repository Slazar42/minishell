#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void removeNode(struct Node* head, int key) {
    struct Node* current = head;
    struct Node* prev = NULL;

    // Find the node to be removed
    while (current != NULL && current->data != key) {
        prev = current;
        current = current->next;
    }

    // If node not found
    if (current == NULL) {
        printf("Node with key %d not found.\n", key);
        return;
    }

    // Update pointers to remove the node
    if (prev != NULL) {
        prev->next = current->next;
    } else {
        // If the node to be removed is the head
        head = current->next;
    }

    free(current);
}

int main() {
    struct Node* head = NULL; // Initialize an empty linked list

    // Add nodes to the linked list

    // Call the removeNode function to remove a node

    return 0;
}
