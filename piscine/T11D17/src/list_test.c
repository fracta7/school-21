#include "list.h"

#include <stdio.h>

void test_add_door();
void test_remove_door();

int main() {
    test_add_door();
    test_remove_door();

    return 0;
}

void test_add_door() {
    // Initialize a linked list with one door
    struct door door1 = {1, 0};
    struct node* head = init(&door1);
    if (head == NULL) {
        printf("FAIL\n");
        return;
    }

    // Add a new door after the head
    struct door door2 = {2, 1};
    struct node* added_node = add_door(head, &door2);
    if (added_node == NULL) {
        printf("FAIL\n");
        destroy(head);
        return;
    }

    // Verify the added node
    if (added_node->door->id == door2.id && added_node->door->status == door2.status &&
        head->next == added_node) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    // Free the allocated memory
    destroy(head);
}

void test_remove_door() {
    // Initialize a linked list with two doors
    struct door door1 = {1, 0};
    struct door door2 = {2, 1};
    struct node* head = init(&door1);
    if (head == NULL) {
        printf("FAIL\n");
        return;
    }
    head = add_door(head, &door2);
    if (head == NULL) {
        printf("FAIL\n");
        destroy(head);
        return;
    }

    // Find and remove the second door
    struct node* node_to_remove = find_door(2, head);
    if (node_to_remove == NULL) {
        printf("FAIL: Find failed\n");
        destroy(head);
        return;
    }

    head = remove_door(node_to_remove, head);
    if (head == NULL || find_door(2, head) != NULL || head->next != NULL) {
        printf("FAIL: Removal failed\n");
        destroy(head);
        return;
    }

    // Verify the removal
    printf("SUCCESS: remove_door function\n");

    // Free the allocated memory
    destroy(head);
}