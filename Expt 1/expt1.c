#include<stdio.h>
#include<stdlib.h>

struct node * create(struct node *);
struct node * addatend(struct node *, int);
struct node * addatbeg(struct node *, int );
void display (struct node *);
void get_union (struct node *, struct node *);
void get_intersection (struct node *, struct node *);
void get_difference (struct node *, struct node *);
int is_present(struct node *, int);

struct node
{
	int info;
	struct node *link;
};

struct node * create(struct node *start)
{
	int n, data;
	printf("Enter number of nodes: ");
	scanf("%d", &n);
	start = NULL;
	if (n == 0)
		return start;
	printf("Enter element 1: ");
	scanf("%d", &data);
	start = addatbeg(start, data);
	for(int i = 2; i <= n; i++){
		printf("Enter element %d: ", i);
		scanf("%d", &data);
		start = addatend(start, data);
	}
	return start;
}

struct node * addatend(struct node *start, int data)
{
	struct node *p, *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp -> info = data;
	p = start;
	while (p -> link != NULL)
		p = p -> link;
	p -> link = temp;
	temp -> link = NULL;
	return start;
}

struct node * addatbeg(struct node *start, int data)
{
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node));
	temp -> info = data;
	temp -> link = start;
	start = temp;
	return start;
}

void display (struct node *start)
{
    struct node *p;
    if (start == NULL){
        printf("Empty list\n");
        return;
    }
    p = start;
    printf("\n");
    while(p != NULL){
        printf(" %d", p -> info);
        p = p -> link;
    }
}

int main()
{
	struct node *start1 = NULL, *start2 = NULL;
	int s, n, data;

	printf("Enter the elements in set 1: \n");
	start1 = create(start1);

	printf("Enter the elements in set 2: \n");
	start2 = create(start2);

	do
	{
		printf("\nSelect option:\n");
		printf("1. Union\n");
		printf("2. Intersection\n");
		printf("3. Difference\n");
		printf("4. Exit\n");
		scanf("%d", &s);
		switch(s)
		{
			case 1:
				get_union (start1, start2);
				break;
			case 2:
				get_intersection (start1, start2);
				break;
			case 3:
				get_difference (start1, start2);
				break;
			case 4:
				break;
			default:
				printf("Invalid input\n");
		}
	}while(s!=4);
}

void get_union (struct node *start1, struct node *start2)
{
	struct node *p1 = start1, *p3 = NULL;
	p3 = addatbeg(p3, p1 -> info);
		p1 = p1 -> link;
	while(p1 != NULL){
		p3 = addatend(p3, p1 -> info);
		p1 = p1 -> link;
	}
	struct node *p2 = start2;
	while (p2!= NULL){
		if (!is_present(start1, p2->info))
        	p3 = addatend(p3, p2->info);
		p2 = p2->link;
	}
	display(p3);
}

void get_intersection (struct node *start1, struct node *start2)
{
	struct node *p1 = start1, *p2 = start2, *p3 = NULL;
    while (p2 != NULL) {
        if (is_present(start1, p2->info))
            p3 = addatbeg(p3, p2->info);
        p2 = p2->link;
    }
	display (p3);
}

void get_difference (struct node *start1, struct node *start2)
{
	struct node *p1 = start1, *p2 = start2, *p3 = NULL;
	printf("A - B : ");
	if (!is_present(start2, p1->info))
        p3 = addatbeg(p3, p1->info);
	p1 = p1->link;
    while (p1!= NULL) {
        if (!is_present(start2, p1->info)) 
            p3 = addatend(p3, p1->info);
        p1 = p1->link;
    }
	display(p3);
	p1 = start1, p2 = start2, p3 = NULL;
	printf("\nB - A: ");
	if (!is_present(start1, p2->info))
        p3 = addatbeg(p3, p2->info);
	p2 = p2->link;
	while (p2!= NULL) {
        if (!is_present(start1, p2->info))
            p3 = addatend(p3, p2->info);
        p2 = p2->link;
    }
	display(p3);
}

int is_present(struct node *start, int data) {
    struct node *p = start;
    while (p->link != NULL) {
        if (p->info == data) 
            return 1;
        p = p->link;
    }
    return 0;
}