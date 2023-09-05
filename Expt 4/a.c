#include<stdio.h>
#include<stdlib.h>

struct node{
	int info;
	struct node *link;
}*front = NULL, *rear = NULL;

void insert(int);
void delete();
void display();
int peek();
int isempty();

int isempty(){
	if(front == NULL)
		return 1;
	else return 0;
}

void insert(int data){
	struct node *tmp = (struct node*)malloc(sizeof(struct node));
	if(tmp == NULL){
		printf("Overflow\n");
		return;
	}
	tmp->info = data;
	tmp->link = NULL;
	if(front ==  NULL)
		front = tmp;
	else rear->link = tmp;
	rear = tmp;
}

void delete(){
	struct node *tmp;
	int item;
	if(isempty()){
		printf("Underflow\n");
		return;
	}
	item = front->info;
	tmp = front;
	front = front->link;
	free(tmp);
	printf("The deleted item is: %d\n", item);
}

void display(){
	struct node *p;
	if(isempty()){
		printf("Underflow\n");
		return;
	}
	p = front;
	printf("The queue is: ");
	while(p != NULL){
		printf("%d ", p->info);
		p = p->link;
	}
}



int main(){
	int s, data;
	do{
		printf("\nEnter your choice:\n");
		printf("1. Insert an element\n");
		printf("2. Delete an element\n");
		printf("3. Display the Queue contents\n");
		printf("4. Exit\n");
		scanf("%d", &s);
		switch(s){
			case 1:
				printf("\nEnter the element to insert: ");
				scanf("%d", &data);
				insert(data);
				break;
			case 2:
				delete();
				break;
			case 3:
				display();
				break;
			case 4:
				break;
			default: 
				printf("Invalid input\n");
		}
	}while(s != 4);
	return 0;
}
