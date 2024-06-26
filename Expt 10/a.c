#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int n = 8;
int max_edges = 12;
int graph[MAX][MAX];

enum State {initial, waiting, visited, finished};
int time = 0;
int d[MAX], f[MAX];
enum State state[MAX];

int front = -1;
int rear = -1;
int cqueue[MAX];

void insert_graph(int, int);
void BFS(int);
void BFS_traversal(int v);
void DFS(int);
void display_graph();

int isempty();
void insert_queue(int);
int delete_queue();
void display_queue();

int isempty(){
	if(front == -1 || front == rear + 1)
		return 1;
	else return 0;
}

void insert_queue(int item){
	if(rear == MAX){
		printf("Overflow\n");
		return;
	}
	if(front == -1)
		front = 0;
	rear = rear + 1;
	cqueue[rear] = item;	
}

int delete_queue(){
	int item;
	if(isempty()){
		printf("Underflow\n");
		exit(1);
	}
	item = cqueue[front];
	front++;
	return item;		
}

void display_queue(){
	if(isempty()){
		printf("Underflow\n");
		return;
	}
	for(int i = front; i <= rear; i++)
		printf("%d ", cqueue[i]);
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

void BFS_traversal(int v){
	for(v = 0; v < n; v++)
		state[v] = initial;
	printf("Element\tQueue\n");
	BFS(v);
	for(v = 0; v < n; v++)
		if(state[v] == initial)
			BFS(v);
}

void BFS(int v){
	insert_queue(v);
	state[v] = waiting;
	while(isempty() == 0){
		v = delete_queue();
		state[v] = visited;
		printf("%d\t", v);
		display_queue();
		for(int i = 0; i < n; i++){
			if(graph[v][i] == 1 && state[i] == initial){
				insert_queue(i);
				state[i] = waiting;
			}
		}
	}
}

void DFS(int v){
	int i;
	time++;
	d[v] = time;
	state[v] = visited;
	printf("%d\t%d\n", v, d[v]);
	for(int i = 0; i < n; i++){
		if(graph[v][i] == 1 && state[i] == initial)
			DFS(i);
		f[v] = ++time;
		state[v] = finished;
	}
}

void display_graph(){
	int outsum, insum[n];
	printf("   ");
	for(int i = 1; i <= n; i++)
		printf("%3d", i);
	printf("Out\n");
	for(int i = 0; i < n; i++){
		outsum = 0, insum[i] = 0;
		printf("%3d", i+1);
		for(int j = 0; j < n; j++){
			printf("%3d", graph[i][j]);
			outsum += graph[i][j];
			insum[i] += graph[j][i];
		}
		printf("%3d", outsum);
		printf("\n");
	}
	printf(" In");
	for(int i = 0; i < n; i++)
		printf("%3d", insum[i]);
}
 
int main(){
	int org, dest;
	printf("Number of vertices: %d\n", n);
	printf("Maximum number of edges = %d\n", max_edges);
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
		graph[org][dest] = 1;
	}
	int s, vertex;
	do{
		printf("\n1. Enter an edge\n");
		printf("2. Perform Breadth First Search\n");
		printf("3. Perform Depth First Search\n");
		printf("4. Display the graph\n");
		printf("5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &s);
		switch(s){
			case 1: printf("Enter edge: ");
					scanf("%d %d", &org, &dest);
					insert_graph(org, dest);
					break;
			case 2: printf("Enter vertex: ");
					scanf("%d", &vertex);
					BFS_traversal(vertex);
					break;
			case 3: printf("Enter vertex: ");
					scanf("%d", &vertex);
					printf("Element\tTime\n");
					DFS(vertex);
					break;
			case 4: display_graph();
					break;
			case 5: break;
			default: printf("Invalid input\n");
		}
	}while(s != 5);
	return 0;
}
