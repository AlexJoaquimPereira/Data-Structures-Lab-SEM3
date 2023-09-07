#include<stdio.h>
#include<stdlib.h>

struct node{
	struct node *prev;
	int info;
	struct node *next;
};

struct node * addtoempty(struct node *, int);
struct node * addatend(struct node *, int);
struct node * create(struct node *, int);
struct node * add(struct node *, struct node *);
struct node * reverse(struct node *);
void display(struct node*);

struct node * addtoempty(struct node *start, int data){
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->info = data;
	temp->next = NULL;
	temp->prev = NULL;
	start = temp;
	return start;
}

struct node * addatend(struct node *start, int data){
	struct node *p = start, *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->info = data;
	temp->next = NULL;
	if(start == NULL){
		temp->prev = NULL;
		start = temp;
		return start;
	}
	while(p->next != NULL)
		p = p->next;
	temp->prev = p;
	p->next = temp;
	return start;
}

struct node * create(struct node *start, int n){
	int data;
	if(n == 0)
		return start;
	data = n % 10;
	n = n / 10;
	start = addtoempty(start, data);
	while(n > 0){
		data = n % 10;
		n = n / 10;
		start = addatend(start, data);
	}	
	return start;
}

struct node * add(struct node *num1, struct node *num2){
	struct node *p = num1, *q = num2, *sum = NULL;
	int s = 0, carry = 0;
	while(p->next != NULL || q->next != NULL){
		if(p->next == NULL && q->next != NULL)
			s = q->info + carry;
		else if (q->next == NULL && p->next != NULL)
			s = p->info + carry;
		else s = p->info + q->info + carry;
		
		if(s > 9 || s < 0){
			carry = s / 10;
			s = s % 10;
		}
		printf("S = %d\n", s);
		sum = addatend(sum, s);
		/*
		if(p->next == NULL && q->next == NULL)
			break;
		else if(p->next == NULL && q->next != NULL)
			q = q->next;
		else if(p->next != NULL && q->next == NULL)
			p = p->next;
		else*/ p = p->next, q = q->next;
	}
	return sum;
}

struct node * reverse(struct node *start){
	struct node *p = start, *q = start->next;
	
	p->prev = q;
	p->next = NULL;
	while(q != NULL){
		q->prev = q->next;
		q->next = p;
		p = q;
		q = q->prev;
	}
	start = p;
	return start;
}

void display(struct node *start){
	struct node *p = start;
	if(start == NULL){
		printf("0\n");
		return;
	}
	do{
		printf("%d", p->info);
		p = p->next;
	}while(p != NULL);
	printf("\n");
}

int main(){
	struct node *num1 = NULL, *num2 = NULL, *sum = NULL;
	int n1, n2;
	printf("Enter the first number: ");
	scanf("%d", &n1);
	num1 = create(num1, n1);
	printf("Enter the second number: ");
	scanf("%d", &n2);
	num2 = create(num2, n2);
	printf("Adding both numbers...\n");
	sum = add(num1, num2);
	reverse(sum);
	printf("The sum is : ");
	display(sum);
}
