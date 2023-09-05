#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<direct.h>
#define MAX 5

struct TASK{
	int taskID;
	char taskTitle[20];
	int taskDuration;
	int status;
}task[10];

int front = -1;
int rear = -1;
int queue[MAX];
int counter = 1;
int taskTimer = 0;

void insert(int);
int isfull();
int isempty();
int delete();
void display();
int peek();
struct TASK readfromfile(char *, FILE *);
void scheduletask();
void createtask();
void delay(int);

int isfull(){
	if(front == (rear+1) % MAX)
		return 1;
	else return 0; 
}

int isempty(){
	if(front == -1)
		return 1;
	else return 0;
}

void insert(int item){
	if(isfull()){
		printf("Tasks overload...wait for %d seconds\n", taskTimer);
		exit(1);
	}
	if(front == -1)
		front = 0;
	rear = (rear + 1) % MAX;
	queue[rear] = item;	
}

int delete(){
	int item;
	if(isempty()){
		printf("No tasks available to execute\n");
		exit(1);
	}
	item = queue[front];
	if(front == rear)
		front = -1, rear= -1;
	if(front == MAX - 1)
		front = (front + 1) % MAX;
	return item;		
}

void display(){
	if(isempty()){
		printf("No tasks available to execute\n");
		return;
	}
	int i = front;
	if(front <= rear)
		while(i <= rear){
			printf(" %d %s", task[queue[i]].taskID, task[queue[i]].taskTitle);
			i++;
		}
	else{
		while(i <= MAX-1){
			printf(" %d %s", task[queue[i]].taskID, task[queue[i]].taskTitle);
			i++;
		}
	for(i = 0; i <= rear; i++)
		printf(" %d %s", task[queue[i]].taskID, task[queue[i]].taskTitle);
	}
}

int main(){
	char c, filename[20];
	int taskIDchoice, temp, s;
	printf("Do you want to take input from a file? Y/N: ");
	scanf("%c", &c);
	if(c == 'Y'){
		printf("Enter filename: ");
		scanf("%s", filename);
		FILE *file = fopen(filename, "r");
		if (file == NULL) {
        	printf("Error opening %s\n", filename);
        	exit(1);
    	}
		while(!EOF){
			task[counter - 1] = readfromfile(filename,file);
			counter++;
		}
		fclose(file);
	}
	do{
		printf("\n1.Create task ");
		printf("2.Schedule ");
		printf("3.Run ");
		printf("4.Display ");
		printf("5.Exit ");
		printf("\nEnter your choice: ");
		scanf("%d", &s);
		switch(s){
			case 1:
				if(counter <= 10)
					createtask();
				else printf("Tasks overload...wait for %d seconds\n", taskTimer);
				break;
			case 2:
				if(rear == MAX-1){
					printf("Tasks overload...wait for %d seconds\n", taskTimer);
					break;
				}
				scheduletask();
				break;
			case 3:
				if(isfull()){
					printf("Tasks overload...wait for %d seconds\n", taskTimer);
					break;
				}
				temp = delete();
				printf("Executing task ID: %d: %s...Wait for %d seconds\n", temp + 1, task[temp].taskTitle, task[temp].taskDuration);
				delay((task[temp].taskDuration));
				printf("Task completed!\n");
				break;
			case 4:
				display();
			case 5:
				break;
			default: 
				printf("Invalid input\n");
		}
	}while(s != 5);
}

void createtask(){
	printf("Task ID: %d\n", counter);
	task[counter-1].taskID = counter;
	printf("Enter the task: ");
	scanf("%s", task[counter-1].taskTitle);
	printf("Status: Unscheduled\n");
	task[counter-1].status = 0;
	counter++;
}

void scheduletask(){
	int taskIDchoice;
	printf("Enter the task ID: ");
	scanf("%d", &taskIDchoice);
	printf("%s\n", task[taskIDchoice-1].taskTitle);
	printf("Enter the time needed for the task: ");
	scanf("%d", &task[taskIDchoice-1].taskDuration);
	printf("Status: Scheduled\n");
	task[taskIDchoice-1].status = 1;
	insert(taskIDchoice - 1);
}

struct TASK readfromfile(char *filename, FILE *file)
{
	int taskID, taskDuration, status;
	char taskTitle[20];
    struct TASK temp;
    fscanf(file, "%d %s", &taskID, taskTitle) == 2;
    temp.taskID = taskID;
    strcpy(temp.taskTitle, taskTitle);
    temp.taskDuration = taskDuration;
	return temp;
}
