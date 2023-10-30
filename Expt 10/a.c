#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int n;
int graph[MAX][MAX];

typedef enum {initial, waiting, visited, finished} State;
int time = 0;
int d[MAX], f[MAX];
State state[MAX];

int front = -1;
int rear = -1;
int cqueue[MAX];

void insert_graph();
void insert();
void BFS(int);
void BFS_traversal();
void DFS(int);
void display_graph();

int isempty();
void insert_queue(int);
int delete_queue();
void display_queue();

int isempty(){
	if(front == -1)
		return 1;
	else return 0;
}

void insert_queue(int item){
	if(front == (rear+1) % MAX){
		printf("Overflow\n");
		exit(1);
	}
	if(front == -1)
		front = 0;
	rear = (rear + 1) % MAX;
	cqueue[rear] = item;	
}

int delete_queue(){
	int item;
	if(isempty()){
		printf("Underflow\b");
		exit(1);
	}
	item = cqueue[front];
	if(front == rear)
		front = -1, rear= -1;
	if(front == MAX - 1)
		front = (front + 1) % MAX;
	return item;		
}

void display_queue(){
	if(isempty()){
		printf("Underflow\n");
		return;
	}
	int i = front;
	if(front <= rear)
		while(i <= rear)
			printf(" %d", cqueue[i++]);
	else
		while(i <= MAX-1)
			printf(" %d", cqueue[i++]);
	for(i = 0; i <= rear; i++)
		printf(" %d", cqueue[i]);
}

void insert_graph(int org, int dest){
	if(org < 0 || org >= n){
		printf("Invalid origin\n");
		return;
	}
	if(dest < 0 || dest >= n){
		printf("Invalid destination\n");
		return;
	}
	graph[org][dest] = 1;
}

void BFS_traversal(){
	int v;
	for(v = 0; v < n; v++)
		state[v] = initial;
	printf("Enter start vertex: ");
	scanf("%d", &v);
	BFS(v);
	for(v = 0; v < n; v++)
		if(state[v] == initial)
			BFS(v);
}

void BFS(int v){
	insert_queue(v);
	state[v] = waiting;
	while(!isempty()){
		v = delete_queue();
		state[v] = visited;
		printf(" %d ", v);
		for(int i = 0; i < n; i++){
			if(graph[v][i] == 1 && state[i] == initial){
				insert_queue(i);
				state[i] = waiting;
			}
		}
	}
}

void DFS(int v){
	time++;
	d[v] = time;
	state[v] = visited;
	printf(" %d ", v);
	for(int i = 0; i < n; i++){
		if(graph[v][i] == 1 && state[i] == initial)
			DFS(i);
		f[v] = ++time;
		state[v] = finished;
	}
}

int main(){
	int org, dest;
	printf("Number of vertices: ");
	scanf("%d", &n);
	int max_edges = n *(n - 1) / 2;
	printf("Fill the graph: Enter (-1, -1) to break\n");
	for(int i = 1; i <= max_edges; i++){
		printf("Enter edge %d: ", i);
		scanf("%d %d", &org, &dest);
		if(org == -1 && dest == -1)
			break;
		if(org >= n || dest >= n || org < 0 || dest < 0){
			printf("Invalid edge\n");
			i--;
		}
		insert_graph(org, dest);
	}
	int s, vertex;
	do{
		printf("\n1. Enter a vertex\n");
		printf("2. Perform Breadth First Search\n");
		printf("3. Perform Depth First Search\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &s);
		switch(s){
			case 1: printf("Enter edge: ");
					scanf("%d %d", &org, &dest);
					insert_graph(org, dest);
					break;
			case 2: printf("Enter vertex: ");
					scanf("%d", &vertex);
					BFS(vertex);
					break;
			case 3: printf("Enter vertex: ");
					scanf("%d", &vertex);
					DFS(vertex);
					break;
			case 4: break;
			default: printf("Invalid input\n");
		}
	}while(s != 4);
	return 0;
}
