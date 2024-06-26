#include<stdio.h>
#include<stdlib.h>

struct node{
	struct node *prev;
	int info;
	struct node *next;
};

struct node * addtoempty(struct node *, int);
struct node * addatend(struct node *, int);
struct node * create(struct node *);
struct node * swap(struct node *);
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
	while(p->next != NULL)
		p = p->next;
	temp->prev = p;
	p->next = temp;
	return start;
}

struct node * create(struct node *start){
	int n, data;
	printf("Enter number of nodes: ");
	scanf("%d", &n);
	if(n == 0)
		return start;
	printf("Enter data: ");
	scanf("%d", &data);
	start = addtoempty(start, data);
	for(int i = 1; i < n; i++){
		printf("Enter data: ");
		scanf("%d", &data);
		start = addatend(start, data);
	}	
	return start;
}

struct node * swap(struct node *start) {
    struct node *p = start, *q = start->next;
    while (p != NULL && q != NULL) {

        p->next = q->next;
        q->prev = p->prev;
        p->prev = q;
        q->next = p;
        if (p->next != NULL) {
            p->next->prev = p;
        }
        if (q->prev != NULL) {
            q->prev->next = q;
        }
        if (start == p) {
            start = q;
        }
        p = p->next;
        if (p != NULL) {
            q = p->next;
        }
    } 
    return start;
}


void display(struct node *start){
	struct node *p = start;
	if(start == NULL){
		printf("Empty list\n");
		return;
	}
	printf("List contents\n");
	do{
		printf(" %d", p->info);
		p = p->next;
	}while(p != NULL);
	printf("\n");
}

int main(){
	struct node *start = NULL;
	printf("Fill the list\n");
	start = create(start);
	display(start);
	printf("Editing the list....\n");
	start = swap(start);
	display(start);
}