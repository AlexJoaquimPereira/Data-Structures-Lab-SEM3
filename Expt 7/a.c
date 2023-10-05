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
		printf("Element not found\n");//OR empty tree
		return ptr;
	}
	if(dkey < ptr->info)
		ptr->lchild = delete(ptr->lchild, dkey);
	else if(dkey > ptr->info)
		ptr->rchild = delete(ptr->rchild, dkey);
	else { //i am doubting from this onwards
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

int main(){
	struct node * root = NULL;
	int k;
	for(int i = 0; i < 10; i++){
		printf("Insert: ");
		scanf("%d", &k);
		root = insert(root, k);
	}
	inorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	for(int i = 0; i < 10; i++){
		printf("Delete: ");
		scanf("%d", &k);
		root = delete(root, k);
	}
	inorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
}
