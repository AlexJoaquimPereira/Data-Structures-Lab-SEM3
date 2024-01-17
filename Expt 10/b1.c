#include <stdio.h>
#include <stdlib.h>

int max_edges = 12;
int n = 8;

struct vertex;
struct edge{
    struct vertex *destvertex;
    struct edge *nextedge;
};

struct vertex{
    struct vertex *nextvertex;
    int info;
    struct edge *firstedge;
} *start = NULL;

void insertvertex(int u){
    struct vertex *tmp, *ptr;
    tmp = (struct vertex *)malloc(sizeof(struct vertex));
    tmp->info = u;
    tmp->nextvertex = NULL;
    tmp->firstedge = NULL;
    if (start == NULL){
        start = tmp;
        return;
    }
    ptr = start;
    while (ptr->nextvertex != NULL)
        ptr = ptr->nextvertex;
    ptr->nextvertex = tmp;
}

struct vertex *findvertex(int u){
    struct vertex *ptr, *loc;
    ptr = start;
    while (ptr != NULL){
        if (ptr->info == u){
            loc = ptr;
            return loc;
        }
        else
            ptr = ptr->nextvertex;
    }
    loc = NULL;
    return loc;
}

void insertedge(int u, int v){
    struct vertex *locu, *locv;
    struct edge *ptr, *tmp;
    locu = findvertex(u);
    locv = findvertex(v);
    if (locu == NULL || locv == NULL){
        printf("Origin or destination vertex not present\n");
        return;
    }
    tmp = (struct edge *)malloc(sizeof(struct edge));
    tmp->destvertex = locv;
    tmp->nextedge = NULL;
    if (locu->firstedge == NULL){
        locu->firstedge = tmp;
        return;
    }
    ptr = locu->firstedge;
    while (ptr->nextedge != NULL)
        ptr = ptr->nextedge;
    ptr->nextedge = tmp;
}

void delete_edge(int u, int v){
    struct vertex *locu;
    struct edge *q, *tmp;
    locu = findvertex(u);
    if (locu == NULL || locu->firstedge == NULL){
        printf("Vertex/edge not present\n");
        return;
    }
    if (locu->firstedge->destvertex->info == v){
        tmp = locu->firstedge;
        locu->firstedge = locu->firstedge->nextedge;
        free(tmp);
        return;
    }
    q = locu->firstedge;
    while (q->nextedge != NULL){
        if (q->nextedge->destvertex->info == v){
            tmp = q->nextedge;
            q->nextedge = tmp->nextedge;
            free(tmp);
            return;
        }
        q = q->nextedge;
    }
    printf("Edge not present in the graph\n");
}

void delete_vertex(int u){
    struct vertex *prev = NULL;
    struct vertex *current = start;
    struct vertex *temp = NULL;
    while (current != NULL){
        if (current->info == u){
            if (prev == NULL)
                start = current->nextvertex;
            else
                prev->nextvertex = current->nextvertex;
            temp = current;
            current = current->nextvertex;
            free(temp);
        }
        else{
            prev = current;
            current = current->nextvertex;
        }
    }
    current = start;
    while (current != NULL){
        delete_edge(current->info, u);
        current = current->nextvertex;
    }
}

void display(){
    struct vertex *ptr;
    struct edge *q;
    ptr = start;
    while (ptr != NULL){
        printf("Vertex %d ->", ptr->info);
        q = ptr->firstedge;
        while (q != NULL){
            if (q->nextedge == NULL)
                printf(" %d", q->destvertex->info);
            else
                printf(" %d->", q->destvertex->info);
            q = q->nextedge;
        }
        printf("\n");
        ptr = ptr->nextvertex;
    }
}

int main(){
	int org, dest;
	printf("Number of vertices: %d\n", n);
	int max_edges = 12;
    for(int i = 0; i < n; i++)
        insertvertex(i);
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
					scanf("%d %d", &org, &dest);
					delete_edge(org, dest);
					break;
			case 3: printf("Enter vertex: ");
					scanf("%d", &vertex);
					delete_vertex(vertex);
					break;
			case 4: display();
					break;
			case 5: break;
			default: printf("Invalid input\n");
		}
	}while(s != 5);
	return 0;
}
