#include "list.h"

struct node* init(struct door* door) {
    struct node* root = (struct node*)malloc(sizeof(struct node));
    root->door = door;
    root->next = NULL;
    return root;
}

struct node* add_door(struct node* elem, struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->door = door;
    new_node->next = NULL;
    if (elem == NULL) {
        return new_node;
    }
    struct node* current = elem;
    while (elem->next != NULL) {
        current = current->next;
    }
    current->next = new_node;

    return elem;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current->next != NULL) {
        if (current->door->id == door_id) {
            return current;
        } else {
            current = current->next;
        }
    }
    return NULL;
}

struct node* remove_door(struct node* elem, struct node* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root == elem) {
        struct node* new_head = root->next;
        free(root);
        return new_head;
    }

    struct node* current = root;
    while (current->next != NULL && current->next != elem) {
        current = current->next;
    }

    if (current->next == elem) {
        current->next = elem->next;
        free(elem);
    }

    return root;
}

void destroy(struct node* root) {
    struct node* current = root;
    while (current != NULL) {
        struct node* next = current->next;

        // Free the door structure
        free(current->door);

        // Free the node structure
        free(current);

        // Move to the next node
        current = next;
    }
}