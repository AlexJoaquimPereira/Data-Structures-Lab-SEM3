#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 100
#define BLANK ' '
#define TAB '\t'

char stack[MAX];
char infix[MAX];
char prefix[MAX];
int top = -1;

void push(char);
char pop();
void infixtoprefix();
int instackpriority(char);
int incomingpriority(char);
int isfull();
int isempty();
int whitespace(char);

int isempty(){
	if(top == -1)
		return 1;
	else return 0;
}

int isfull(){
	if(top == (MAX - 1))
		return 1;
	else return 0;
}

void push(char symbol){
	if(isfull()){
		printf("Stack overflow\n");
		return;
	}
	top++;
	stack[top] = symbol;
}

char pop(){
	if(isempty()){
		printf("Stack underflow\n");
		exit(1);
	}
	return(stack[top--]);
}

int instackpriority(char symbol){
	switch(symbol){
		case ')':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 4;
	}
}

int incomingpriority(char symbol){
	switch(symbol){
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 3;
	}
}

int whitespace(char symbol){
	if(symbol == BLANK || symbol == TAB)
		return 0;
	else return 1;
}

void infixtoprefix(){
	char symbol, next;
	int p = 0;
	for(int i = strlen(infix)-1; i >= 0; i--){
		symbol = infix[i];
		if(whitespace(symbol)){
			switch(symbol){
				case ')': push(symbol);
					break;
				case '(':
					while((next = pop()) != ')'){
						prefix[p] = next;
						p++;
					}
					break;
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':
				case '^':
					while(top != -1 && (instackpriority(stack[top]) > incomingpriority(symbol))){
						prefix[p] = pop();
						p++;
					}
					push(symbol);
					break;
				default: prefix[p] = symbol;
					p++;
			}
			printf("%c\t%s\t%s\n", symbol, stack, prefix);
		}
	}
	while (top != -1)
		prefix[p++] = pop();
	int n = strlen(prefix) -1;
	for(int i = 0; i < n/2; i++){
		char temp = prefix[n - i];
		prefix[n - i] = prefix[i];
		prefix[i] = temp;
	}
	prefix[p] = '\0';
}

int main(){
	printf("Enter the infix expression\n");
	scanf("%s", infix);
	printf("The infix expression is %s\n", infix);
	printf("Symbol\tStack\tPrefix\n");
	infixtoprefix();
	printf("The prefix expression is: %s\n", prefix);
	return 0;
}
