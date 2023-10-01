#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct node {
    char data[MAX];
    struct node* link;
};

struct node* top = NULL;
char postfix[MAX];
char* infix = NULL;

void push(const char* data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL){
        printf("Not enough memory...stack overflow\n");
        return;
    }
    strcpy(temp->data, data);
    temp->link = top;
    top = temp;
}

struct node* pop() {
    if (top == NULL) {
        printf("Stack underflow\n");
        exit(1);
    }
    struct node* temp = top;
    top = top->link;
    return temp;
}

void postfixToInfix() {
    int len = strlen(postfix);
    for (int i = 0; i < len; i++) {
        char ch = postfix[i];
        if (ch >= '0' && ch <= '9') {
            char operand[2] = {ch, '\0'};
            push(operand);
        } else {
            struct node* operand2 = pop();
            struct node* operand1 = pop();
            int infixsize = strlen(operand1->data) + 3 + strlen(operand2->data) + 1;
            infix = (char*)malloc(infixsize * sizeof(char));
            snprintf(infix, infixsize, "(%s%c%s)", operand1->data, ch, operand2->data);
            push(infix);
            free(operand1);
            free(operand2);
        }
    }
}

int main() {
    printf("Enter a postfix expression: ");
    scanf("%s", postfix);
    printf("Char\tStack\tInfix\n");
    postfixToInfix();
    printf("Infix expression: %s\n", infix);
    free(infix);
    return 0;
}