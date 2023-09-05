#include<stdio.h>
#include<stdlib.h>

struct node * create(struct node *);
struct node * addatend(struct node *, int, int);
struct node * addatbeg(struct node *, int, int);
struct node * addatpos(struct node *, int, int);
struct node * delete(struct node *, int);
void add(struct node *, struct node *);
void mult (struct node *, struct node *);
struct node * modify (struct node *);
struct node * readfromfile(char *, FILE *);
void display (struct node *);

struct node
{
	int c;
	int e;
	struct node *link;
};

struct node * create(struct node *start)
{
	int n, coeff, expo;
	printf("Enter number of terms: ");
	scanf("%d", &n);
	start = NULL;
	if (n == 0)
		return start;
	printf("Enter coefficient of x^%d: ", n-1);
	scanf("%d", &coeff);
	start = addatbeg(start, coeff, n-1);
	for(int i = n-2; i >= 0; i--){
		printf("Enter coefficient of x^%d: ", i);
		scanf("%d", &coeff);
		start = addatend(start, coeff, i);
	}
	display (start);
	return start;
}

struct node * addatend(struct node *start, int coeff, int expo)
{
	struct node *p, *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	temp -> c = coeff;
	temp -> e = expo;
	p = start;
	while (p -> link != NULL)
		p = p -> link;
	p -> link = temp;
	temp -> link = NULL;
	return start;
}

struct node * addatbeg(struct node *start, int coeff, int expo)
{
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node));
	temp -> c = coeff;
	temp -> e = expo;
	temp -> link = start;
	start = temp;
	return start;
}

struct node * addatpos(struct node *start, int coeff, int expo){
    struct node *p = start, *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->c = coeff;
    temp->e = expo;
    temp->link = NULL;
    if (start == NULL || start->e < expo) {
        temp->link = start;
        start = temp;
        return start;
    }
    while (p->link != NULL && p->link->e >= expo)
        p = p->link;

    temp->link = p->link;
    p->link = temp;
    return start;
}

struct node * delete(struct node *start, int expo){
	struct node *p, *temp;
	if (start == NULL){
        printf("Empty list\n");
        return start;
    }
	if(start->e == expo){
		temp = start;
		start = start->link;
		free(temp);
		return start;
	}
	p = start;
	while(p->link != NULL){
		if(p->link->e == expo){
			temp = p->link;
			p->link = temp->link;
			free(temp);
			return start;
		}
		p = p->link;
	}
	printf("Term not found\n");
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
        printf(" %dx^%d", p -> c, p -> e);
        p = p -> link;
    }
}

int main()
{
	struct node *polynomial1 = NULL, *polynomial2 = NULL;
	int s, sm;
	char filename[20], yn;

	printf("Do you want to accept polynomials from a preexisting file? Y/N?\n");
	scanf("%c", &yn);
	if (yn == 'Y'){
		printf("\nEnter the filename: ");
		scanf("%s", filename);
		FILE *file = fopen(filename, "r");
		polynomial1 = readfromfile(filename, file);
		printf("\nPolynomial 1: ");
    	display(polynomial1);
		polynomial2 = readfromfile(filename, file);
		printf("\nPolynomial 2: ");
    	display(polynomial2);
		fclose(file);
	}
	else {
		printf("\nEnter the first polynomial: \n");
		polynomial1 = create(polynomial1);

		printf("\nEnter the second polynomial: \n");
		polynomial2 = create(polynomial2);
	}
	do{
		printf("\nSelect option: \n");
		printf("1. Add the two polynomials\n");
		printf("2. Multiply the two polynomials\n");
		printf("3. Modify a polynomial\n");
		printf("4. Exit\n");
		scanf("%d", &s);

		switch(s)
		{
			case 1:
				add(polynomial1, polynomial2);
				break;
			case 2:
				mult(polynomial1, polynomial2);
				break;
			case 3:
				printf("\nWhich polynomial do you want to modify: 1 or 2? ");
				scanf("%d", &sm);
				if(sm == 1)
					polynomial1 = modify(polynomial1);
				else if (sm == 2)
					polynomial2 = modify(polynomial2);
				else printf("Invalid input\n");
				break;
			case 4:
				break;
			default:
				printf("Invalid input\n");
		}
	}while(s!=4);
}


void add(struct node *start1, struct node *start2)
{
    struct node *sum = NULL, *p1 = start1, *p2 = start2;
    int csum;
	if (p1->e > p2->e)
            sum = addatbeg(sum, p1 -> c, p1 -> e);
        else if (p1 -> e < p2 -> e)
            sum = addatbeg(sum, p2 -> c, p2 -> e);
        else{
            csum = p1-> c + p2 -> c;
            sum = addatbeg(sum, csum, p1 -> e);
        	p1 = p1 -> link, p2 = p2 -> link;
	}
    while (p1->link != NULL && p2->link != NULL){
        if (p1->e > p2->e)
            sum = addatend(sum, p1 -> c, p1 -> e);
        else if (p1 -> e < p2 -> e)
            sum = addatend(sum, p2 -> c, p2 -> e);
        else{
            csum = p1-> c + p2 -> c;
            sum = addatend(sum, csum, p1 -> e);
        	p1 = p1 -> link, p2 = p2 -> link;
		}
    }
	while (p1 != NULL) {
        sum = addatend(sum, p1->c, p1->e);
        p1 = p1->link;
    }
    while (p2 != NULL) {
        sum = addatend(sum, p2->c, p2->e);
        p2 = p2->link;
    }
    display(sum);
}

void mult(struct node *start1, struct node *start2)
{
    struct node *mult = NULL, *p1 = start1, *p2 = start2;
    int cmult, emult;
	cmult = p1-> c * p2 -> c;
    emult = p1-> e + p2 -> e;
    mult = addatbeg(mult, cmult, emult);
    p1 = p1 -> link, p2 = p2 -> link;
    while (p1 != NULL && p2  != NULL){
        cmult = p1-> c * p2 -> c;
        emult = p1-> e + p2 -> e;
        mult = addatend(mult, cmult, emult);
        p1 = p1 -> link, p2 = p2 -> link;
    }
    display(mult);
}

struct node * modify(struct node *p)
{
    int s, coeff, expo;
    printf("\nSelect option:\n");
    printf("1. Insert Term\n");
    printf("2. Delete Term\n");
    scanf("%d", &s);
    switch (s) {
        case 1:
            printf("Enter coefficient and exponent of the term to be inserted: ");
            scanf("%d %d", &coeff, &expo);
            p = addatpos(p, coeff, expo);
            break;
        case 2:
            printf("Enter exponent of the term to be deleted: ");
            scanf("%d", &expo);
            p = delete(p, expo);
            break;
        default:
            printf("Invalid input\n");
    }
	display(p);
    return p;
}

struct node * readfromfile(char *filename, FILE *file)
{
	int coeff, expo;
    struct node *p = NULL;
    if (file == NULL) {
        printf("Error opening %s\n", filename);
        return NULL;
    }
	fscanf(file, "%d %d", &coeff, &expo);
	p = addatbeg(p, coeff, expo);
    while ((fscanf(file, "%d %d", &coeff, &expo) == 2)){
        p = addatend(p, coeff, expo);
		if (expo == 0)
			return p;
	}
}