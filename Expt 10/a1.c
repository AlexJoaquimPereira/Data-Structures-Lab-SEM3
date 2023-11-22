#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define initial 1
#define visited 2
#define finished 3
int d[MAX], f[MAX];
int time = 0;
int state[MAX];
int stack[MAX], top = -1;
int adj[MAX][MAX];
int n = 8, max_edges = 12;
int queue[MAX], front = -1, rear = -1;

void insert_graph(int origin, int destin)
{
    if (origin < 0 || origin >= n)
    {
        printf("Origin vertex does not exist\n");
        return;
    }
    if (destin < 0 || destin >= n)
    {
        printf("Destination vertex does not exist\n");
        return;
    }
    adj[origin][destin] = 1;
}
void delete(int origin, int destin)
{
    if (origin >= n || destin >= n || origin < 0 || destin < 0 || adj[origin][destin] == 0)
    {
        printf("The edge does not exist\n");
        return;
    }
    adj[origin][destin] = 0;
}
void display(){
	int outsum, insum[n];
	printf("   ");
	for(int i = 1; i <= n; i++)
		printf("%3d", i);
	printf("Out\n");
	for(int i = 0; i < n; i++){
		outsum = 0, insum[i] = 0;
		printf("%3d", i+1);
		for(int j = 0; j < n; j++){
			printf("%3d", adj[i][j]);
			outsum += adj[i][j];
			insum[i] += adj[j][i];
		}
		printf("%3d", outsum);
		printf("\n");
	}
	printf(" In");
	for(int i = 0; i < n; i++)
		printf("%3d", insum[i]);
}
void addVertex()
{
    if (n >= MAX)
    {
        printf("Graph is full, cannot add more vertices\n");
        return;
    }
    n++;
    printf("Vertex %d added.\n", n - 1);
}
void insertq(int vertex)
{
    if (rear == MAX - 1)
    {
        printf("Queue overflow\n");
    }
    else
    {
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = vertex;
    }
}
int delq()
{
    int item;
    if (front == -1 || front > rear)
    {
        printf("Queue Underflow\n");
    }
    else
    {
        item = queue[front];
        front++;
        return item;
    }
}
void displayQueue(int q[], int front, int rear)
{
    if (front == -1)
    {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    for (int i = front; i <= rear; i++)
    {
        printf("%d ", q[i]);
    }
    printf("\n");
}
void push(int v)
{
    if (top == MAX - 1)
    {
        printf("Stack overflow\n");
    }
    else
    {
        top = top + 1;
        stack[top] = v;
    }
}
int pop()
{
    int v;
    if (top == -1)
    {
        printf("Stack underflow\n");
        exit(1);
    }
    v = stack[top];
    top = top - 1;
    return v;
}
int isEmpty()
{
    return top == -1;
}
void displayStackDFS(int s[], int top, int v)
{
    printf("Stack (DFS at vertex %d): ", v);
    for (int i = 0; i <= top; i++)
    {
        printf("%d ", s[i]);
    }
    printf("\n");
}
void DFS(int v)
{
    int i;
    time++;
    d[v] = time;
    printf("%d\n", v);
    state[v] = visited;
    for (i = 0; i < n; i++)
    {
        if (adj[v][i] == 1 && state[i] == initial)
            DFS(i);
    }
    state[v] = finished;
    f[v] = ++time;
}
void DFS_stack(int v)
{
    int i;
    push(v);
    while (top != -1)
    {
        v = pop();
        if (state[v] == initial)
        {
            printf("%d ", v);
            state[v] = visited;
        }
        for (i = n - 1; i >= 0; i--)
        {
            if (adj[v][i] == 1 && state[i] == initial)
                push(i);
        }
        displayStackDFS(stack, top, v);
    }
    printf("\n");
}
void DF_Traversal()
{
    int v;
    for (v = 0; v < n; v++)
        state[v] = initial;
    printf("Enter starting vertex for Depth First Search : ");
    scanf("%d", &v);
    DFS_stack(v);
    for (v = 0; v < n; v++)
        if (state[v] == initial)
            DFS_stack(v);
}
void recursiveDF_traversal()
{
    int v;
    for (v = 0; v < n; v++)
        state[v] = initial;
    printf("Enter starting vertex for Depth First Search : ");
    scanf("%d", &v);
    DFS(v);
    for (v = 0; v < n; v++)
        if (state[v] == initial)
            DFS(v);
}
void BFS_traversal()
{
    int v;
    for (v = 0; v < n; v++)
    {
        state[v] = initial;
    }
    printf("Enter starting vertex for BFS traversal: ");
    scanf("%d", &v);
    insertq(v);
    state[v] = visited;
    printf("BFS Traversal (Queue Operations):\n");
    while (front != -1 && !(front > rear))
    {
        v = delq();
        printf("%d ", v);
        for (int i = 0; i < n; i++)
        {
            if (adj[v][i] == 1 && state[i] == initial)
            {
                insertq(i);
                state[i] = visited;
            }
        }
        displayQueue(queue, front, rear);
    }
    printf("\n");
}
void deleteVertex(int vertex)
{
    if (vertex < 0 || vertex >= n)
    {
        printf("Vertex does not exist\n");
        return;
    }
    // Delete edges connected to the vertex
    for (int i = 0; i < n; i++)
    {
        if (adj[vertex][i] == 1)
        {
            adj[vertex][i] = 0;
        }
        if (adj[i][vertex] == 1)
        {
            adj[i][vertex] = 0;
        }
    }
    // Shift remaining vertices to fill the gap
    for (int i = vertex; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adj[i][j] = adj[i + 1][j];
        }
    }
    for (int i = vertex; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adj[j][i] = adj[j][i + 1];
        }
    }
    n--;
    printf("Vertex %d deleted.\n");
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
		adj[org][dest] = 1;
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
			case 2: BFS_traversal();
					break;
			case 3: printf("Element\tTime\n");
					DFS_stack(vertex);
					break;
			case 4: display();
					break;
			case 5: break;
			default: printf("Invalid input\n");
		}
	}while(s != 5);
	return 0;
}
