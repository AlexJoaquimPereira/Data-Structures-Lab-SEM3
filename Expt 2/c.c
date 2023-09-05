#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

long int lstack[MAX];
float fstack[MAX];
char postfix[MAX];
int top = -1;
int floatint;

void push(float);
float pop();
void evalpostfix();
int isfull();
int isempty();

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

void push(float symbol){
	if(isfull()){
		printf("Stack overflow\n");
		return;
	}
	if (floatint == 1)
		fstack[++top] = symbol;
	else lstack[++top] = (long int)symbol;
}

float pop(){
	if(isempty()){
		printf("Stack underflow\n");
		exit(1);
	}
	if (floatint == 1)
		return(fstack[top--]);
	else return((long int)lstack[top--]);
}

void evalpostfix(){
	float a, b;
	float temp;
	for(int i = 0; i < strlen(postfix); i++){
		if(postfix[i] >= '0' && postfix[i] <= '9')
			push((float)(postfix[i] - '0'));
		else{
			b = pop();
			if (floatint == 1) {
				printf("%f\t", b);
   				for (int j = 0; j <= top; j++)
        		printf("%f,", fstack[j]);
			} else {
				printf("%ld\t", b);
    			for (int j = 0; j <= top; j++)
        			printf("%ld,", lstack[j]);
			}
			printf("\n");
			a = pop();
			if (floatint == 1) {
				printf("%f\t", a);
   				for (int j = 0; j <= top; j++)
        		printf("%f,", fstack[j]);
			} else {
				printf("%ld\t", a);
    			for (int j = 0; j <= top; j++)
        			printf("%ld,", lstack[j]);
			}
			printf("\n");
			switch(postfix[i]){
				case '+':
					temp = b + a;
					break;
				case '-':
					temp = b - a;
					break;
				case '*':
					temp = b * a;
					break;
				case '/':
					temp = b / a;
					break;
				case '%':
					temp = (long int)b % (long int)a;
					break;
				case '^':
					temp = 1;
					for(int i = 1; i <= a; i++)
						temp = temp * b;
					break;
				case 'A': 
					temp = 3;
					break;
				case 'B':
				case 'C':
				case 'D':
				case 'E':
					temp = 2;
					break;
				case 'F':
					temp = 1;
					break;
			}
			push(temp);
		}
	}
}

int main(){
	printf("Enter the postfix expression: ");
	scanf("%s", postfix);
	do{
		printf("\nDo you want it as a 1. Float or 2. Integer?: ");
		scanf("%d", &floatint);
		if (floatint != 1 && floatint != 2)
			printf("Invalid input\n");
	} while (floatint != 1 && floatint != 2);
	printf("Symbol\tStack\t\n");
	evalpostfix();
	if(floatint == 1)
		printf("The evaluation is: %f\n", fstack[0]);
	else 
		printf("The evaluation is: %f\n", lstack[0]);
	return 0;
}
