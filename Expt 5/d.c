#include<stdio.h>
#include<stdlib.h>

struct node{
	int info;
	struct node *link;
};

struct node * addtoempty(struct node *, int);
struct node * addatend(struct node *, int);
struct node * create(struct node *);
struct node * delete(struct node *);
void display(struct node*);

struct node * addtoempty(struct node *last, int data){
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->info = data;
	last = temp;
	last->link = last;
	return last;
}

struct node * addatend(struct node *last, int data){
	struct node *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp->info = data;
	temp->link = last->link;
	last->link = temp;
	last = temp;
	return last;
}

struct node * create(struct node *last){
	int n, data;
	printf("Enter number of nodes: ");
	scanf("%d", &n);
	if(n == 0)
		return last;
	printf("Enter data: ");
	scanf("%d", &data);
	last = addtoempty(last, data);
	for(int i = 1; i < n; i++){
		printf("Enter data: ");
		scanf("%d", &data);
		last = addatend(last, data);
	}	
	return last;
}

struct node * delete(struct node *last){
	if (last == NULL) {
		printf("Empty list\n");
        exit(1);
    }
    struct node* p = last;
    struct node* temp;
    do {
        temp = p->link;
        p->link = temp->link;
        free(temp);
        p = p->link;
    } while (p!=last && p->link!=last);
	return last;
}


void display(struct node *last){
	struct node *p = last->link;
	if(last == NULL){
		printf("Empty list\n");
		return;
	}
	printf("List contents: ");
	do{
		printf(" %d", p->info);
		p = p->link;
	}while(p != last->link);
}

int main(){
	struct node *last = NULL;
	printf("Fill the list\n");
	last = create(last);
	printf("Editing the list...\n");
	last = delete(last);
	display(last);
}
