#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MAX 100
#define BLANK ' '
#define TAB '\t'

char stack[MAX];
char infix[MAX];
char postfix[MAX];
int top = -1;

void push(char);
char pop();
void infixtopostfix();
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
		case '(': return 0;
		case '+' :
		case '-' : return 1;
		case '*':
		case '/':
		case '%': return 2;
		case '^': return 3;		
	}
}

int incomingpriority(char symbol){
	switch(symbol){
		case ')': return 0;
		case '+':
		case '-': return 1;
		case '*':
		case '/':
		case '%': return 2;
		case '^': return 4;		
	}
}

int whitespace(char symbol){
	if(symbol == BLANK || symbol == TAB)
		return 0;
	else return 1;
}

void infixtopostfix(){
	char symbol, next;
	int p = 0;
	for(int i = 0; i < strlen(infix); i++){
		symbol = infix[i];
		if(whitespace(symbol)){
			switch(symbol){
				case '(': push(symbol);
					break;
				case ')':
					while((next = pop()) != '('){
						postfix[p] = next;
						p++;
					}
					break;
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':
				case '^':
					while(top != 1 && (instackpriority(stack[top]) >= incomingpriority(symbol))){
						postfix[p] = pop();
						p++;
					}
					push(symbol);
					break;
				default: postfix[p] = symbol;
					p++;	
			}
			printf("%c\t%s\t\t%s\n", symbol, display(), postfix);
		}
	}
	while (top != -1)
		postfix[p++] = pop();
	postfix[p] = '\0';
}

int main(){
	printf("Enter the infix expression\n");
	scanf("%s", infix);
	printf("The infix expression is %s\n", infix);
	printf("Symbol\tStack\t\tPostfix\n");
	infixtopostfix();
	printf("The postfix expression is: %s\n", postfix);
	return 0;
}
