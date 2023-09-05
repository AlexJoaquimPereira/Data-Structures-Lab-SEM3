//use sprintf

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

struct node{
	char *info;
	struct node *link;
}*top = NULL;

char postfix[MAX];
char infix[MAX];

void push(char *);
char * pop();
void display();
int isempty();
void postfixtoinfix();

int isempty(){
	if(top == NULL)
		return 1;
	else return 0;
}

void push(char *data){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	if(temp == NULL){
		printf("Unavailable heap space\n");
		return;
	}
	temp->info = data;
	temp->link = top;
	top = temp;
	printf("Test push %s\n", data);
}

char * pop(){
	char *data;
	if(isempty()){
		printf("Underflow\n");
		exit(1);
	}
	printf("Test pop %s\n", data);
	data = top->info;
	struct node *temp;
	temp = top;
	top = top->link;
	free(temp);
	printf("Test pop %s\n", data);
	return data;
}

void postfixtoinfix(){
	char *data = " ";
	char *a, *b, *c;
	for(int i = 0; i < strlen(postfix); i++){
		c = postfix[i];
		printf("Test for-loop %c\n", postfix[i]);
		if(postfix[i] >= '0' && postfix[i] <= '9'){
			printf("Test if-case %c\n",postfix[i]);
			push(&c);
		}
		else{
			printf("Test else-case %c\n", postfix[i]);
			a = pop();//strcpy(a, pop());
			b = pop();//strcpy(b, pop());
			strcat(data, "(");
			strcat(data, b);
			strcat(data, c);
			strcat(data, a);
			strcat(data, ")");
			printf("Test else-case %s\n", data);
			push(data);
		}
	}
}

int main(){
	printf("Enter the postfix expression: ");
	scanf("%s", postfix);
	postfixtoinfix();
	printf("The infix expression is: %s\n", infix);
	return 0;
}
