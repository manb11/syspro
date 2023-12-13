#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }

    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

int pop(struct node **top) {
    if (*top == NULL) {
        printf("Stack is empty\n");
        exit(1);
    }

    struct node *temp = *top;
    int data = temp->data;
    *top = temp->next;
    free(temp);

    return data;
}

int main() {
    struct node *top = NULL;
    int input;


    while (scanf("%d", &input) == 1) {
        if (input < 0) {
            printf("Invalid input. Popping the entire stack:\n");
            break;
        }

        push(&top, input);
    }

    printf("Print queue:\n");

    while (top != NULL) {
        printf("%d\n", pop(&top));
    }

    return 0;
}
