#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*tail == NULL) {
        // If the queue is empty, set both head and tail to the new node
        *head = *tail = newNode;
    } else {
        // Otherwise, add the new node to the end of the queue and update the tail
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        printf("Queue is empty\n");
        exit(1);
    }

    struct node *temp = *head;
    int data = temp->data;

    *head = temp->next;
    free(temp);

    // If the queue becomes empty after deletion, update the tail to NULL
    if (*head == NULL) {
        *tail = NULL;
    }

    return data;
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int input;


    while (scanf("%d", &input) == 1) {
        if (input < 0) {
            printf("Invalid input. Dequeuing the entire queue:\n");
            break;
        }

        addq(&head, &tail, input);
    }

    printf("Print queue:\n");

    while (head != NULL) {
        printf("%d\n", delete(&head, &tail));
    }

    return 0;
}
