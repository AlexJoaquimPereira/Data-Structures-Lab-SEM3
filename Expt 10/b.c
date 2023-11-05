#include <stdio.h>
#include <stdlib.h>

struct edge{
	struct vertex *destvertex;
	struct edge *nextedge;
};

struct vertex{
	struct vertex *nextvertex;
	int info;
	struct edge *firstedge;
}*start = NULL;

void insert(int x){
	struct vertex *ptr, *temp;
	temp = (struct vertex *)malloc(sizeof(struct vertex));
	temp->nextvertex = NULL;
	temp->firstedge = NULL;
	temp->info = x;
	if(start == NULL){
		start = temp;
		return;
	}
	ptr = start;
	while(ptr->nextvertex != NULL)
		ptr = ptr->nextvertex;
	ptr->nextvertex = temp;
}

struct vertex * findvertex(int u){
	struct vertex *ptr;
	ptr = start;
	while(ptr != NULL){
		if(ptr->info == u);
			return ptr;
		ptr = ptr->nextvertex;
	}
	return NULL;
}

void insertedge(int u, int v){
	struct edge *temp, *ptr;
	struct vertex *locu, *locv;
	locu = findvertex(u);
	locv = findvertex(v);
	if(locu == NULL|| locv == NULL){
		printf("Invalid\n");
		return;
	}
	temp = (struct edge *)malloc(sizeof(struct edge));
	temp->destvertex = locv;
	temp->nextedge = NULL;
	if(locu->firstedge == NULL){
		locu->firstedge = temp;
		return;
	}
	ptr = locu->firstedge;
	while(ptr->destvertex != NULL)
		ptr = ptr->nextedge;
	ptr->nextedge = temp;
}

void delete_edge(int u, int v){
	struct vertex * locu;
	struct edge *temp, *q;
	locu = findvertex(u);
	if(locu == NULL){
		printf("Vertex not found\n");
		return;
	}
	if(locu->firstedge == NULL){
		printf("No edge present\n");
		return;
	}
	if(locu->firstedge->destvertex->info == v){
		temp = locu->firstedge;
		locu->firstedge = temp->nextedge;
		free(temp);
		return;
	}
	q = locu->firstedge;
	while(q->nextedge != NULL){
		if(q->nextedge->destvertex->info == v){
			temp = q->nextedge;
			q->nextedge = temp->nextedge;
			free(temp);
			return;
		}
		q = q->nextedge;
	}
	printf("Edge not found\n");
}

void delete_incoming_edges(int u){
	struct vertex *ptr = start;
	struct edge *temp, *q;
	while(ptr!=NULL){
		if(ptr->firstedge == NULL){
			ptr = ptr->nextvertex;
			continue;
		}
		if(ptr->firstedge->destvertex->info == u){
			temp = ptr->firstedge;
			ptr->firstedge = temp->nextedge;
			free(temp);
		}
		q = ptr->firstedge;
		while(q->nextedge != NULL){
			if(q->nextedge->destvertex->info == u){
				temp = q->nextedge;
				q->nextedge = temp->nextedge;
				free(temp);
			}
			q = q->nextedge;
		}
		ptr = ptr->nextvertex;
	}
}

void delete_vertex(int u){
	struct vertex *temp, *ptr;
	struct edge *temp1, *q;
	if(start == NULL){
		printf("No vertices\n");
		return;
	}
	delete_incoming_edges(u);
	if(start->info == u){
		temp = start;
		start = start->nextvertex;
	}
	else{
		ptr = start;
		while(ptr != NULL){
			if(ptr->nextvertex->info == u){
				temp= ptr->nextvertex;
				ptr->nextvertex = temp->nextvertex;
			}
			ptr = ptr->nextvertex;
		}
		if(ptr->nextvertex == NULL){
			printf("No vertex found\n");
			return;
		}
	}
	q = temp->firstedge;
	while(q != NULL){
		temp1 = q;
		q = temp1->nextedge;
		free(temp1);
	}
	free(temp);
}

void display(){
	struct vertex *ptr;
	struct edge *q;
	if(start == NULL){
		printf("List empty\n");
		return;
	}
	ptr = start;
	while(ptr != NULL){
		printf("%d-> ", ptr->info);
		q = ptr->firstedge;
		while(q != NULL){
			printf("%d-> ", q->destvertex->info);
			q = q->nextedge;
		}
		printf("\n");
		ptr = ptr->nextvertex;
	}
}

 
int main(){
	int org, dest, n;
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
		insertedge(org, dest);
	}
	int s, vertex, edge;
	do{
		printf("\n1. Enter an edge\n");
		printf("2. Delete an edge\n");
		printf("3. Delete a vertex\n");
		printf("4. Display the graph\n");
		printf("5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &s);
		switch(s){
			case 1: printf("Enter edge: ");
					scanf("%d %d", &org, &dest);
					insertedge(org, dest);
					break;
			case 2: printf("Enter edge: ");
					scanf("%d", &edge);
					delete_incoming_edges(edge);
					break;
			case 3: printf("Enter vertex: ");
					scanf("%d", &vertex);
					deletevertex(vertex);
					break;
			case 4: display();
					break;
			case 5: break;
			default: printf("Invalid input\n");
		}
	}while(s != 5);
	return 0;
}
