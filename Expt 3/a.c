#include<stdio.h>
#include<stdlib.h>
#define MAX 4

int front = -1;
int rear = -1;

int cqueue[MAX];

void insert(int);
int isfull();
int isempty();
int delete();
void display();
int peek();

int isfull(){
	if((rear+1) % MAX == front)
		return 1;
	else return 0; 
}

int isempty(){
	if(front == -1 && rear == -1)
		return 1;
	else return 0;
}

void insert(int item){
	if(isfull()){
		printf("Overflow\n");
		exit(1);
	}
	if(front == -1)
		front = 0;
	rear = (rear + 1) % MAX;
	cqueue[rear] = item;	
}

int delete(){
	int item;
	if(isempty()){
		printf("Underflow\n");
		exit(1);
	}
	item = cqueue[front];
	front = (front + 1) % MAX;
	if(front == rear)
		front = -1, rear = -1;
	return item;		
}

int peek(){
	if(isempty()){
		printf("Underflow\n");
		exit(1);
	}
	return cqueue[front];
}

void display(){
	if(isempty()){
		printf("Empty queue\n");
		return;
	}
	int i = front;
	printf("Queue contents: ");
	if(front <= rear){
		while(i <= rear){
			printf(" %d", cqueue[i]);
		i++;
		}
	}
	else{
		while(i <= MAX-1){
			printf(" %d", cqueue[i]);
			i++;
		}
	
	for(i = 0; i <= rear; i++)
		printf(" %d", cqueue[i]);
	}
}

int main(){
	int item, s;
	do{
		printf("\n\n1.Insert ");
		printf("2.Delete ");
		printf("3.Peek ");
		printf("4.Display ");
		printf("5.Exit ");
		printf("\nEnter your choice :");
		scanf("%d", &s);
		switch(s){
			case 1:
				printf("Enter the element: ");
				scanf("%d", &item);
				insert(item);
				display();
				break;
			case 2:
				if(isempty())
					break;
				printf("%d dequeued from array\n", delete());
				display();
				break;
			case 3:
				printf("%d is the topmost element\n", peek());
				display();
				break;
			case 4:
				printf("Contents of the queue:");
				display();
				break;
			case 5: break;
			default: printf("Invalid choice\n");
		}
	}while(s != 5);
	return 0;
}
