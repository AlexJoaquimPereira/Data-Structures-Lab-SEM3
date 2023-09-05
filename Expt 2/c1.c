#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

//long int lstack[MAX];
float stack[MAX];
char *postfix = "FDCA+/D*B*B-DEA^^-";
int top = -1;
//int floatint;

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
    //[++top] = symbol;
	stack[++top] = symbol;
}

float pop(){
	if(isempty()){
		printf("Stack underflow\n");
		exit(1);
    }
	return(stack[top--]);
}

void evalpostfix(){
	float a, b;
	float temp;
	for(int i = 0; i < strlen(postfix); i++){
		if(postfix[i] >= 'A' && postfix[i] <= 'F'){
            switch(postfix[i]){
                case 'A': 
					temp = 3.000000;
					break;
				case 'B':
				case 'C':
				case 'D':
				case 'E':
					temp = 2.000000;
					break;
				case 'F':
					temp = 1.000000;
					break;
            }
        }
		else{
			b = pop();
			a = pop();
			switch(postfix[i]){
				case '+':
					temp = b + a;
					break;
				case '-':
					temp =b -a;
					break;
				case '*':
					temp = b * a;
					break;
				case '/':
					temp = b / a;
					break;
				case '%':
					temp = (int)b % (int)a;
					break;
				case '^':
					temp = 1;
					for(int i = 1; i <= a; i++)
						temp = temp * b;
					break;
			}
		}
        push(temp);
	}
}

int main(){
	printf("Enter the postfix expression: ");
	printf("%s", postfix);
    printf("\nDo you want it as a 1. Float or 2. Integer?: 1\n");
	/*do{
		printf("\nDo you want it as a 1. Float or 2. Integer?: ");
		scanf("%d", &floatint);
		if (floatint != 1 && floatint != 2)
			printf("Invalid input\n");
	} while (floatint != 1 && floatint != 2);*/
	printf("Symbol\tStack\t\n");
	evalpostfix();
	//if(floatint == 1)
		printf("The evaluation is: %f\n", stack[0]);
	//else 
	//	printf("The evaluation is: %f\n", lstack[0]);
	return 0;
}
