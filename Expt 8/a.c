#include<stdio.h>
#include<stdlib.h>
typedef enum {false, true} bool;

struct node{
	struct node *lchild;
	bool lthread;
	int info;
	struct node *rchild;
	bool rthread;
};

struct node * insert(struct node *, int);
struct node * delete(struct node *, int);
struct node * case_a(struct node *, struct node *, struct node *);
struct node * case_b(struct node *, struct node *, struct node *);
struct node * case_c(struct node *, struct node *, struct node *);
struct node * in_succ(struct node *);
struct node * in_pred(struct node *);
void inorder(struct node *);
void preorder(struct node *);
void search (struct node *, int);

struct node * insert(struct node * root, int ikey){
	struct node *temp, *par = NULL, *ptr = root;
	int found = 0;
	while(ptr != NULL){
		if(ikey == ptr->info){
			found = 1;
			break;
		}
		par = ptr;
		if(ikey < ptr->info){
			if(ptr->lthread == false)
				ptr = ptr->lchild;
			else break;
		}
		else{
			if(ptr->rthread == false)
				ptr = ptr->rchild;
			else break;
		}
	}
	if(found)
		printf("Duplicate\n");
	else{
		temp = (struct node *)malloc(sizeof(struct node));
		temp->info = ikey;
		temp->lthread = true;
		temp->rthread = true;
		if(par == NULL){
			root = temp;
			temp->lchild = NULL;
			temp->rchild = NULL;
		}
		else if(ikey > par->info){
			temp->rchild = par->rchild;
			temp->lchild = par;
			par->rchild = temp;
			par->rthread = false;
		}
		else{
			temp->lchild = par->lchild;
			temp->rchild = par;
			par->lchild = temp;
			par->lthread = false;
		}
	}
	return root;
}

struct node * delete(struct node *root, int dkey){
	struct node *par = NULL, *ptr = root;
	int found = 0;
	while(ptr!= NULL){
		if(dkey == ptr->info){
			found = 1;
			break;
		}
		par = ptr;
		if(dkey < ptr->info){
			if(ptr->lthread == false)
				ptr = ptr->lchild;
			else break;
		}
		else{
			if(ptr->rthread == false)
				ptr = ptr->rchild;
			else break;
		}
	}
	if(found == 0)
		printf("Element not found\n");
	else if(ptr->lthread == false && ptr->rthread == false)
		root = case_c(root, par, ptr);
	else if (ptr->lthread == false && ptr->rthread == true)
        root = case_b(root, par, ptr);
    else if (ptr->lthread == true && ptr->rthread == false)
        root = case_b(root, par, ptr);
	else root = case_a(root, par, ptr);
	return root;
}

struct node * case_a(struct node *root, struct node *par, struct node *ptr){
	if(par == NULL)
		root = NULL;
	else if(ptr == par->lchild){
		par->lthread = true;
		par->lchild = ptr->lchild;
	}
	else{
		par->rthread = true;
		par->rchild = ptr->rchild;
	}
	free(ptr);
	printf("Deleted the element\n");
	return root;
}

struct node * case_b(struct node *root, struct node *par, struct node *ptr){
	struct node *child, *s, *p;
	if(ptr->lthread == false)
		child = ptr->lchild;
	else child = ptr->rchild;
	
	if(par == NULL)
		root = child;
	else if(ptr == par->lchild)
		par->lchild = child;
	else par->rchild = child;
	s = in_succ(ptr);
	p = in_pred(ptr);
	if(ptr->lthread == false)
		p->rchild = s;
	else{
		if(ptr->rthread == false)
			s->lchild = p;
	}
	free(ptr);
	printf("Deleted the element\n");
	return root;
}

struct node * case_c(struct node *root, struct node *par, struct node *ptr){
	struct node *succ = ptr->rchild, *parsucc = ptr;
	while(succ->lchild != NULL){
		parsucc = succ;
		succ = succ->lchild;
	}
	ptr->info = succ->info;
	if(succ->lthread == true && succ->rthread == true)
		root = case_a(root, parsucc, succ);
	else root = case_b(root, parsucc, succ);
	return root;
}

struct node * in_succ(struct node * ptr){
	if(ptr->rthread == true)
		return ptr->rchild;
	else{
		ptr = ptr->rchild;
		while(ptr->lthread == false)
			ptr = ptr->lchild;
		return ptr;
	}
}

struct node * in_pred(struct node * ptr){
	if(ptr->lthread == true)
		return ptr->lchild;
	else{
		ptr = ptr->lchild;
		while(ptr->rthread == false)
			ptr = ptr->rchild;
		return ptr;
	}
}

void inorder(struct node * root){
	struct node *ptr = root;
	if(ptr == NULL){
		printf("Empty\n");
		return;
	}
	while(ptr->lthread == false)
		ptr = ptr->lchild;
	while(ptr!= NULL){
		printf(" %d", ptr->info);
		ptr = in_succ(ptr);
	}
}

void preorder(struct node * root){
	struct node * ptr = root;
	if(root == NULL){
		printf("Empty\n");
		return;
	}
	while(ptr != NULL){
		printf(" %d", ptr->info);
		if(ptr->lthread == false)
			ptr = ptr->lchild;
		else if (ptr->rthread == false)
			ptr = ptr->rchild;
		else{
			while(ptr!=NULL && ptr->rthread == true)
				ptr = ptr->rchild;
			if(ptr != NULL)
				ptr = ptr->rchild;
		}
	}
}

void search(struct node* ptr, int skey){
    while(ptr->lthread == false || ptr->rthread == false){
		if(ptr->info == skey){
			printf("Element found\n");
			return;
		}
		else if(ptr->info > skey && ptr->lthread == false)
			ptr = ptr->lchild;
		else if (ptr->info < skey && ptr->rthread == false)
            ptr = ptr->rchild;
	}
	printf("Element not found\n");
}

int main(){
	struct node *root = NULL;
	int s, key, n;
	char c;
	printf("Do you want to insert many elements? (y/n): ");
	scanf("%c", &c);getchar();
	if(c == 'y'){
		printf("Enter number of elements to insert: ");
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			printf("Insert: ");
			scanf("%d", &key);
			root = insert(root, key);
		}
	}
	do{
		printf("\n1. Insertion of a new element\n"
				"2. Deletion of an existing element\n"
				"3. Searching for a given element\n"
				"4. Perform inorder and preorder traversals\n"
				"5. Exit\n");
		printf("Enter your option: ");
		scanf("%d", &s);
		switch(s){
			case 1: printf("Insert: ");
					scanf("%d", &key);
					root = insert(root, key);
					break;
			case 2: printf("Delete: ");
					scanf("%d", &key);
					root = delete(root, key);
					break;
			case 3: printf("Enter the element: ");
					scanf("%d", &key);
					search(root, key);
					break;
			case 4: printf("Inorder: "); inorder(root);
					printf("\nPreorder: "); preorder(root);
					break;
			case 5: break;
			default: printf("Invalid input\n");
		}
	}while(s != 5);

	return 0;
}
