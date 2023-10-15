#include <stdio.h>
#include <stdlib.h>

struct node{
	struct node *lchild;
	int info;
	struct node *rchild;
};


struct node * insert (struct node *, int);
struct node * delete (struct node *, int);
struct node * search (struct node *, int);
void inorder (struct node *);
void preorder (struct node *);
void postorder (struct node *);
int minimum(struct node *);
int maximum(struct node *);

struct node * insert (struct node * ptr, int ikey){
	if(ptr == NULL){
		ptr = (struct node *)malloc(sizeof(struct node));
		ptr->info = ikey;
		ptr->lchild = NULL;
		ptr->rchild = NULL;
		printf("%d inserted\n", ikey);
		return ptr;
	}
	if(ikey < ptr->info)
		ptr->lchild = insert(ptr->lchild, ikey);
	else if(ikey > ptr->info)
		ptr->rchild = insert(ptr->rchild, ikey);
	if(ikey == ptr->info)
		printf("Duplicate\n");
	return ptr;
}

struct node * delete (struct node * ptr, int dkey){
	struct node *succ, *temp;
	if(ptr == NULL){
		printf("Element not found\n");
		return ptr;
	}
	if(dkey < ptr->info)
		ptr->lchild = delete(ptr->lchild, dkey);
	else if(dkey > ptr->info)
		ptr->rchild = delete(ptr->rchild, dkey);
	else {
		if(ptr->lchild != NULL && ptr->rchild != NULL){
			succ = succ->rchild;
			while(succ->lchild!= NULL)
				succ = succ->lchild;
			ptr->info = succ->info;
			ptr->rchild = delete(ptr->rchild, succ->info);
		}
		else{
			temp = ptr;
			if(ptr->lchild != NULL)
				ptr = ptr->lchild;
			else if(ptr->rchild != NULL)
				ptr = ptr->rchild;
			else ptr = NULL;
			free (temp);
			printf("%d deleted\n", dkey);
		}
	}
	return ptr;
}

void inorder (struct node * ptr){
	if(ptr == NULL)
		return;
	inorder(ptr->lchild);
	printf("%d ", ptr->info);
	inorder(ptr->rchild);
}

void preorder (struct node * ptr){
	if(ptr == NULL)
		return;
	printf("%d ", ptr->info);
	preorder(ptr->lchild);
	preorder(ptr->rchild);
}

void postorder (struct node * ptr){
	if(ptr == NULL)
		return;
	postorder(ptr->lchild);
	postorder(ptr->rchild);
	printf("%d ", ptr->info);
}

int minimum(struct node* ptr){
    while (ptr->lchild != NULL)
        ptr = ptr->lchild;
    return ptr->info;
}

int maximum(struct node* ptr) {
    while (ptr->rchild != NULL)
        ptr = ptr->rchild;
    return ptr->info;
}

struct node* search(struct node* ptr, int skey){
    if (ptr == NULL || ptr->info == skey)
        return ptr;
    else if (skey < ptr->info)
        return search(ptr->lchild, skey);
    else return search(ptr->rchild, skey);
}

int main(){
	struct node * root = NULL, *seek = NULL;
	int key, s, c, n;
	char b;
	printf("Do you want to insert many elements? (y/n): ");
	scanf("%c", &b);
	if(b == 'y'){
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
				"4. Perform in order, pre order and post order traversals\n"
				"5. Find the maximum and minimum value\n"
				"6. Exit\n");
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
					seek = search(root, key);
					if(seek == NULL)
						printf("Element not found\n");
					else printf("Element found\n");
					break;
			case 4: printf("Inorder: "); inorder(root);
					printf("\nPreorder: "); preorder(root);
					printf("\nPostorder: "); postorder(root);
					printf("\n");
					break;
			case 5: printf("Minimum: %d\n", minimum(root));
					printf("Maximum: %d\n", maximum(root));
					break;
			case 6: break;
			default: printf("Invalid input\n");
		}
	}while(s != 6);
}
