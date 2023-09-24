#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the stack node
struct StackNode {
    char data;
    struct StackNode* next;
};

// Function to create a new stack node
struct StackNode* createNode(char data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Define a structure for the stack
struct Stack {
    struct StackNode* top;
};

// Function to initialize an empty stack
void initialize(struct Stack* stack) {
    stack->top = NULL;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(struct Stack* stack, char data) {
    struct StackNode* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop an element from the stack
char pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    char data = stack->top->data;
    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

// Function to convert a postfix expression to infix expression
void postfixToInfix(char postfix[]) {
    struct Stack stack;
    initialize(&stack);

    int len = strlen(postfix);
    char infix[len * 2]; // Infix expression can be at most twice the length of postfix

    for (int i = 0, j = 0; i < len; i++) {
        char ch = postfix[i];

        if (ch >= '0' && ch <= '9') {
            // Operand, push onto the stack
            push(&stack, ch);
        } else {
            // Operator, pop two operands and create an infix expression
            char operand2 = pop(&stack);
            char operand1 = pop(&stack);

            // Construct the infix expression
            infix[j++] = '(';
            infix[j++] = operand1;
            infix[j++] = ch;
            infix[j++] = operand2;
            infix[j++] = ')';
            push(&stack, infix[j - 1]); // Push the result onto the stack
        }
    }

    infix[strlen(infix) - 1] = '\0'; // Null-terminate the infix expression
    printf("Infix expression: %s\n", infix);
}

int main() {
    char postfix[100];

    printf("Enter a postfix expression: ");
    scanf("%s", postfix);

    postfixToInfix(postfix);

    return 0;
}
